#include "Camera.h"

Camera::Camera(const FLOAT3& position) : 
    m_cameraNeedsUpdate(true),
    m_yaw(0.0f),     
    m_pitch(0.0f),
    m_roll(0.0f)
{
    m_initialPos = D3DXVECTOR3(position.x, position.y, position.z);
    Reset();
}

void Camera::Forward(float val)
{
    m_pos += m_forward*val;
    m_cameraNeedsUpdate = true;
}

void Camera::Right(float val)
{
    m_pos += m_right*val;
    m_cameraNeedsUpdate = true;
}

void Camera::Up(float val)
{
    m_pos += m_up*val;
    m_cameraNeedsUpdate = true;
}

void Camera::Yaw(float angle)
{
    m_yaw += angle;
    m_cameraNeedsUpdate = true;
}

void Camera::Pitch(float angle)
{
    m_pitch += angle;
    m_cameraNeedsUpdate = true;
}

void Camera::Roll(float angle)
{
    m_roll += angle;
    m_cameraNeedsUpdate = true;
}

void Camera::Reset()
{
    m_cameraNeedsUpdate = true;
    m_pos = m_initialPos; 
    m_up = D3DXVECTOR3(0.0f,1.0f,0.0f);
    m_forward = D3DXVECTOR3(0.0f,0.0f,1.0f);
    m_right = D3DXVECTOR3(1.0f,0.0f,0.0f);
    m_yaw = 0;
    m_roll = 0;
    m_pitch = 0;
}

void Camera::UpdateCamera()
{
    if (m_cameraNeedsUpdate)
    {
        m_cameraNeedsUpdate = false;

        //set axis back to initial values(set due to float-pt errors over time would screw the axis's orthogonality)
        m_up = D3DXVECTOR3(0.0f,1.0f,0.0f);
        m_forward = D3DXVECTOR3(0.0f,0.0f,1.0f);
        m_right = D3DXVECTOR3(1.0f,0.0f,0.0f);

        //Create yaw rotation
        D3DXMATRIX yawMatrix;
        D3DXMatrixRotationAxis(&yawMatrix, &m_up, m_yaw); //matrix to store in, axis, angle
        D3DXVec3TransformCoord(&m_forward, &m_forward, &yawMatrix); //rotate axis using yaw rotation around up axis
        D3DXVec3TransformCoord(&m_right, &m_right, &yawMatrix); 

        //Create pitch rotation
        D3DXMATRIX pitchMatrix;
        D3DXMatrixRotationAxis(&pitchMatrix, &m_right, m_pitch);
        D3DXVec3TransformCoord(&m_forward, &m_forward, &pitchMatrix); 
        D3DXVec3TransformCoord(&m_up, &m_up, &pitchMatrix); 

        //Create roll rotation
        D3DXMATRIX rollMatrix;
        D3DXMatrixRotationAxis(&rollMatrix, &m_forward, m_roll);
        D3DXVec3TransformCoord(&m_right, &m_right, &rollMatrix); 
        D3DXVec3TransformCoord(&m_up, &m_up, &rollMatrix); 
        
        //set to identity matrix
        View.MakeIdentity();

        //fill in view matrix
        View.Matrix._11 = m_right.x;   View.Matrix._12 = m_up.x;   View.Matrix._13 = m_forward.x;
        View.Matrix._21 = m_right.y;   View.Matrix._22 = m_up.y;   View.Matrix._23 = m_forward.y;
        View.Matrix._31 = m_right.z;   View.Matrix._32 = m_up.z;   View.Matrix._33 = m_forward.z;
        
        //fill in view matrix position vector
        View.Matrix._41 = -D3DXVec3Dot(&m_pos,&m_right); 
        View.Matrix._42 = -D3DXVec3Dot(&m_pos,&m_up);
        View.Matrix._43 = -D3DXVec3Dot(&m_pos,&m_forward);

        //fill in world matrix
        D3DXMATRIX matTrans, matRX, matRY, matRZ;
        D3DXMatrixRotationX(&matRX, m_pitch); //PITCH
        D3DXMatrixRotationY(&matRY, m_yaw); //YAW
        D3DXMatrixRotationZ(&matRZ, m_roll); //ROLL
        World.Matrix = (matRZ*matRX*matRY);
        World.Matrix._41 = m_pos.x;
        World.Matrix._42 = m_pos.y;
        World.Matrix._43 = m_pos.z;
    }
}

void Camera::CreateProjMatrix()
{
    D3DXMatrixPerspectiveFovLH(&Projection.Matrix,
                                D3DX_PI/4, //horizontal field of view
                                static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), //aspect ratio
                                1.0f, //the near view-plane
                                1000.0f); //the far view-plane
}
