///////////////////////////////////////////////////////////////////////////////////////////////////////
//FACADE / ADAPTER PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Structural
USE: Wraps around another class, making it easier to use
	 FACADE: Used when a complicated class is needed to made simpler
	 ADAPTER: Used to wrap around unrelated classes
-------------------------------------------------------------------------------------------*/

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