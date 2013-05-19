/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com) 
* Diagnostic static drawing class
*****************************************************************/
#pragma once

#include <unordered_map>
#include "common.h"

class Shader;
class Text;

class Diagnostic
{
public:

    /**
    * Easy access diagnostic colours
    */
    enum Colour
    {
        WHITE,
        RED,
        GREEN,
        BLUE
    };

    /**
    * @return the pointer to the diagnostics object
    */
    static Diagnostic& Get() { return *sm_diag; }

    /**
    * Initialise the use of diagnostics 
    * @param the directX device
    * @param the shader to apply to diagnostics meshes
    */
    static void Initialise(LPDIRECT3DDEVICE9 d3ddev, std::shared_ptr<Shader> boundsShader);

    /**
    * Shows a popup box with a message
    * @param the message to show
    */
    static void Diagnostic::ShowMessage(const std::string& message);

    /**
    * Adds a sphere for diagnostic rendering. Will only add once per id and update each call
    * @param the id of the sphere
    * @param the colour of the sphere
    * @param the poition in world coordinates
    * @param the radius of the sphere
    */
    void UpdateSphere(const std::string& id, Colour color, const D3DXVECTOR3& position, float radius);

    /**
    * Adds text for diagnostic rendering. Will only add once per id and update each call
    * @param the id of the text
    * @param the colour of the text
    * @param the text to draw
    */
    void UpdateText(const std::string& id, Colour color, const std::string& text);
    void UpdateText(const std::string& id, Colour color, const char* text);
    
    /**
    * Adds text for diagnostic rendering. Will only add once per id and update each call
    * @param the id of the text
    * @param the colour of the text
    * @param the c-string with value identifies
    * @param all values to display in the string
    */
    void UpdateText(const std::string& id, Colour color, char* text, ...);

    /**
    * Adds text for diagnostic rendering. Will only add once per id and update each call
    * @param the id of the text
    * @param the colour of the text
    * @param whether to increase the counter or not
    */
    void UpdateText(const std::string& id, Colour color, bool increaseCounter);

    /**
    * Adds a line for diagnostic rendering. Will only add once per id and update each call
    * @param the id of the line
    * @param the colour of the line
    * @param the start position in world coordinates
    * @param the end position in world coordinates
    */
    void UpdateLine(const std::string& id, Colour color, const D3DXVECTOR3& start, D3DXVECTOR3& end);

    /**
    * Draws all 3D diagnostics
    * @param the projection matrix
    * @param the view matrix
    */
    void DrawAll3D(const Transform& projection, const Transform& view);

    /**
    * Draws all 2D diagnostics
    */
    void DrawAll2D();

    /**
    * Destructor
    */
    ~Diagnostic();

private:

    static std::shared_ptr<Shader> sm_shader; ///< Global diagnostic mesh shader
    static std::shared_ptr<Diagnostic> sm_diag; ///< Diagnostic singleton pointer

    Diagnostic(LPDIRECT3DDEVICE9 d3ddev);
    Diagnostic& operator=(const Diagnostic&);
    Diagnostic(const Diagnostic&);     

    /**
    * Generates the text to display for the given key. Key must exist.
    * @param the id of the text
    * @param the value to display
    */
    template<typename T> void GenerateText(const std::string& id, const T& value);

    /**
    * Diagnostics sphere
    */
    struct DiagSphere
    {
        D3DXVECTOR3 color;     ///< Colour of the sphere
        D3DXVECTOR3 position;  ///< World coordinate center of the sphere
        float radius;          ///< Radius of the sphere
    };

    /**
    * Diagnostics text
    */
    struct DiagText
    {
        D3DXVECTOR3 color;  ///< Colour of the text
        std::string text;   ///< Actual text to display
        int counter;        ///< Optional counter for text
    };

    /**
    * Diagnostics line
    */
    struct DiagLine
    {
        D3DXVECTOR3 color;  ///< Colour of the lin
        D3DXVECTOR3 start;  ///< Start position in world coordinates
        D3DXVECTOR3 end;    ///< End position in world coordinates
    };

    typedef std::string KeyType;
    typedef std::pair<KeyType, DiagSphere> SpherePair;
    typedef std::vector<SpherePair> SphereMap;
    typedef std::unordered_map<KeyType, DiagText> TextMap;
    typedef std::unordered_map<KeyType, DiagLine> LineMap;
    typedef std::unordered_map<Colour, D3DXVECTOR3> ColorMap;

    LineMap m_linemap;      ///< Map of line diagnostics
    TextMap m_textmap;      ///< Map of text diagnostics
    SphereMap m_spheremap;  ///< Sorted vector map of sphere diagnostics
    ColorMap m_colourmap;   ///< Easy access diagnostic colours

    Transform m_transform;             ///< Diagnostic transform for mesh
    LPD3DXMESH m_sphere;               ///< Diagnostic geometry sphere
    std::shared_ptr<Text> m_text;      ///< Diagnostic text
    LPD3DXLINE m_line;                 ///< Diagnostic line
};