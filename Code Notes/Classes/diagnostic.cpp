#include "diagnostic.h"
#include "shader.h"
#include "text.h"
#include <algorithm>
#include <sstream>

namespace
{
    const int TEXT_BORDER = 10;             ///< Border between diagnostic text and edge of screen
    const int TEXT_SIZE = 16;               ///< Text Character size
    const int TEXT_WEIGHT = 600;            ///< Boldness of text
    const int SPHERE_SEGMENTS = 8;          ///< Quality of the sphere mesh
    const int VARIADIC_BUFFER_SIZE = 32;    ///< Size of the character buffer for variadic text calls
}

std::shared_ptr<Shader> Diagnostic::sm_shader = nullptr;
std::shared_ptr<Diagnostic> Diagnostic::sm_diag = nullptr;

Diagnostic::Diagnostic(LPDIRECT3DDEVICE9 d3ddev) :
    m_sphere(nullptr)
{
    D3DXCreateSphere(d3ddev, 1.0f, SPHERE_SEGMENTS, SPHERE_SEGMENTS, &m_sphere, NULL);

    m_colourmap.insert(ColorMap::value_type(RED, D3DXVECTOR3(1.0f, 0.0f, 0.0f)));
    m_colourmap.insert(ColorMap::value_type(GREEN, D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
    m_colourmap.insert(ColorMap::value_type(BLUE, D3DXVECTOR3(0.0f, 0.0f, 1.0f)));
    m_colourmap.insert(ColorMap::value_type(WHITE, D3DXVECTOR3(1.0f, 1.0f, 1.0f)));

    int border = 10;
    m_text.reset(new Text());
    if(!m_text->Load(d3ddev, false, TEXT_WEIGHT, TEXT_SIZE, DT_LEFT, 
        border, border, WINDOW_WIDTH-border, WINDOW_HEIGHT-border))
    {
        m_text = nullptr;
    }
}

Diagnostic::~Diagnostic()
{
    if(m_sphere)
    { 
        m_sphere->Release();
    }
}

void Diagnostic::ShowMessage(const std::string& message)
{
    MessageBox(NULL, message.c_str(), TEXT("ERROR"), MB_OK);
}

void Diagnostic::Initialise(LPDIRECT3DDEVICE9 d3ddev, std::shared_ptr<Shader> boundsShader)
{
    sm_shader = boundsShader;
    sm_diag.reset(new Diagnostic(d3ddev));
}

void Diagnostic::DrawAll2D()
{
#ifdef _DEBUG
    if(m_text)
    {
        int counter = -1;
        for(TextMap::iterator it = m_textmap.begin(); it != m_textmap.end(); ++it)
        {
            m_text->SetText(it->second.text);
            m_text->SetColour(it->second.color);
            m_text->SetPosition(TEXT_BORDER, TEXT_BORDER+(TEXT_SIZE*(++counter)));
            m_text->Draw();
        }
    }
#endif
}

void Diagnostic::DrawAll3D(const Transform& projection, const Transform& view)
{
#ifdef _DEBUG

    LPD3DXEFFECT pEffect(sm_shader->GetEffect());
    pEffect->SetTechnique(DxConstant::DefaultTechnique);

    //sort by z value for alpha blending
    auto sorter = [](const SpherePair& o1, const SpherePair& o2){ return o1.second.position.z < o2.second.position.z; };
    std::sort(m_spheremap.begin(), m_spheremap.end(), sorter);

    for(SphereMap::iterator it = m_spheremap.begin(); it != m_spheremap.end(); ++it)
    {
        m_transform.MakeIdentity();
        m_transform.SetScale(it->second.radius);
        m_transform.SetPosition(it->second.position);

        D3DXMATRIX wvp = m_transform.Matrix * view.Matrix * projection.Matrix;
        pEffect->SetMatrix(DxConstant::WordViewProjection, &wvp);

        pEffect->SetFloatArray(DxConstant::VertexColor, &it->second.color.x, 3);

        UINT nPasses = 0;
        pEffect->Begin(&nPasses, 0);
        for( UINT iPass = 0; iPass<nPasses; iPass++)
        {
            pEffect->BeginPass(iPass);
            m_sphere->DrawSubset(0);
            pEffect->EndPass();
        }
        pEffect->End();
    }

#endif
}

void Diagnostic::UpdateSphere(const std::string& id, Diagnostic::Colour color, const D3DXVECTOR3& position, float radius)
{
    auto find = [&](const SpherePair& pair){ return pair.first == id; };
    auto iterator = std::find_if(m_spheremap.begin(), m_spheremap.end(), find);
    if(iterator != m_spheremap.end())
    {
        int index = m_spheremap.size();
        m_spheremap.push_back(SpherePair(id,DiagSphere()));
        m_spheremap[index].second.color = m_colourmap[color];
        m_spheremap[index].second.position = position;
        m_spheremap[index].second.radius = radius;
    }
    else
    {
        iterator->second.color = m_colourmap[color];
        iterator->second.position = position;
        iterator->second.radius = radius;
    }
}

void Diagnostic::UpdateText(const std::string& id, Diagnostic::Colour color, const std::string& text)
{
    UpdateText(id, color, text.c_str());
}

void Diagnostic::UpdateText(const std::string& id,  Diagnostic::Colour color, const char* text)
{
    if(m_textmap.find(id) == m_textmap.end())
    {
        m_textmap.insert(TextMap::value_type(id,DiagText())); 
    }
    m_textmap[id].color = m_colourmap[color];
    GenerateText(id, text);
}

void Diagnostic::UpdateText(const std::string& id, Diagnostic::Colour color, char* text, ...)
{
    if(m_textmap.find(id) == m_textmap.end())
    {
        m_textmap.insert(TextMap::value_type(id,DiagText())); 
    }
    m_textmap[id].color = m_colourmap[color];

    char buffer[VARIADIC_BUFFER_SIZE];
    va_list arguments;
	va_start(arguments, text); //Parse the string for variables
	vsprintf_s(buffer, text, arguments); //Convert argument symbols to text
	va_end(arguments); //Store results in text
    GenerateText(id, buffer);
}

void Diagnostic::UpdateText(const std::string& id, Diagnostic::Colour color, bool increaseCounter)
{
    if(m_textmap.find(id) == m_textmap.end())
    {
        m_textmap.insert(TextMap::value_type(id,DiagText())); 
        m_textmap[id].counter = 0;
    }
    else if(increaseCounter)
    {
        ++m_textmap[id].counter;
    }
    m_textmap[id].color = m_colourmap[color];
    GenerateText(id, m_textmap[id].counter);
}

template<typename T> void Diagnostic::GenerateText(const std::string& id, const T& value)
{
    std::ostringstream stream;
    stream << id << ": " << value;
    m_textmap[id].text = stream.str();
}

void Diagnostic::UpdateLine(const std::string& id, Diagnostic::Colour color, const D3DXVECTOR3& start, D3DXVECTOR3& end)
{
    if(m_linemap.find(id) == m_linemap.end())
    {
        m_linemap.insert(LineMap::value_type(id,DiagLine())); 
    }
    m_linemap[id].color = m_colourmap[color];
    m_linemap[id].start = start;
    m_linemap[id].end = end;
}

