/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// MAXSCRIPT FORMS / UI
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

//===============================================================================================================
// CREATING A FLOATING WINDOW
//===============================================================================================================
if((myRollout != undefined) and (myRollout.isdisplayed)) do
(destroyDialog myRollout)

rollout myRollout "Name"
(
    //FORM ELEMENTS
    spinner mySpinner "Enter value: "
    button myButton "Button text"
    pickbutton myPicker "Pick object"

    //FORM LOCAL VARS
    local myVar

    //FORM FUNCTIONS
    fn myFunction =
    (
        //do something with local vars
    )

    //FORM EVENT HANDLERS
    on myButton pressed do  //event handler for myButton
    (
        value = mySpinner.value
        messagebox(value)
    )
    on myPicker picked obj do //obj is object picked
    (
        myVar += 10.0
        obj.pos.x += 10.0
    )
)
createDialog myRollout \    //name of form to create
             200 \          //width of form
             50             //height of form

//===============================================================================================================
// CREATING A SECTION IN THE UTILITIES PANEL
//===============================================================================================================
utility myUtility "Name"
(
    //Form events
    spinner mySpinner "Enter value: "
    button myButton "Button text"

    //Form local variables
    local myVar

    //Form event handlers
    on myButton pressed do  //event handler for myButton
    (
        myVar += 10.0
        value = mySpinner.value
        messagebox(value as string)
    )
)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// UI ELEMENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

//UI EVENT HANDLERS
on myElement pressed do () //when element is pressed
on myElement changed value do () //when element's value is changed
on myElement picked obj do ()  //when object is selected in scene
on myElement selected do () //when item in list/combo is selected
on myElement rickclick do () //when element is right clicked

//GROUPING ELEMENTS IN A PANEL
group "group description"
(
    //UI elements
)

//ELEMENT PROPERTIES
//All can be accessed through element: myElement.enabled = true
range:[1,10,3]  //from 1 to 10 with a default value of 3
type:#integer   //value type
enabled:false   //enable/disabled
fieldwidth: 40

//===============================================================================================================
// ELEMENT TYPES
//===============================================================================================================

//SPINNER (value with up/down arrows)
spinner mySpinner "Enter value: "

//BUTTON
button myButton "Button text"

//LABEL
label myLabel "Text"

//PROGRESS BAR
progressBar myProgress value:0  //from 0-100

//PICKBUTTON 
//allows select object in scene
pickbutton myPickButton "Text" autoDisplay:true //display name of picked obj

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// OPEN/SAVE DIALOGS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

myFileName = getOpenFileName caption:"select a file"
                             filename:"test.txt"
                             types:"Text(*.txt)|*.txt|All(*.*)|*.*|"

myFileName = getSaveFileName caption:"Save your file"
                             filename:"test.txt"
                             types:"Text(*.txt)|*.txt|All(*.*)|*.*|"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// FILES/INPUT/OUTPUT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

myFile = openFile "c:\\mypath"
myFile = createFile "c:\\mypath"
close myFile

//===============================================================================================================
// READING FROM FILES
//===============================================================================================================
readLine myFile
readChar myFile 2   //read two characters
while NOT eof myFile do readLine myFile     //read till end of file

//USING TAGS
skipToString myFile "$$MyTag" //looks from current pointer position
myValue = readValue myFile  //read value at tag
seek myFile 0   //move back to start if needed

//FILE POINTER
seek myFile 6
filePos myFile  //returns position pointer is at

//===============================================================================================================
// WRITING TO FILES
//===============================================================================================================

format "My Text %" myValue to:myFile    //similar to printf
format "My\n Text % %" myValue1 myValue2 to:myFile 

//===============================================================================================================
// WORKING WITH FILES
//===============================================================================================================

fileList = getFiles "c:\\*.max" //get all .max files in specific folder
directoryList = getDirectories "c:\\*"   //get array of all directions at path

fileList.count //returns number of files found

//Create directory
makeDir "c:\\myNewDir"

//Delete a file
deleteFile "c:\\myFile.txt"

//Rename a file
renameFile "c:\\myFile.txt" "c:\\renamedFile.txt"

//Copy a file
copyFile "c:\\myFile.txt" "c:\\copiedFile.txt"

//Delete a directory
DOSCommand "rd \"C:\MyDirectory\""

sysInfo.windowsdir  //windows install directory
sysInfo.systemdir   //windows system directory
sysInfo.tempdir     //windows temp directory
#startupScripts     //maxscript startup scripts directory
#scene              //3ds max scene directory
#maxroot            //main 3ds max executable directory
#matlib             //materials library directory
#scripts            //scripts directory
#image              //images directory
#ui                 //user interfaces directory
#userscripts        //user scripts directory
#usericons          //user icons directory

//Project path
mypath = pathConfig.getCurrentProjectFolder()

//===============================================================================================================
// IMPORT/EXPORTING
//===============================================================================================================

//List of import plugins
importerPlugin.classes

//Import a file; no prompt skips dialog windows
importFile "c:\\myFile.xxx" #noPrompt using:myPlugin

//Export a file
exportFile  "c:\\myFile.xxx" #noPrompt using:myPlugin

