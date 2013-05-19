/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com) 
* Basic collision geometry class
*****************************************************************/

#pragma once

#include "common.h"
class Shader;

class Collision
{
public:

    /**
    * Shapes avaliable for collision geometry
    */
    enum CollisionShape
    {
        CUBE,
        SPHERE
    };

    /**
    * Initialise the use of collisions 
    * @param the shader to apply to collision meshes
    */
    static void Initialise(std::shared_ptr<Shader> boundsShader);

    /**
    * @return the shape the collision mesh has
    */
    CollisionShape GetShape() const { return m_shape; }

    /**
    * Sets the colour the collision mesh appears
    * @param the colour to set in rgb from 0->1.0
    */
	void SetColor(const D3DXVECTOR3& color){ m_colour = color; }

    /**
    * @return the center in world coordinates of the collision geometry
    */
    const D3DXVECTOR3& GetPosition() const { return m_position; }

    /**
    * @return the collision geometry mesh
    */
    LPD3DXMESH GetMesh(){ return m_mesh; }
    
    /**
    * Test the collision geometry against another collision geometry
    * @param the geometry to test against
    * @return whether collision occured
    */
    virtual bool TestCollision(const Collision* obj) const = 0;

    /**
    * Draw the collision geometry. Assumes Update() has been called as needed
    * @param the projection matrix
    * @param the view matrix
    */
	void Draw(const Transform& projection, const Transform& view);

    /**
    * Updates the collision geometry upon scale/rotate/translate
    */
    virtual void FullUpdate() = 0;

    /**
    * Updates the collision geometry upon translate
    */
    virtual void PositionalUpdate() = 0;

    /**
    * Set visiblity of the collision geometry
    */
    void SetDraw(bool draw) { m_draw = draw; }

protected:

    /**
    * Constructor
    * @param the shape the collision geometry will be
    * @param the transform of the parent geometry 
    */
    Collision(CollisionShape shape, const Transform& parent);

    /**
    * Destructor
    */
    virtual ~Collision();

    bool m_draw;                ///< Whether to draw the geometry
    CollisionShape m_shape;     ///< Shape of the mesh
	LPD3DXMESH m_mesh;          ///< Collision geometry mesh
	D3DXVECTOR3 m_colour;       ///< Colour to render
    const Transform& m_parent;  ///< Parent transform of the collision geometry
    Transform m_world;          ///< World transform of the collision geometry
    Transform m_localWorld;     ///< Local transform before any calculations of the geometry
    D3DXVECTOR3 m_position;     ///< Position in world coordinates of the collision geometry

    static std::shared_ptr<Shader> sm_shader;   ///< Shared shader of all collision geometry
};

class CollisionCube : public Collision
{
public:

    /**
    * Creates a cube collision model
    * @param the directX device
    * @param the transform of the mesh parent
    * @param the initial width of the cube
    * @param the initial height of the cube
    * @param the initial depth of the cube
    */
    CollisionCube(LPDIRECT3DDEVICE9 d3ddev, const Transform& parent, float width, float height, float depth);

    /**
    * Test the collision geometry against another collision geometry
    * @param the geometry to test against
    * @return whether collision occured
    */
    virtual bool TestCollision(const Collision* obj) const override;

    /**
    * Updates the collision geometry upon scale/rotate/translate
    */
    virtual void FullUpdate() override;

    /**
    * Updates the collision geometry upon translate
    */
    virtual void PositionalUpdate() override;

    /**
    * @return the min/max bounds of the box in world coordinates
    */
    const D3DXVECTOR3& GetMaxBounds() const { return m_maxBounds; }
    const D3DXVECTOR3& GetMinBounds() const { return m_minBounds; }

private:

	D3DXVECTOR3 m_localMinBounds;   ///< Untransformed min bounds of the cube
    D3DXVECTOR3 m_localMaxBounds;   ///< Untransformed max bounds of the cube
	D3DXVECTOR3 m_minBounds;        ///< Transformed world min bounds of the cube
    D3DXVECTOR3 m_maxBounds;        ///< Transformed world ma bounds of the cube
};

class CollisionSphere : public Collision
{
public:

    /**
    * Creates a sphere collision model
    * @param the directX device
    * @param the transform of the mesh parent
    * @param the initial radius of the sphere
    * @param the amount of divisions of the mesh
    */
    CollisionSphere(LPDIRECT3DDEVICE9 d3ddev, const Transform& parent, float radius, int divisions);

    /**
    * Test the collision geometry against another collision geometry
    * @param the geometry to test against
    * @return whether collision occured
    */
    virtual bool TestCollision(const Collision* obj) const override;

    /**
    * Updates the collision geometry upon scale/rotate/translate
    */
    virtual void FullUpdate() override;

    /**
    * Updates the collision geometry upon translate
    */
    virtual void PositionalUpdate() override;

    /**
    * @return the radius of the sphere
    */
    float GetRadius() const { return m_radius; }

    /**
    * Draw the collision geometry with a specific radius.
    * @param the projection matrix
    * @param the view matrix
    * @param the radius to override
    */
	void DrawWithRadius(const Transform& projection, const Transform& view, float radius);

private:

	float m_radius;      ///< sphere radius with scaling applied
    float m_localRadius; ///< initial sphere radius
};

class Collision_Manager
{
public:

    /**
    * Tests Cube-Sphere collision
    * @param the cube/sphere to test
    * @return whether collision is occurring
    */
    static bool TestCubeSphereCollision(const CollisionCube* cube, const CollisionSphere* sphere);

    /**
    * Tests Sphere-Sphere collision
    * @param the sphere/sphere to test
    * @return whether collision is occurring
    */
    static bool TestSphereSphereCollision(const CollisionSphere* sphere1, const CollisionSphere* sphere2);

    /**
    * Tests Cube-Cube collision
    * @param the cube/cube to test
    * @return whether collision is occurring
    */
    static bool TestCubeCubeCollision(const CollisionCube* cube1, const CollisionCube* cube2);
};
