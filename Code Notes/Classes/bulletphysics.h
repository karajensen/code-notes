
#ifndef BULLETPHYS_H_
#define BULLETPHYS_H_

//======================================================================================================
//CLASS BULLET PHYSICS
//class for holding bullet physics code
//requires all bullet library included
//======================================================================================================

#include "include\bullet\Bullet-C-Api.h"
#include "include\bullet\btBulletCollisionCommon.h"
#include "include\bullet\btBulletDynamicsCommon.h"
#include "include\bullet\LinearMath\btQuaternion.h"
#include "include\bullet\LinearMath\btTransform.h"
#include "include\bullet\LinearMath\btIDebugDraw.h"
#include "include\bullet\LinearMath\btConvexHullComputer.h"
#include "include\bullet\LinearMath\btTransformUtil.h"
#include "include\bullet\BulletCollision\CollisionShapes\btConvexHullShape.h"
#include "include\bullet\BulletCollision\CollisionShapes\btCylinderShape.h"
#include "include\bullet\BulletCollision\CollisionShapes\btBoxShape.h"
#include "include\bullet\BulletCollision\NarrowPhaseCollision\btVoronoiSimplexSolver.h"
#include "include\bullet\BulletCollision\NarrowPhaseCollision\btGjkEpaPenetrationDepthSolver.h"
#include "include\bullet\BulletCollision\NarrowPhaseCollision\btGjkPairDetector.h"
#include "include\bullet\BulletCollision\NarrowPhaseCollision\btPointCollector.h"
#include "include\bullet\BulletCollision\NarrowPhaseCollision\btVoronoiSimplexSolver.h"
#include "include\bullet\BulletCollision\NarrowPhaseCollision\btConvexPenetrationDepthSolver.h"

#include "matrix.h"
#include "float3.h"
#include <vector>
using namespace std;

inline btVector3 BulletVector(FLOAT3 & v){ return btVector3(btScalar(v.x),btScalar(v.y),btScalar(v.z)); }
inline btVector3 BulletVector(float x, float y, float z){ return btVector3(btScalar(x),btScalar(y),btScalar(z)); }
inline FLOAT3 BulletToFLOAT3(btVector3 & v){ return FLOAT3(v.getX(),v.getY(),v.getZ()); }
inline FLOAT3 BulletToFLOAT3(const btVector3 & v){ return FLOAT3(v.getX(),v.getY(),v.getZ()); }
inline float Mag(float t){ if(t < 0){ t*= -1; } return t; }

//-----------------------------------------------------------------------------------------------------
//COLLISION EVENT STRUCTURE
//-----------------------------------------------------------------------------------------------------
struct CollisionEvent
{
    int shape1;
    int shape2;
    int body1;
    int body2;
    int objindex1;
    int objindex2;
    bool temporary;
    bool processed;
    bool colliding;
    
    CollisionEvent(){ processed = false; colliding = false; temporary = false; }
    bool operator==(CollisionEvent & a)
    {
        if((a.body1 == body1)&&(a.body2 == body2))
            return true;
        return false;
    }
};
//-----------------------------------------------------------------------------------------------------
//RIGID BODY STRUCTURE
//-----------------------------------------------------------------------------------------------------
struct RigidBody
{
    btRigidBody* rb;
    int shape;
    int index;
    int objectIndex;
    int mask;
    int group;
    bool processEvents;
    RigidBody(){ processEvents = true; }
};
//-----------------------------------------------------------------------------------------------------
//BULLET PHYSICS CLASS
//-----------------------------------------------------------------------------------------------------
class BULLET_PHYS
{
private:

    vector<btCollisionShape*> shapes;
    vector<RigidBody> bodies;
    vector<btHingeConstraint*> hinges;

    static float sleepvalue;
    static float iterations;
    static btDiscreteDynamicsWorld * dynamicsWorld;
    static btDefaultCollisionConfiguration * collisionConfiguration;
    static btCollisionDispatcher * dispatcher;
    static btBroadphaseInterface * overlappingPairCache;
    static btSequentialImpulseConstraintSolver * solver;
    static btOverlapFilterCallback * filterCallback;

    static BULLET_PHYS * p_bullet;
    BULLET_PHYS(){};
    ~BULLET_PHYS(){};

public:

    static float timestep;

    void OnTimeStep();
    int  LoadRigidBody(MATRIX & M, int Shape, float Mass, int Group, int Mask, int objectIndex, bool createEvents, FLOAT3& centerOfMass);
    void LoadConvexShape(float* vertices, int vertexno, int shape);
    void ReleaseAllObjects();
    bool GenerateCollisionEvent(int collisionIndex, CollisionEvent& colEvent);
    void RemoveFromWorld(int rigidbody);
    void ResetSimulation();
    void AddToWorld(int rigidbody, short group, int mask = NOMASK);

    bool SetGroup(int rb, int group);
    void SetMotionState(int rigidBody, MATRIX & M);
    void SetPosition(int rigidBody, FLOAT3 & v);
    void SetBasis(int rigidBody, MATRIX & M);
    void SetUserPointers();
    void SetFriction(int rb, float amount);
    void SetGravity(int rigidbody, float gravity);
    void SetVelocity(FLOAT3 & vel, int rigidbody, float linearDamp = 0, float angDamp = 0);
    void SetMass(int rb, int shape, float mass);
    void SetInternalDamping(int rb, float linear, float ang);

    int   GetCollisionAmount();
    float GetFriction(int rigidbody);
    void  GetVelocity(int rigidbody, FLOAT3 & vel);
    void  GetTransform(int rigidBody, MATRIX & M);

    void ResetVelocityAndForce(int rb);
    void AddForce(FLOAT3 & force, FLOAT3 & position, int rigidbody);
    void AddImpulse(FLOAT3 & force, FLOAT3 & position, int rigidbody);
    void AddLinearDamping(int rb, float amount);
    void AddRotationalDamping(int rb, float amount);

    float GetHingeRotation(int hinge);
    int   CreateHinge(int rb1, int rb2, FLOAT3 & pos1local, FLOAT3 & pos2local, FLOAT3 & axis1, FLOAT3 & axis2, float breakthreshold=0);
    void  RotateHinge(int hinge, float amount, float dt);
    void  StopHinge(int hinge, float dt, float damping);
    bool  HingeEnabled(int hinge);

    static const int NOMASK = -1;
    static const int NOGROUP = -1;
    static const int DISABLED = -2;
    static BULLET_PHYS* Initialise();
    static void Terminate();

};
//-----------------------------------------------------------------------------------------------------
//COLLISION MASKING STRUCTURE
//-----------------------------------------------------------------------------------------------------
struct collisionFilterCallback : public btOverlapFilterCallback
{
    //return true when pairs need collision
    //http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Collision_Filtering for reference

    virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0,btBroadphaseProxy* proxy1) const
    {
        //GROUPS: members of a group don't collide with each other
        if(proxy0->m_collisionFilterGroup == proxy1->m_collisionFilterGroup)
        {
            return false;

        } //MASK: objects with a mask only collide with the corresponding group
        else if((proxy0->m_collisionFilterMask != BULLET_PHYS::NOMASK)||
                (proxy1->m_collisionFilterMask != BULLET_PHYS::NOMASK))
        {
            if(proxy0->m_collisionFilterMask == proxy1->m_collisionFilterGroup)
                return true;
            else if(proxy1->m_collisionFilterMask == proxy0->m_collisionFilterGroup)
                return true;
            else
                return false;
        }
        else
            return true;
    }
};



#endif