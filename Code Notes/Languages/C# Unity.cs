////////////////////////////////////////////////////////////////////////////////////////////
//UNITY SCRIPTS
////////////////////////////////////////////////////////////////////////////////////////////

// • Before Starting: Preferences -> Editor -> Visible Meta Files for Source Control
// • Statics are shared between scenes
// • GameObjects are destroyed between scenes (including statics) unless specified not to

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

    // Post tick function
    void LateUpdate()
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
GUILayout.Label("Message")       // Creates a message at the top corner of the game

// GAME OBJECTS
// Main base class for all objects
// Each script inherits from Game Object attached to
// Destroyed between scenes unless specified not to
GameObject myGameObject
GameObject.FindWithTag("Player")            // Finds component with tag, null if cannot be found, slow
GameObject.Find("Player")                   // Finds comonent with name, null if cannot be found, slow
GameOjbect.FindGameObjectWithTag("Player")  // Finds GameObject with tag
GameObject.FindGameObjectsWithTag("Player") // Finds GameObject[] with tage
GameObject.Instantiate(myObj)               // Creates a new instance based on the obj
myObj.transform                             // Gets the transform
myObj.name                                  // Set/get the name
myObj.GetComponent<RigidBody>()             // Gets rigid body of object
myObj.GetComponentsInChildren<Transform>()  // Gets array of children of object 
myObj.AddComponent<RigidBody>()             // Adds a component to the object
FindObjectOfType<MyScript>()                // Returns first instance of MyScript found
DontDestroyOnLoad(myGameObject)             // Don't destroy object between scenes

// SELECTION
Selection.activeTransform                   // returns transform of selected object
Selection.transforms                        // returns [] of all selected objects transforms

// MATHS
Mathf.PI          
Mathf.Epsilon
Mathf.Clamp(a, min, max)    // Clamps between two values
Mathf.Abs(a)                // Gets signed value from given value
Mathf.Lerp(a,b,t)           // Interpolates between a and b by t
Mathf.Atan2(y,x)            // Calculates tan(x/y), returns radians
Mathf.Rad2Deg               // Value used to convert radians to degrees
Mathf.Deg2Rad               // Value used to convert degrees to radianss
Mathf.PerlinNoise(x,y)      // Return noise value at position

// RIGID BODY
Rigidbody2D myRigidBody2D;
Rigidbody myRigidBody;
myRigidBody.AddForce(vec)      // Adds a Vector3 force to the body
myRigidBody.angularVelocity    // Sets/gets the angualar velocity

// VECTOR
Vector2 myVector;
Vector3 myVector;
Vector3.up              // Gets the up vector 0,1,0
Vector3.Distance(a, b)  // Gets the length between two vectors
Vector3.Dot(a, b)       // Dots both vectors
myVector.Set(x,y,z);    // Sets the vector

// TRANSFORM
Transform myTransform
myTransform.position      // Gets the position as a Vector3 as a copy, use = new Vector3 to set
myTransform.localRotation // Get rotation of transform
myTransform.localScale    // Get scale of transform
myTransform.Rotate(vec)   // Rotates the transform by a Vector3
myTransform.eulerAngles   // Sets/gets the euler angles as a Vector3
myTransform.up            // Get up vector of transform
myTransform.parent;       // Get/set the parent object
myTransform.gameObject;   // Get the associated game object for the transform

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

// TEXTURES
Texture2D myTex;
texture.name;                               // Set/get the name of the texture
texture.width;                              // Dimensions of the texture
texture.height;                             // Dimensions of the texture    
texture.GetPixels(0, 0, size, size)         // returns an array of pixels in dimensions
texture.GetPixels32();                      // returns an array of pixels
texture.SetPixels(0, 0, size, size, pixels) // sets an array of pixels
texture.SetPixels32(pixels);                // sets an array of pixels
texture.filterMode = FilterMode.Point       // sets the texture filter mode
texture.wrapMode = TextureWrapMode.Clamp    // sets the texture wrap mode
texture.Apply()                             // applys any pixel changes to the texture

// SPRITE RENDERER
SpriteRenderer myRenderer;
myRenderer.name             // Get/set the name of the renderer
myRenderer.color            // Get/set the tint colour of the sprite

// SPRITE OBJECT
Sprite mySprite;
Sprite.Create(myTexture, bounds, pivot, pixelsPerUnit); // bounds is Rect, pivot is Vector2 from 0->1 each component
mySprite.name;              // Set/get the name of the sprite
mySprite.pixelsPerUnit;     // Scale of texture dimensions to game dimensions

// AUDIO SOURCE
AudioSource myAudioSource;
myAudioSource.Stop()        // Stop playing
myAudioSource.Play()        // Start playing
myAudioSource.isPlaying     // Get whether the audio is playing or not
myAudioSource.volume        // Set/Get the volume

// TEXT
UnityEngine.UI.Text myText;
myText.text = "text";

////////////////////////////////////////////////////////////////////////////////////////////
//UNITY ALGORITHMS
////////////////////////////////////////////////////////////////////////////////////////////

// Get world scale of sprite
float scale = ((float)texture.width / sprite.pixelsPerUnit) * transform.localScale;


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