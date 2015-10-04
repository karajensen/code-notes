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

    // Cleanup
    void OnDestroy()
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

// APPLICATION
// Levels must be added to the build to be used
Application.LoadLevel(0)        // Loads the level with build ID 0
Application.Quit()
Application.loadedLevel         // Gets the current loaded level

// SCRIPT OBJECTS
// Always attached to a game object
MyScript myScript;
myScript.gameObject;                        // Gets the object attached to
myScript = FindObjectOfType<MyScript>()      // Returns first instance of MyScript found

// GAME OBJECTS
// Main base class for all objects
// Each script inherits from Game Object attached to
// Destroyed between scenes unless specified not to
// Any references of the object when its destroyed automatically get set to null
GameObject myGameObject
GameObject.FindWithTag("Player")            // Finds component with tag, null if cannot be found, slow
GameObject.Find("Player")                   // Finds comonent with name, null if cannot be found, slow
GameOjbect.FindGameObjectWithTag("Player")  // Finds GameObject with tag
GameObject.FindGameObjectsWithTag("Player") // Finds GameObject[] with tage
GameObject.Instantiate(myObj)               // Creates a new instance based on the obj
GameObject.DontDestroyOnLoad(myGameObject)  // Don't destroy object between scenes
GameObject.Destroy(myGameObject)
myObj.transform                             // Gets the transform
myObj.transform.parent                      // Gets/Sets the gameobject parent
myObj.name                                  // Set/get the name
myObj.tag                                   // tag must exist or throws exception
myObj.SetActive(true)                       // Enables/disables the game object. All components/children are also disabled
myObj.activeSelf                            // Whether the object is enabled/disabled
myObj.GetComponent<RigidBody>()             // Gets rigid body of object
myObj.GetComponentsInChildren<Transform>()  // Gets array of children of object 
myObj.AddComponent<RigidBody>()             // Adds a component to the object
myObj.CompareTag("myTag")                   // Returns true if has this tag

// TRANSFORM
// Holds the parent-child hierarchy of gameobjects
Transform myTransform
myTransform.position                       // Gets the position as a Vector3 as a copy, use = new Vector3 to set
myTransform.localPosition
myTransform.localRotation                  // Get rotation of transform
myTransform.localScale                     // Get scale of transform
myTransform.Rotate(vec)                    // Rotates the transform by a Vector3
myTransform.eulerAngles                    // Sets/gets the euler angles as a Vector3
myTransform.up                            
myTransform.right
myTransform.forward
myTransform.parent;                        // Get/set the parent object
myTransform.gameObject;                    // Get the associated game object for the transform
myTransform.FindChild("MyChildGameObj");   // Gets the direct child with the given name

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
Vector3.zero
myVector.Set(x,y,z);    // Sets the vector

//QUATERNION
Quaternion myQuat;
Quaternion.identity

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

Animator myAnimator;
myAnimator.enabled                              // Set/get whether the animation is enabled
myAnimator.CrossFade("Base Layer.Entry", 0.0f); // switch animation states

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
myRenderer.enabled          // Enable/disable the sprite rendering
myRenderer.bounds.max       // Vector2 of max bounds position
myRenderer.bounds.min       // Vector2 of min bounds position

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

// RECT TRANSFORM
// Transform for a UI object
myRect.rect.width                               // Gets the width of the UI object
myRect.rect.height                              // Gets the height of the UI object
myRect.sizeDelta = new Vector2(with, height);   // Sets the width/height of the UI object

// UI TOGGLE
UnityEngine.UI.Toggle myToggle
myToggle.isOn               // Whether the tick is on/off

// UI IMAGE
UnityEngine.UI.Image myImage;
myimage.color = new Color(1.0f, 1.0f, 1.0f, 0.5f);

// UI TEXT
UnityEngine.UI.Text myText;
myText.text = "text";
myText.enabled = true;      // Enable/disable the text

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