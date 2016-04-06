///////////////////////////////////////////////////////////////////////////////////
//RENDER ENGINES
///////////////////////////////////////////////////////////////////////////////////
/**
                ===================================================================
                |           DirectX               |           OpenGL              |
===================================================================================
| Screen Origin |           Top Left              |         Lower Left            |
| Winding Order |           Clockwise             |        Anticlockwise          |
| Z Axis        |            +Z Axis              |          -Z Axis              |
| ---------------------------------------------------------------------------------
| Transform     |      Scale * Rot * Trans        |      Trans * Rot * Scale      |
| Order         |  Vertex * World * View * Proj   |  Proj * Veiw * World * Vertex |
|----------------------------------------------------------------------------------
| Coordinate    |      Row Major Left Handed      |  Column Major Right Handed    |
| System        |  Right.x  Right.y   Right.z  0  |  Right.x  Up.x  For.x  Pos.x  |
|               |  Up.x     Up.y      Up.z     0  |  Right.y  Up.y  For.y  Pos.y  |
|               |  For.x    For.y     For.z    0  |  Right.z  Up.z  For.z  Pos.z  |
|               |  Pos.x    Pos.y     Pos.z    1  |    0       0       0     1    |
===================================================================================

-----------------------------------------------------------------------------------
OPENGL                          DIRECTX
-----------------------------------------------------------------------------------
GL_ZERO                         D3D11_BLEND_ZERO
GL_ONE                          D3D11_BLEND_ONE
GL_SRC_COLOR                    D3D11_BLEND_SRC_COLOR
GL_ONE_MINUS_SRC_COLOR          D3D11_BLEND_INV_SRC_COLOR
GL_SRC_ALPHA                    D3D11_BLEND_SRC_ALPHA
GL_ONE_MINUS_SRC_ALPHA          D3D11_BLEND_INV_SRC_ALPHA
GL_DST_ALPHA                    D3D11_BLEND_DEST_ALPHA
GL_ONE_MINUS_DST_ALPHA          D3D11_BLEND_INV_DEST_ALPHA
GL_DST_COLOR                    D3D11_BLEND_DEST_COLOR
GL_ONE_MINUS_DST_COLOR          D3D11_BLEND_INV_DEST_COLOR
GL_SRC_ALPHA_SATURATE           D3D11_BLEND_SRC_ALPHA_SAT
GL_CONSTANT_COLOR               D3D11_BLEND_BLEND_FACTOR
GL_ONE_MINUS_CONSTANT_COLOR     D3D11_BLEND_INV_BLEND_FACTOR
GL_SRC1_COLOR                   D3D11_BLEND_SRC1_COLOR
GL_ONE_MINUS_SRC1_COLOR         D3D11_BLEND_INV_SRC1_COLOR
GL_SRC1_ALPHA                   D3D11_BLEND_SRC1_ALPHA
GL_ONE_MINUS_SRC1_ALPHA         D3D11_BLEND_INV_SRC1_ALPHA
GL_FUNC_ADD                     D3D11_BLEND_OP_ADD
GL_FUNC_SUBTRACT                D3D11_BLEND_OP_SUBTRACT
GL_FUNC_REVERSE_SUBTRACT        D3D11_BLEND_OP_REV_SUBTRACT
GL_MIN                          D3D11_BLEND_OP_MIN
GL_MAX                          D3D11_BLEND_OP_MAX 

*/
///////////////////////////////////////////////////////////////////////////////////
//OPENGL
///////////////////////////////////////////////////////////////////////////////////

// TEXTURE TO PIXEL ARRAY
unsigned int* pixels = new unsigned int[width*height];
glBindTexture(GL_TEXTURE_2D, texture);
glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

// PIXEL ARRAY TO TEXTURE
// where x,y is the offset in the texture to start overwriting with the array
unsigned int pixels = new unsigned int[width*height];
glBindTexture(GL_TEXTURE_2D, texture);
glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

// OPENGL MATHS LIBRARY
#include "opengl/glm/glm.hpp"
#include "opengl/glm/gtc/matrix_transform.hpp"
glm::vec2 myVec;
glm::vec3 myVec;
glm::mat4 myMat;
glm::inverse(myMat); // returns inversed copy
myMat[0][3]
myMat1 * myMat2;

// PROJECTION
glm::perspective(FIELD_OF_VIEW, 
    WINDOW_WIDTH / static_cast<float>(WINDOW_HEIGHT),
    CAMERA_NEAR, CAMERA_FAR);

// ERROR CHECKING
// returns GL_NO_ERROR, GL_INVALID_VALUE, GL_INVALID_OPERATION
// requires an OpenGL Context to be created or will always return an error
glGetError()

// RENDER STATES
glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
glClearDepth(1.0f);
glDepthFunc(GL_LEQUAL);
glDepthRange(0.0f, 1.0f);
glFrontFace(GL_CCW); 
glEnable(GL_CULL_FACE);
glDisable(GL_MULTISAMPLE);  
glDisable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

///////////////////////////////////////////////////////////////////////////////////
//DIRECTX
///////////////////////////////////////////////////////////////////////////////////

RIGHT:    D3DXVECTOR3(m_matrix._11, m_matrix._12, m_matrix._13)
UP:       D3DXVECTOR3(m_matrix._21, m_matrix._22, m_matrix._23)
FORWARD:  D3DXVECTOR3(m_matrix._31, m_matrix._32, m_matrix._33)
POSITION: D3DXVECTOR3(m_matrix._41, m_matrix._42, m_matrix._43)

// PERFORMANCE INVESTIGATOR FOR XBOX (PIX)
// Markers can be used to auto-capture frames
D3DPERF_SetMarker(D3DCOLOR_ARGB(255,255,255,255), L"A_MARKER");
D3DPERF_BeginEvent(D3DCOLOR_ARGB(255,255,255,255), L"An Event");

// DIRECTX MATRIX
D3DXMATRIX myMatrix
myMatrix *= myMatrix2;
myMatrix = myMatrix * myMatrix2;
D3DXMatrixIdentity(&matIn);
D3DXMatrixScaling(&matIn,scale,scale,scale); //scales the matrix
D3DXMatrixTranspose(&matOut, &matIn); //transposes the matrix
D3DXMatrixDeterminant(&matIn); //returns determinate of matrix
D3DXMatrixInverse(&matOut, nullptr, &matIn); //creates inverse of matIn
D3DXMatrixRotationAxis(&matOut, &axis, angle); //axis to rotate around, angle in radians
D3DXMatrixRotationX(&matRX, m_pitch); //out mat, angle in radians
D3DXMatrixRotationY(&matRY, m_yaw); //out mat, angle in radians
D3DXMatrixRotationZ(&matRZ, m_roll); //out mat, angle in radians
D3DXMatrixRotationYawPitchRoll
D3DXMatrixReflect

// DIRECTX VECTORS
D3DXVECTOR3 myVector(x, y, z)
myVector *= 2.0f;
myVector = myVector * 2.0f;
D3DXVec3Dot(&vec1, &vec2); //returns dot product of two vectors
D3DXVec3TransformCoord(&vecOut, &vecIn, &matIn); //transform in vector into matrix coordinate   
D3DXVec3Normalize(&vecOut, &vecIn);
D3DXVec3TransformNormal(&vecOut, &vecIn, &matIn);
D3DXVec3Cross(&vecOut, &vecIn1, &vecIn2);
D3DXVec3Length(&vec) //returns length of vector    
D3DXVec3Add
D3DXVec3BaryCentric
D3DXVec3CatmullRom
D3DXVec3Hermite
D3DXVec3LengthSq
D3DXVec3Lerp
D3DXVec3Maximize
D3DXVec3Minimize
D3DXVec3Project
D3DXVec3Scale
D3DXVec3Subtract
D3DXVec3Transform
D3DXVec3Unproject

// PROJECTION MATRIX
D3DXMatrixPerspectiveFovLH(
    &Projection.Matrix,
    D3DX_PI/4, //horizontal field of view
    static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), //aspect ratio
    1.0f, //the near view-plane
    1000.0f); //the far view-plane

// MAPPING VERTEX DATA TO VERTEX SHADER
struct Vertex
{
    D3DXVECTOR3 position;
    D3DXVECTOR3 normal;
    D3DXVECTOR2 uv1;
    D3DXVECTOR2 uv2;
};

D3DVERTEXELEMENT9 VertexDec[] =
{
    { 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },     
    { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
    { 0, 32, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
    D3DDECL_END()
}; 

OutputVS VertexShader(float4 position : Position0,
                      float4 normal   : Normal0,
                      float2 uv1      : TEXCOORD0,
                      float2 uv2      : TEXCOORD1)

// RENDER STATES DX9
d3ddev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, antiAliasing);

// RENDER STATES DX11
D3D11_RASTERIZER_DESC rasterDesc;
rasterDesc.AntialiasedLineEnable = false;
rasterDesc.DepthBias = 0;
rasterDesc.DepthBiasClamp = 0.0f;
rasterDesc.DepthClipEnable = true;
rasterDesc.FillMode = D3D11_FILL_SOLID;
rasterDesc.FrontCounterClockwise = false;
rasterDesc.MultisampleEnable = true;
rasterDesc.ScissorEnable = false;
rasterDesc.SlopeScaledDepthBias = 0.0f;
rasterDesc.CullMode = D3D11_CULL_FRONT; // for Maya vert winding order
ID3D11RasterizerState* renderState;
d3ddev->CreateRasterizerState(&rasterDesc, &renderState)
context->RSSetState(renderState);

// ERROR CHECKING
dxObject->SetPrivateData(WKPDID_D3DDebugObjectName, name.size(), name.c_str());



