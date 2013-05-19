
#include "collision.h"
#include "shader.h"

std::shared_ptr<Shader> Collision::sm_shader = nullptr;

Collision::Collision(Collision::CollisionShape shape, const Transform& parent) :
    m_draw(false),
    m_shape(shape),
    m_mesh(nullptr),
    m_colour(0.0f,0.0f,1.0f),
    m_parent(parent)
{
}

CollisionCube::CollisionCube(LPDIRECT3DDEVICE9 d3ddev, const Transform& parent, float width, float height, float depth) :
    Collision(CUBE, parent),
    m_localMinBounds(-width/2.0f, -height/2.0f, -depth/2.0f),
    m_localMaxBounds(width/2.0f, height/2.0f, depth/2.0f)
{
    D3DXCreateBox(d3ddev,width,height,depth,&m_mesh,NULL);

    m_localWorld.SetScale(width, height, depth);
    m_world.Matrix = m_localWorld.Matrix * m_parent.Matrix;
    m_position = m_world.Position();
    D3DXVec3TransformCoord(&m_minBounds, &m_localMinBounds, &m_world.Matrix);
    D3DXVec3TransformCoord(&m_maxBounds, &m_localMaxBounds, &m_world.Matrix);
}

CollisionSphere::CollisionSphere(LPDIRECT3DDEVICE9 d3ddev, const Transform& parent, float radius, int divisions) :
    Collision(SPHERE, parent),
    m_localRadius(radius),
    m_radius(0.0f)
{
    D3DXCreateSphere(d3ddev,radius,divisions,divisions,&m_mesh,NULL);

    m_localWorld.SetScale(radius);
    m_world.Matrix = m_localWorld.Matrix * m_parent.Matrix;
    m_position = m_world.Position();
    m_radius = m_localRadius * m_world.GetScaleFactor().x;
}

Collision::~Collision()
{ 
    if(m_mesh != nullptr)
    { 
        m_mesh->Release(); 
    } 
}

void Collision::Initialise(std::shared_ptr<Shader> boundsShader)
{
    sm_shader = boundsShader;
}

void Collision::Draw(const Transform& projection, const Transform& view)
{
    if(m_draw && m_mesh)
    {
        LPD3DXEFFECT pEffect(sm_shader->GetEffect());
        pEffect->SetTechnique(DxConstant::DefaultTechnique);

        D3DXMATRIX wvp = m_world.Matrix * view.Matrix * projection.Matrix;
        pEffect->SetMatrix(DxConstant::WordViewProjection, &wvp);

        pEffect->SetFloatArray(DxConstant::VertexColor, &(m_colour.x), 3);

        UINT nPasses = 0;
        pEffect->Begin(&nPasses, 0);
        for( UINT iPass = 0; iPass<nPasses; iPass++)
        {
            pEffect->BeginPass(iPass);
            m_mesh->DrawSubset(0);
            pEffect->EndPass();
        }
        pEffect->End();
    }
}

void CollisionCube::PositionalUpdate()
{
    D3DXVECTOR3 difference(m_position-m_parent.Position());
    m_position += difference;
    m_world.Translate(difference);
    m_minBounds += difference;
    m_maxBounds += difference;
}

void CollisionSphere::PositionalUpdate()
{
    m_position = m_parent.Position();
    m_world.SetPosition(m_position);
}

void CollisionCube::FullUpdate()
{
    //DirectX:  World = LocalWorld * ParentWorld
    m_world.Matrix = m_localWorld.Matrix * m_parent.Matrix;
    m_position = m_world.Position();
    D3DXVec3TransformCoord(&m_minBounds, &m_localMinBounds, &m_world.Matrix);
    D3DXVec3TransformCoord(&m_maxBounds, &m_localMaxBounds, &m_world.Matrix);
}

void CollisionSphere::FullUpdate()
{
    //DirectX:  World = LocalWorld * ParentWorld
    m_world.Matrix = m_localWorld.Matrix * m_parent.Matrix;
    m_position = m_world.Position();
    
    //assumes uniform scaling
    m_radius = m_localRadius * m_world.GetScaleFactor().x;
}

bool CollisionCube::TestCollision(const Collision* obj) const
{
    switch(obj->GetShape())
    {
    case SPHERE:
        return Collision_Manager::TestCubeSphereCollision(this, static_cast<const CollisionSphere*>(obj));
    case CUBE:
        return Collision_Manager::TestCubeCubeCollision(this, static_cast<const CollisionCube*>(obj));
    }
    return false;
}

bool CollisionSphere::TestCollision(const Collision* obj) const
{
    switch(obj->GetShape())
    {
    case SPHERE:
        return Collision_Manager::TestSphereSphereCollision(this, static_cast<const CollisionSphere*>(obj));
    case CUBE:
        return Collision_Manager::TestCubeSphereCollision(static_cast<const CollisionCube*>(obj), this);
    }
    return false;
}

bool Collision_Manager::TestSphereSphereCollision(const CollisionSphere* sphere1, const CollisionSphere* sphere2)
{
    D3DVECTOR relPos = sphere1->GetPosition() - sphere2->GetPosition();
    float dist = (relPos.x * relPos.x) + (relPos.y * relPos.y) + (relPos.z * relPos.z);
    float minDist = sphere1->GetRadius() + sphere2->GetRadius();
    return (dist <= (pow(minDist,2)));
}

bool Collision_Manager::TestCubeCubeCollision(const CollisionCube* cube1, const CollisionCube* cube2)
{
    return (!((cube1->GetMaxBounds().x < cube2->GetMinBounds().x || cube1->GetMinBounds().x > cube2->GetMaxBounds().x) ||
              (cube1->GetMaxBounds().y < cube2->GetMinBounds().y || cube1->GetMinBounds().y > cube2->GetMaxBounds().y) ||
              (cube1->GetMaxBounds().z < cube2->GetMinBounds().z || cube1->GetMinBounds().z > cube2->GetMaxBounds().z)));
}

bool Collision_Manager::TestCubeSphereCollision(const CollisionCube* cube, const CollisionSphere* sphere)
{
    //get normalized vector from sphere center to box center
    //times by radius to get vector from center sphere to sphere pointing at cube
    D3DXVECTOR3 sphereToBox = cube->GetPosition() - sphere->GetPosition();
    D3DXVec3Normalize(&sphereToBox,&sphereToBox);
    D3DXVECTOR3 sphereDir = sphere->GetRadius() * sphereToBox; //vector from center of sphere pointing at cube

    //convert vector to world space
    sphereDir += sphere->GetPosition();

    //check for collision
    if((sphereDir.x < cube->GetMaxBounds().x) && (sphereDir.x > cube->GetMinBounds().x)) //test if in x portion
    {
        if((sphereDir.y < cube->GetMaxBounds().y) && (sphereDir.y > cube->GetMinBounds().y)) //test if in y portion
        {
            return ((sphereDir.z < cube->GetMaxBounds().z) && (sphereDir.z > cube->GetMinBounds().z)); //test if in z portion
        }
    }
    return false;
}

void CollisionSphere::DrawWithRadius(const Transform& projection, const Transform& view, float radius)
{
    m_world.Matrix._11 = m_world.Matrix._22 = m_world.Matrix._33 = radius;
    Draw(projection, view);
    m_world.Matrix._11 = m_world.Matrix._22 = m_world.Matrix._33 = m_radius;
}