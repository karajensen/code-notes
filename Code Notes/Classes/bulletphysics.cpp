#include "bulletphysics.h"

//=====================================================================================
//Static variables
//=====================================================================================
float BULLET_PHYS::iterations;
float BULLET_PHYS::timestep;
float BULLET_PHYS::sleepvalue;
BULLET_PHYS * BULLET_PHYS::p_bullet = nullptr;
btDiscreteDynamicsWorld* BULLET_PHYS::dynamicsWorld = nullptr;
btDefaultCollisionConfiguration* BULLET_PHYS::collisionConfiguration = nullptr;
btCollisionDispatcher* BULLET_PHYS::dispatcher = nullptr;
btBroadphaseInterface* BULLET_PHYS::overlappingPairCache = nullptr;
btSequentialImpulseConstraintSolver* BULLET_PHYS::solver = nullptr;
btOverlapFilterCallback * BULLET_PHYS::filterCallback = nullptr;
//=====================================================================================
//Simulation timestep
//=====================================================================================
void BULLET_PHYS::OnTimeStep()
{
	//Stimulate
	for (int i = 0; i < iterations; i++)
		dynamicsWorld->stepSimulation(timestep);
}
//=====================================================================================
//Set the collision group [will only suceed if rb is in world]
//=====================================================================================
bool BULLET_PHYS::SetGroup(int rb, int group)
{
	bodies[rb].group = group;
	btBroadphaseProxy* bt = bodies[rb].rb->getBroadphaseHandle();

	if(bt == nullptr)
  		return false;
	else
		bt->m_collisionFilterGroup = group;
	return true;
}
//=====================================================================================
//Set the mass
//=====================================================================================
void BULLET_PHYS::SetMass(int rb, int shape, float mass)
{
	btVector3 localInertia(0,0,0);
	shapes[shape]->calculateLocalInertia(mass,localInertia);
	bodies[rb].rb->setMassProps(mass,localInertia);
}
//=====================================================================================
//Get number of collisions
//=====================================================================================
int BULLET_PHYS::GetCollisionAmount()
{
	return dispatcher->getNumManifolds();
}
//=====================================================================================
//Collision detection
//=====================================================================================
bool BULLET_PHYS::GenerateCollisionEvent(int collisionIndex, CollisionEvent& colEvent)
{
	btPersistentManifold* contactManifold = dispatcher->getManifoldByIndexInternal(collisionIndex);
	btCollisionObject* obA = (btCollisionObject*)contactManifold->getBody0();
	btCollisionObject* obB = (btCollisionObject*)contactManifold->getBody1();
	RigidBody* a = (RigidBody*)obA->getUserPointer();
	RigidBody* b = (RigidBody*)obB->getUserPointer();

	//check if any of the bodies doesn't want events
	if((!a->processEvents) || (!b->processEvents))
		return false;

	colEvent.objindex1 = a->objectIndex;
	colEvent.objindex2 = b->objectIndex;
	colEvent.shape1 = a->shape;
	colEvent.shape2 = b->shape;
	colEvent.body1 = a->index;
	colEvent.body2 = b->index;
	return true;
}
//=====================================================================================
//Add a force
//=====================================================================================
void BULLET_PHYS::AddForce(FLOAT3 & force, FLOAT3 & position, int rb)
{
	if(!bodies[rb].rb->isActive())
		bodies[rb].rb->activate(true);

	bodies[rb].rb->applyForce(BulletVector(force),BulletVector(position));
}
//=====================================================================================
//Get the friction
//=====================================================================================
float BULLET_PHYS::GetFriction(int rb)
{
	return bodies[rb].rb->getFriction();
}
//=====================================================================================
//Change the rbs velocity
//=====================================================================================
void BULLET_PHYS::SetVelocity(FLOAT3 & vel, int rb, float linearDamp, float angDamp)
{
	if(!bodies[rb].rb->isActive())
		bodies[rb].rb->activate(true);

	bodies[rb].rb->setLinearVelocity(BulletVector(vel));
	bodies[rb].rb->setDamping(linearDamp, angDamp);
}
//=====================================================================================
//Add an impulse
//=====================================================================================
void BULLET_PHYS::AddImpulse(FLOAT3 & force, FLOAT3 & position, int rb)
{
	if(!bodies[rb].rb->isActive())
		bodies[rb].rb->activate(true);

	bodies[rb].rb->applyImpulse(BulletVector(force),BulletVector(position));
}
//=====================================================================================
//Add an impulse
//=====================================================================================
void BULLET_PHYS::GetVelocity(int rb, FLOAT3 & vel)
{
	vel = BulletToFLOAT3(bodies[rb].rb->getLinearVelocity());
}
//=====================================================================================
//Add Set damping
//=====================================================================================
void BULLET_PHYS::SetInternalDamping(int rb, float linear, float ang)
{
	bodies[rb].rb->setDamping(linear, ang);
}
//=====================================================================================
//Add linear damping
//=====================================================================================
void BULLET_PHYS::AddLinearDamping(int rb, float amount)
{
	FLOAT3 v = BulletToFLOAT3(bodies[rb].rb->getLinearVelocity());
	v.x *= amount;
	v.z *= amount;
	bodies[rb].rb->setLinearVelocity(BulletVector(v));
}
//=====================================================================================
//Add rotational damping
//=====================================================================================
void BULLET_PHYS::AddRotationalDamping(int rb, float amount)
{
	FLOAT3 a = BulletToFLOAT3(bodies[rb].rb->getAngularVelocity());
	a.x *= amount;
	a.y *= amount;
	a.z *= amount;
	bodies[rb].rb->setAngularVelocity(BulletVector(a));
}
//=====================================================================================
//Remove a rigid body from the world
//=====================================================================================
void BULLET_PHYS::RemoveFromWorld(int rb)
{
	dynamicsWorld->removeRigidBody(bodies[rb].rb);
}
//=====================================================================================
//Set gravity for a rb
//=====================================================================================
void BULLET_PHYS::SetGravity(int rb, float gravity)
{
	bodies[rb].rb->setGravity(BulletVector(0,gravity,0));
	bodies[rb].rb->applyGravity();
}
//=====================================================================================
//Set friction for a rb
//=====================================================================================
void BULLET_PHYS::SetFriction(int rb, float amount)
{
	bodies[rb].rb->setFriction(amount);
}
//=====================================================================================
//add to the world
//=====================================================================================
void BULLET_PHYS::AddToWorld(int rb, short group, int mask)
{
	dynamicsWorld->addRigidBody(bodies[rb].rb,group,mask);
}
//=====================================================================================
//Reset the forces/velocty of a body
//=====================================================================================
void BULLET_PHYS::ResetVelocityAndForce(int rb)
{
	bodies[rb].rb->clearForces();
	bodies[rb].rb->setAngularVelocity(BulletVector(0,0,0));
	bodies[rb].rb->setLinearVelocity(BulletVector(0,0,0));
}
//=====================================================================================
//Set a rb's motion state
//=====================================================================================
void BULLET_PHYS::SetMotionState(int rb, MATRIX & M)
{
	btTransform& transform = bodies[rb].rb->getWorldTransform();
	btMatrix3x3 basis;
	basis.setValue(M.m11,M.m12,M.m13,M.m21,M.m22,M.m23,M.m31,M.m32,M.m33);
	transform.setOrigin(BulletVector(M.Position()));
	transform.setBasis(basis);
	bodies[rb].rb->setWorldTransform(transform);
	bodies[rb].rb->getMotionState()->setWorldTransform(transform);
}
//=====================================================================================
//Set a rb's motion state basis
//=====================================================================================
void BULLET_PHYS::SetBasis(int rb, MATRIX & M)
{
	btTransform& transform = bodies[rb].rb->getWorldTransform();
	btMatrix3x3 basis;
	basis.setValue(M.m11,M.m12,M.m13,M.m21,M.m22,M.m23,M.m31,M.m32,M.m33);
	transform.setBasis(basis);
	bodies[rb].rb->setWorldTransform(transform);
	bodies[rb].rb->getMotionState()->setWorldTransform(transform);
}
//=====================================================================================
//Set a rb's motion state position
//=====================================================================================
void BULLET_PHYS::SetPosition(int rb, FLOAT3 & v)
{
	btTransform transform;
	bodies[rb].rb->getMotionState()->getWorldTransform(transform);	
	transform.setOrigin(BulletVector(v));
	bodies[rb].rb->setWorldTransform(transform);
	bodies[rb].rb->getMotionState()->setWorldTransform(transform);
}
//=====================================================================================
//Get transform information from a specific rigid body
//=====================================================================================
void BULLET_PHYS::GetTransform(int rb, MATRIX & M)
{
	btTransform trans;
	bodies[rb].rb->getMotionState()->getWorldTransform(trans);

	FLOAT3 position = BulletToFLOAT3(trans.getOrigin());
	btMatrix3x3 basis = trans.getBasis();
		
	M.SetPosition(position);
	M.SetRight(BulletToFLOAT3(basis.getColumn(0)));
	M.SetUp(BulletToFLOAT3(basis.getColumn(1)));
	M.SetForward(BulletToFLOAT3(basis.getColumn(2)));
}
//=====================================================================================
//Create a hinge constraint
//=====================================================================================
int BULLET_PHYS::CreateHinge(int rb1, int rb2, FLOAT3 & pos1local, FLOAT3 & pos2local, FLOAT3 & axis1, FLOAT3 & axis2, float breakthreshold)
{
	hinges.push_back(nullptr);
	hinges[hinges.size()-1] = new btHingeConstraint((*(bodies[rb1].rb)),(*(bodies[rb2].rb)),
													BulletVector(pos1local),BulletVector(pos2local),
													BulletVector(axis1),BulletVector(axis2));

	hinges[hinges.size()-1]->enableAngularMotor(true,0.0f,10.0f);

	if(breakthreshold != 0)
		hinges[hinges.size()-1]->setBreakingImpulseThreshold(breakthreshold);

	dynamicsWorld->addConstraint(hinges[hinges.size()-1]);
	return (hinges.size()-1);
}
//=====================================================================================
//Test if the hinge is enabled
//=====================================================================================
bool BULLET_PHYS::HingeEnabled(int hinge)
{
	return hinges[hinge]->isEnabled();
}
//=====================================================================================
//Rotate the hinge
//=====================================================================================
void BULLET_PHYS::RotateHinge(int hinge, float amount, float dt)
{
	hinges[hinge]->setEnabled(true);
	btRigidBody& a = hinges[hinge]->getRigidBodyA();
	btRigidBody& b = hinges[hinge]->getRigidBodyB();
	if(!a.isActive())
		a.activate(true);
	if(!b.isActive())
		b.activate(true);
	
	hinges[hinge]->setMotorTarget(amount,dt);
}
//=====================================================================================
//Get the hinge's current rotation
//=====================================================================================
float BULLET_PHYS::GetHingeRotation(int hinge)
{
	return hinges[hinge]->getHingeAngle();
}
//=====================================================================================
//Disable the hinge
//=====================================================================================
void BULLET_PHYS::StopHinge(int hinge, float dt, float damping)
{
	float vel = hinges[hinge]->getMotorTargetVelosity();
	hinges[hinge]->setMotorTarget(hinges[hinge]->getHingeAngle()+(vel*damping),dt);
}
//=====================================================================================
//Load a custom shape
//=====================================================================================
void BULLET_PHYS::LoadConvexShape(float* vertices, int vertexno, int shape)
{
	btCollisionShape* newShape = new btConvexHullShape(vertices,vertexno,3*sizeof(btScalar));
	shapes.push_back(newShape);
}
//=====================================================================================
//Load a rigid body
//=====================================================================================
int BULLET_PHYS::LoadRigidBody(MATRIX & M, int Shape, float Mass, int Group, int Mask, int objectIndex, bool createEvents, FLOAT3& centerOfMass)
{
	btTransform transform;
	btMatrix3x3 basis;
	basis.setValue(M.m11,M.m21,M.m31,M.m12,M.m22,M.m32,M.m13,M.m23,M.m33);
	transform.setIdentity();
	transform.setOrigin(BulletVector(M.Position()));
	transform.setBasis(basis);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (Mass != 0.f);
	btVector3 localInertia(BulletVector(centerOfMass));
	if (isDynamic)
		shapes[Shape]->calculateLocalInertia(Mass,localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(Mass,myMotionState,shapes[Shape],localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	
	body->setSleepingThresholds(sleepvalue,sleepvalue);
	body->setCcdMotionThreshold(0);
	
	//add rigid body
	RigidBody newRB;
	newRB.rb = body;
	newRB.shape = Shape;
	newRB.objectIndex = objectIndex;
	newRB.processEvents = createEvents;
	newRB.group = Group;

	bodies.push_back(newRB);
	int index = bodies.size()-1;

	bodies[index].index = index;
	dynamicsWorld->addRigidBody(body,Group,Mask);
	return index;
}
//=====================================================================================
//Set user pointers [saves address in rb vector into actual rb object]
//=====================================================================================
void BULLET_PHYS::SetUserPointers()
{
	for(unsigned int i = 0; i < bodies.size(); i++)
		bodies[i].rb->setUserPointer((void*)&bodies[i]);
}
//=====================================================================================
//Reset the simulation
//=====================================================================================
void BULLET_PHYS::ResetSimulation()
{
	//delete all constraints
	for(unsigned int i = 0; i < hinges.size(); i++)
	{
		dynamicsWorld->removeConstraint(hinges[i]);
		delete hinges[i];
	}

	//delete all rigid bodies
	for(unsigned int i = 0; i < bodies.size(); i++)
	{
		dynamicsWorld->removeRigidBody(bodies[i].rb);
		delete bodies[i].rb->getMotionState();
		delete bodies[i].rb;
	}
	
	hinges.clear();
	bodies.clear();
	dynamicsWorld->clearForces();
	dynamicsWorld->setGravity(btVector3(0,-10,0));
}
//=====================================================================================
//Release all objects in world
//=====================================================================================
void BULLET_PHYS::ReleaseAllObjects()
{
	//delete all constraints
	for(unsigned int i = 0; i < hinges.size(); i++)
	{
		dynamicsWorld->removeConstraint(hinges[i]);
		delete hinges[i];
	}

	//delete all rigid bodies
	for(unsigned int i = 0; i < bodies.size(); i++)
	{
		dynamicsWorld->removeRigidBody(bodies[i].rb);
		delete bodies[i].rb->getMotionState();
		delete bodies[i].rb;
	}

	//delete collision states
	for (unsigned int j = 0; j < shapes.size(); j++)
		delete shapes[j];

	shapes.clear();
	hinges.clear();
	bodies.clear();
}
//=====================================================================================
//Terminate Bullet
//=====================================================================================
void BULLET_PHYS::Terminate()
{
	if(p_bullet != nullptr)
	{
		delete filterCallback;
		delete dynamicsWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
		delete collisionConfiguration;
		delete p_bullet;
	}
}
//=====================================================================================
//Initialise Bullet
//=====================================================================================
BULLET_PHYS* BULLET_PHYS::Initialise()
{
	//Create a new object if needed
	if(p_bullet != nullptr)
		return p_bullet;
	p_bullet = new BULLET_PHYS();

	//Set values
	timestep = 1.0f/500.0f;
	iterations = 1;
	sleepvalue = 0.0f;

	//collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	//use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	//btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	//the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	//Create dynamics world
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-10,0));

	//Register custom filter callback
	filterCallback = new collisionFilterCallback();
	dynamicsWorld->getPairCache()->setOverlapFilterCallback(filterCallback);


	return p_bullet;

}

