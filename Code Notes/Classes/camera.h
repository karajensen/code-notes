/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com) 
* Maya styled camera class 
*****************************************************************/
#pragma once

#include "common.h"

class Camera
{
public:

    /**
    * Constructor
    * @param the initial position of the camera
    */
    Camera(const FLOAT3& position);

    /**
    * Updates the view matrix
    */
    void UpdateCamera();

    /**
    * Resets the camera to the initial state
    */
    void Reset();

    /**
    * Creates the projection matrix for the camera
    */
    void CreateProjMatrix();

    /**
    * Rotate the camera
    * @param angle the angle to rotate in radians
    */
    void Yaw(float angle);
    void Pitch(float angle);
    void Roll(float angle);

    /**
    * Translates the camera
    * @param the amount to move the camera
    */
    void Forward(float val);
    void Right(float val);
    void Up(float val);

    Transform Projection; ///< Projection Matrix for the camera
    Transform View;       ///< View Matrix for the camera
    Transform World;      ///< World Matrix for the camera

private:

    bool m_cameraNeedsUpdate;  ///< Whether the camera requires updating or not
	D3DXVECTOR3 m_initialPos;  ///< Camera initial position in world space
	D3DXVECTOR3 m_pos;         ///< Camera position in world space
	D3DXVECTOR3 m_up;          ///< Camera up axis
    D3DXVECTOR3 m_forward;     ///< Camera forward axis
    D3DXVECTOR3 m_right;       ///< Camera right axis
    float m_yaw;               ///< Radian amount of yaw
    float m_pitch;             ///< Radian amount of pitch
    float m_roll;              ///< Radian amount of roll
};