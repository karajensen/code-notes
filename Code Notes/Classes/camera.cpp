////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com - camera.cpp
////////////////////////////////////////////////////////////////////////////////////////

#include "Camera.h"

Camera::Camera(const D3DXVECTOR3& position, const D3DXVECTOR3& target) : 
    m_cameraNeedsUpdate(true),
    m_initialPos(position),
    m_pos(0.0f, 0.0f, 0.0f),
    m_target(target),
    m_yaw(0.0f),     
    m_pitch(0.0f),
    m_roll(0.0f)
{
    Reset();
}

void Camera::ForwardMovement(const D3DXVECTOR2& mouseDir, float speed, bool isMouseDown)
{
    if(isMouseDown)
    {
        Forward(speed*mouseDir.y);
        m_cameraNeedsUpdate = true;
    }
}

void Camera::SideMovement(const D3DXVECTOR2& mouseDir, float speed, bool isMouseDown)
{
    if(isMouseDown)
    {
        Up(-speed*mouseDir.y);
        Right(speed*mouseDir.x);
        m_cameraNeedsUpdate = true;
    }
}

void Camera::Rotation(const D3DXVECTOR2& mouseDir, float speed, bool isMouseDown)
{
    if(isMouseDown)
    {
        if(mouseDir.x != 0.0f)
        {
            Yaw(mouseDir.x < 0.0f ? speed : -speed);
            m_cameraNeedsUpdate = true;
        }

        if(mouseDir.y != 0.0f)
        {
            Pitch(mouseDir.y < 0.0f ? speed : -speed);
            m_cameraNeedsUpdate = true;
        }
    }
}

void Camera::Forward(float val)
{
    m_pos.z += val;
}

void Camera::Right(float val)
{
    m_pos.x += val;
}

void Camera::Up(float val)
{
    m_pos.y += val;
}

void Camera::Yaw(float angle)
{
    m_yaw += angle;
}

void Camera::Pitch(float angle)
{
    m_pitch += angle;
}

void Camera::Roll(float angle)
{
    m_roll += angle;
}

void Camera::Reset()
{
    m_cameraNeedsUpdate = true;
    m_pos = m_initialPos; 
    m_yaw = 0;
    m_roll = 0;
    m_pitch = 0;
}

void Camera::UpdateCamera()
{
    if (m_cameraNeedsUpdate)
    {
        m_cameraNeedsUpdate = false;

        World.MakeIdentity();
        World.SetPosition(m_pos);

        D3DXMATRIX matRX, matRY, matRZ;
        D3DXMatrixRotationX(&matRX, m_pitch); 
        D3DXMatrixRotationY(&matRY, m_yaw);
        D3DXMatrixRotationZ(&matRZ, m_roll);
        World.Multiply(matRZ * matRX * matRY);

        float determinant = D3DXMatrixDeterminant(&World.Matrix());
        D3DXMatrixInverse(View.MatrixPtr(), &determinant, &World.Matrix());
    }
}

void Camera::CreateProjMatrix()
{
    D3DXMatrixPerspectiveFovLH(Projection.MatrixPtr(),
        D3DX_PI/4, //horizontal field of view
        static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), //aspect ratio
        1.0f, //the near view-plane
        1000.0f); //the far view-plane
}
