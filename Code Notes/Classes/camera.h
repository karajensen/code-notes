////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "common.h"

/**
* Maya styled camera class 
*/
class Camera
{
public:

    /**
    * Constructor
    * @param position The initial position of the camera
    * @param target The target the camera looks at
    */
    Camera(const D3DXVECTOR3& position, const D3DXVECTOR3& target);

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
    * Generates forward movement for the camera
    * @param mouseDir The direction the mouse has moved
    * @param speed The speed for the movement (negative for reverse)
    * @param isMouseDown Whether the mouse is pressed or not
    */
    void ForwardMovement(const D3DXVECTOR2& mouseDir, float speed, bool isMouseDown);

    /**
    * Generates side movement for the camera
    * @param mouseDir The direction the mouse has moved
    * @param speed The speed for the movement (negative for reverse)
    * @param isMouseDown Whether the mouse is pressed or not
    */
    void SideMovement(const D3DXVECTOR2& mouseDir, float speed, bool isMouseDown);

    /**
    * Generates rotation for the camera around the world origin
    * @param mouseDir The direction the mouse has moved
    * @param speed The speed for the movement (negative for reverse)
    * @param isMouseDown Whether the mouse is pressed or not
    */
    void Rotation(const D3DXVECTOR2& mouseDir, float speed, bool isMouseDown);

    Transform Projection;   ///< Projection Matrix for the camera
    Transform View;         ///< View Matrix for the camera
    Transform World;        ///< World Matrix for the camera

private:

    /**
    * Rotate the camera
    * @param angle The angle to rotate in radians
    */
    void Yaw(float angle);

    /**
    * Rotate the camera
    * @param angle The angle to rotate in radians
    */
    void Pitch(float angle);

    /**
    * Rotate the camera
    * @param angle The angle to rotate in radians
    */
    void Roll(float angle);

    /**
    * Translates the camera
    * @param val The amount to move the camera
    */
    void Forward(float val);

    /**
    * Translates the camera
    * @param val The amount to move the camera
    */
    void Right(float val);

    /**
    * Translates the camera
    * @param val The amount to move the camera
    */
    void Up(float val);

    bool m_cameraNeedsUpdate;  ///< Whether the camera requires updating or not
    D3DXVECTOR3 m_initialPos;  ///< Camera initial position in world space
    D3DXVECTOR3 m_pos;         ///< Camera position in world space
    D3DXVECTOR3 m_target;      ///< Camera Look target
    float m_yaw;               ///< Radian amount of yaw
    float m_pitch;             ///< Radian amount of pitch
    float m_roll;              ///< Radian amount of roll
};