////////////////////////////////////////////////////////////////////////////////////////////
//UNITY SCRIPTS
////////////////////////////////////////////////////////////////////////////////////////////

using UnityEngine;
using System.Collections;

[System.Serializable] // Required for user-defined classes/structs to view in editor
public class MyData
{
    public int myInt; // Variables must be in pascal form for easy reading in editor
}

// Main script class
public class MyScript : MonoBehaviour
{
    public MyData data; // public members visible in editor and require drag-drop reference set
    private int myInt;  // private members not visible or set in editor

    // Initialise the script
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

////////////////////////////////////////////////////////////////////////////////////////////
//UNITY COMPONENTS
////////////////////////////////////////////////////////////////////////////////////////////

Debug.Log(myInt);  // Logs information to console window

// INPUT
Input.GetKey("space");      // Whether the key is currently being pressed/held
Input.GetKeyDown("space");  // Whether the key is held down this tick
Input.GetKeyUp("space");    // Whether the kkey is released this tick

// LIGHTING
Light myLight;
myLight.enabled = true;    // Sets whether the light is active or not


