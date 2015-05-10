////////////////////////////////////////////////////////////////////////////////////////////
//UNITY SCRIPTS
////////////////////////////////////////////////////////////////////////////////////////////

using UnityEngine;
using UnityEditor; // For adding GUI items
using System.Collections;

// Main script class; name must match script filename
// Will not run unless attached to game object
// Members visible in editor require drag-drop reference set or are null
// Members visible in editor must be in pascal form for easy reading
public class MyScript : MonoBehaviour
{
    public int myInt;   // public members visible in editor
    private int myInt;  // private members not visible or set in editor
    public MyData data; // public class/structs not visible unless have System.Serializable attribute

    [Range(2,5)]       // Creates a slider in editor at range
    [HideInInspector]  // Hides public member from editor
    public int myInt; 

    [SerializeField]   // Force private member shown in editor
    private int myInt;

    // Initialise any variables
    void Awake()
    {
    }

    // Initialise any logic
    void Start()
    {
    }

    // Main tick function
    void Update()
    {
    }

    // Main physics tick function
    void FixedUpdate()
    {
    }
}

// CLASS ATTRIBUTES
[RequireComponent (typeof(Rigidbody))] // Enforces attached game object to have the required component
[System.Serializable]                  // Required for user-defined classes/structs to view in editor
public class MyData
{
}

////////////////////////////////////////////////////////////////////////////////////////////
//UNITY COMPONENTS
////////////////////////////////////////////////////////////////////////////////////////////

Debug.Log(myInt)                 // Logs a message to the console
Debug.LogError("Message")        // Logs an error to the console
InvokeRepeating("FnName", 1, 1)  // Requires class to have function with name, invokes once every second

// FINDING OBJECTS
GameObject.FindWithTag("Player")          // Finds component with tag, null if cannot be found, slow
GameObject.Find("Player")                 // Finds comonent with name, null if cannot be found, slow
GetComponent<RigidBody>()                 // Gets rigid body of object script is attached to
GetComponentsInChildren<ParticleSystem>() // Gets array of children of object script is attached to
Selection.activeTransform                 // returns transform of selected object
Selection.transforms                      // returns [] of all selected objects transforms

// MATHS
Mathf.PI          
Mathf.Epsilon
Mathf.Clamp
Mathf.Abs
Mathf.Lerp(a,b,t)       // Interpolates between a and b by t
Mathf.Atan2(y,x)        // Calculates tan(x/y), returns radians
Mathf.Rad2Deg           // Value used to convert radians to degrees
Mathf.Deg2Rad           // Value used to convert degrees to radianss
Mathf.PerlinNoise(x,y)  // Return noise value at position

// GAME OBJECTS
// Main base class for all objects
GameObject myGameObject
myGameObject.transform    // Gets the transform

// RIGID BODY
Rigidbody2D myRigidBody2D;
Rigidbody myRigidBody;
myRigidBody.AddForce(vec)      // Adds a Vector3 force to the body
myRigidBody.angularVelocity    // Sets/gets the angualar velocity

// VECTOR
Vector2 myVector;
Vector3 myVector;
Vector3.up            // Gets the up vector 0,1,0
myVector.Set(x,y,z);  // Sets the vector

// TRANSFORM
Transform myTransform
myTransform.position      // Gets the position as a Vector3 as a copy
myTransform.Rotate(vec)   // Rotates the transform by a Vector3
myTransform.eulerAngles   // Sets/gets the euler angles as a Vector3
myTransform.up            // Get up vector of transform

//QUATERNION
Quaternion myQuat;

// LIGHTING
Light myLight
myLight.enabled = true  // Sets whether the light is active or not

// PARTICLES
ParticleSystem myParticles
myParticles.Pause()         // Pauses the system
myParticles.Emit(100)       // Emits particles

// COLOUR
Color myColor

// RANDOM
Random.insideUnitSphere // Returns a random normalised Vector3
Random.Range(min, max)  // Retruns random between [min, max)

// BOUNDS
Bounds myBounds;
myBounds.extents

// RAYCAST
RaycastHit myRayCast;   // Filled by Physics.Raycast
myRayCast.point;        // Vector3 where the raycast hit
myRayCast.normal;       // normal of the surface that the raycast hit

// PHYSICS
Physics.Raycast(position, direction, out myRayCast); // raycasts using Vector3

// TIME
Time.time         // Gets the total time passed
Time.deltaTime    // Gets the time passed between ticks

// CAMERA
Camera.main.ScreenToWorldPoint(vec) // Converts a Vector2 screen position to Vector3 world point 

// INPUT
Input.GetMouseButtonDown(0) 
Input.mousePosition         // Returns the screen space mouse position
Input.GetKey("space")       // Whether the key is currently being pressed/held
Input.GetKeyDown("space")   // Whether the key is held down this tick
Input.GetKeyDown(KeyCode.E) // Whether the key is held down this tick
Input.GetKeyUp("space")     // Whether the key is released this tick

////////////////////////////////////////////////////////////////////////////////////////////
//UNITY GUI
////////////////////////////////////////////////////////////////////////////////////////////

public class GuiScript : MonoBehaviour
{
    // ADDING CONTEXT MENU ITEM TO COMPONENT
    // Adds item to object with the script rigid body component
    [MenuItem("CONTEXT/Rigidbody/Menu item name")]
    static void MenuItem(MenuCommand command)
    {
        RigidBody rb = (RigidBody)command.context; // do stuff with the component
    }

    // ADDING CONTEXT MENU ITEM TO SCRIPT
    [ContextMenu("Menu item name")]
    void MenuItem()
    {
    }

    // ADDING TOP MENU ITEM
    // Creates 'My Tools' in the top menu automatically
    [MenuItem("My Tools/Menu item name")]
    static void MenuItem()
    {
    }
}