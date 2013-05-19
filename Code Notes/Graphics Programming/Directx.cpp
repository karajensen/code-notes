////////////////////////////////////////////////////////////////////////////// 
//DIRECTX
//////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------
DIRECTX: Row Major Matrix / Left Handed Coordinate System
------------------------------------------------------------------
Scale * Rot * Trans = LocalWorld
LocalWorld * ParentWorld = World
Vertex * World * View * Proj = FinalVertex in screenspace

| Right.x  Right.y   Right.z  0 |   UP: +Y
| Up.x     Up.y      Up.z     0 |   RIGHT: +X
| For.x    For.y     For.z    0 |   FORWARD: +Z
| Pos.x    Pos.y     Pos.z    1 |
------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////// 
//PERFORMANCE INVESTIGATOR FOR XBOX (PIX)
//////////////////////////////////////////////////////////////////////////////

//Markers can be used to auto-capture frames
D3DPERF_SetMarker(D3DCOLOR_ARGB(255,255,255,255), L"A_MARKER");
D3DPERF_BeginEvent(D3DCOLOR_ARGB(255,255,255,255), L"An Event");

//////////////////////////////////////////////////////////////////////////////
//DIRECTX MATRIX
//////////////////////////////////////////////////////////////////////////////

D3DXMATRIX myMatrix
myMatrix *= myMatrix2;
myMatrix = myMatrix * myMatrix2;

//Note: matIn and matOut can be the same
D3DXMatrixIdentity(&matIn);
D3DXMatrixScaling(&matIn,scale,scale,scale); //scales the matrix
D3DXMatrixTranspose(&matOut, &matIn); //transposes the matrix
D3DXMatrixDeterminant(&matIn); //returns determinate of matrix
D3DXMatrixInverse(&matOut, NULL, &matIn); //creates inverse of matIn
D3DXMatrixRotationAxis(&matOut, &axis, angle); //axis to rotate around, angle in radians

//////////////////////////////////////////////////////////////////////////////
//DIRECTX VECTORS
//////////////////////////////////////////////////////////////////////////////

D3DXVECTOR3 myVector(x, y, z)
myVector *= 2.0f;
myVector = myVector * 2.0f;

D3DXVec3Dot(&vec1, &vec2); //returns dot product of two vectors
D3DXVec3TransformCoord(&vecOut, &vecIn, &matIn); //transform in vector into matrix coordinate   
D3DXVec3Normalize(&vecOut, &vecIn);
D3DXVec3TransformNormal(&vecOut, &vecIn, &matIn);

//////////////////////////////////////////////////////////////////////////////
//CREATE PROJECTION MATRIX
//////////////////////////////////////////////////////////////////////////////

D3DXMatrixPerspectiveFovLH(
    &Projection.Matrix,
    D3DX_PI/4, //horizontal field of view
    static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), //aspect ratio
    1.0f, //the near view-plane
    1000.0f); //the far view-plane

//////////////////////////////////////////////////////////////////////////////
//DIRECTX SURFACES
//////////////////////////////////////////////////////////////////////////////
//Holds a buffer of pixels which includes additional width (pitch)
//Holds pixel format (D3DFMT_) and can be coupled with Directx Texture

/*WRITING TO A SURFACE BUFFER*/
//Get a D3DSURFACE_DESC structure which describes the surface
D3DSURFACE_DESC surfaceDesc;
surface->GetDesc(&surfaceDesc);

//Get a pointer to the surface pixel data.
D3DLOCKED_RECT lockedRect;
surface->LockRect(&lockedRect,  // pointer to receive locked data
                  0,            // lock entire surface
                  0);           // no lock flags specified

//Cast bits to pixel data (be care of non 32bit buffers)
DWORD* imageData = (DWORD*)lockedRect.pBits;

//Iterate through each pixel in the surface and set it to red.
for(int i = 0; i < surfaceDesc.Height; i++)
{
  for(int j = 0; j < surfaceDesc.Width; j++)
  {
    //Pitch is given in bytes, divide by four to get proper width of 
    //buffer. Pitch is longer than width of buffer (see image)
    int index = (i * lockedRect.Pitch) / 4 + j;

    imageData[index] = 0xffff0000;
  }
}
surface->UnlockRect();

//////////////////////////////////////////////////////////////////////////////
//DIRECTX RENDER TARGETS
//////////////////////////////////////////////////////////////////////////////
/*
1) Create texture/surface and AA Render Target Surface
2) Render all meshes onto the AA RT Surface
3) Copy AA RT surface to Texture surface using stretchrect
4) Draw the texture onto a sprite onto the back buffer, using a shader

D3DXCreateRenderToSurface() [non-AA RT]
Creates a surface which when set as a Render Target will render directly 
onto the texture. Cannot have AA set.

CreateRenderTarget() [AA RT]
Creates a surface which when set as a Render Target will render directly 
onto the surface. Can have AA set.

/*Set up for Antialiasing on a render target*/
m_d3ddev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
LPDIRECT3DSURFACE9 AARenTarSurface;
LPDIRECT3DTEXTURE9 RenTarTexture;
LPDIRECT3DSURFACE9 RenTarSurface;
LPDIRECT3DSURFACE9 BackBuffer;
d3ddev->GetRenderTarget(0, &BackBuffer);
int samples = D3DMULTISAMPLE_4_SAMPLES;
int quality = 4;
HRESULT hr;

//Create the AA Render target surface
hr = m_d3ddev->CreateRenderTarget(1024, 1024, D3DFMT_A8R8G8B8, samples,
                                  quality,false, &AARenderSurface, NULL);
if(!SUCCEEDED(hr){ /*failed*/ }

//Create the texture
hr = D3DXCreateTexture(d3ddev, 1024, 1024, 1, D3DUSAGE_RENDERTARGET, 
					   D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &RenTarTexture)
if(!SUCCEEDED(hr){ /*failed*/ }

//Get the default surface created for the texture
RenTarTexture->GetSurfaceLevel(0, &RenTarSurface);

//Render the scene to the AA render target surface 
//This renders directly into the surface buffer itself rather to a texture
//as multisampling rendering in DirectX9 cannot render to textures
d3ddev->SetRenderTarget(0, AARenTarSurface);

//Copy the AA render target surface to the texture surface
if(FAILED(d3ddev->StretchRect(AARenTarSurface, NULL, 
           RenTarSurface, NULL, D3DTEXF_LINEAR)))
{ /*failed*/ }

//Render the texture color buffer as normal to a quad and do any post work
d3ddev->SetRenderTarget(0,BackBuffer);


////////////////////////////////////////////////////////////////////////////// 
//DIRECTX CHECK SHADER MODEL
////////////////////////////////////////////////////////////////////////////// 

D3DCAPS9 caps;
gd3dDevice->GetDeviceCaps(&caps);

// Check for vertex shader version 2.0 support.
if(caps.VertexShaderVersion < D3DVS_VERSION(2, 0)) { return false; }

// Check for pixel shader version 2.0 support.
if(caps.PixelShaderVersion < D3DPS_VERSION(2, 0))  { return false; }

////////////////////////////////////////////////////////////////////////////// 
//DIRECTX LOAD A SHADER FILE
////////////////////////////////////////////////////////////////////////////// 

ID3DXBuffer* errorlog = NULL; //error buffer
if(FAILED(D3DXCreateEffectFromFile(d3ddev,filename,0,0,
   D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,0, &Shader, &errorlog)))
{
	if (errorlog)//if there is an error
		MessageBox(NULL, (char*)errorlog->GetBufferPointer(), "ERROR", MB_OK);
	else
        MessageBox(NULL, "failed", "ERROR", MB_OK);
}

////////////////////////////////////////////////////////////////////////////// 
//DIRECTX SEND INFO TO A SHADER
////////////////////////////////////////////////////////////////////////////// 

LPD3DXEFFECT pEffect;	
pEffect->SetTechnique("MAIN");
pEffect->SetFloatArray("CameraPos", &(Camera->GetPos().x), 3);
pEffect->SetMatrix("WorldInvTrans", &wit);
pEffect->SetMatrix("WorldViewProjection", &wvp);
pEffect->SetMatrix("World", &worldMatrix);

//Render the mesh
UINT nPasses = 0;
pEffect->Begin(&nPasses, 0);
for(UINT iPass = 0; iPass<nPasses; iPass++)
{
	pEffect->BeginPass(iPass);
		m_pMesh->DrawSubset(0);
	pEffect->EndPass();
}
pEffect->End();

////////////////////////////////////////////////////////////////////////////// 
//INITIALISING
////////////////////////////////////////////////////////////////////////////// 

if(FAILED(d3d = Direct3DCreate9(D3D_SDK_VERSION)))
{
    Diagnostic::ShowMessage("Direct3D interface creation has failed");
    return false;
}

// Build present params
D3DPRESENT_PARAMETERS d3dpp;
ZeroMemory(&d3dpp, sizeof(d3dpp));

D3DMULTISAMPLE_TYPE antiAliasingLvl;
bool antiAliasing = false;
if(SUCCEEDED(d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, TEXTURE_FORMAT, 
                                                true, D3DMULTISAMPLE_2_SAMPLES, nullptr)))
{
    d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
    antiAliasingLvl = D3DMULTISAMPLE_2_SAMPLES;
    antiAliasing = true;
}
d3dpp.hDeviceWindow = hWnd;
d3dpp.Windowed = true;
d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
d3dpp.BackBufferFormat = TEXTURE_FORMAT;
d3dpp.BackBufferWidth = WINDOW_WIDTH; 
d3dpp.BackBufferHeight = WINDOW_HEIGHT;
d3dpp.EnableAutoDepthStencil = TRUE;
d3dpp.AutoDepthStencilFormat = BACKBUFFER_FORMAT; 

if(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                            D3DCREATE_HARDWARE_VERTEXPROCESSING,
                            &d3dpp, &d3ddev)))
{
    Diagnostic::ShowMessage("Direct3D interface creation has failed");
    return false;
}

// Create Z-buffer
if(FAILED(d3ddev->CreateDepthStencilSurface(WINDOW_WIDTH, WINDOW_HEIGHT, BACKBUFFER_FORMAT,
                                            antiAliasing ? antiAliasingLvl : D3DMULTISAMPLE_NONE,
                                            NULL, TRUE, &backBuffer, NULL)))
{
    Diagnostic::ShowMessage("Z-buffer creation has failed");
    return false;
}
d3ddev->SetRenderTarget(0,backBuffer);

// Set render states
d3ddev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, antiAliasing);





