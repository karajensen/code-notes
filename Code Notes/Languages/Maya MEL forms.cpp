/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEL DIALOG
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SCENE MESSAGE
headsUpMessage "This is the message";

//CONFIRM DIALOG BOX
confirmDialog -title "The Title"
              -message "This is the message"
              -button "Title for button"
              -defaultButton "Title for button";  //sets button as default button

//PROMPT DIALOG BOX
string $myResult = `promptDialog 
    -message "message here" 
    -button "OK" 
    -button "CANCEL" 
    -defaultButton "OK" 
    -cancelButton "CANCEL" 
    -dismissString "Cancel"`;
if($myResult == "OK"){}

//SELECTION DIALOG BOX
string $myFiles[] = `fileDialog2 -fileMode 4`;  //returns a list of paths to files selected

//PROGRESS WINDOW
waitCursor -state on; //auto done for progress window
int $amount = 0;
progressWindow -title "Progress" -progress $amount -status "Completed: 0%" -isInterruptable true;
while(true)
{
    //do part of the operation
    if(`progressWindow -query -isCancelled`){ break; }
    $amount += 1;
    progressWindow -edit -progress $amount -status ("Completed: " +$amount+"%");
}
progressWindow -endProgress;

//PROGRESS BAR
string $progCtrl = `progressBar -maxValue 5 -width 300`;
button -label "Next step" -command ("progressBar -edit -step 1 " + $progCtrl);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WINDOWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if(`window -exists "MyWindow"`)
{ 
    windowPref -remove "MyWindow";    
    deleteUI -wnd "MyWindow"; 
}
window -title "My Title" -resizeToFitChildren false "MyWindow";
showWindow "MyWindow";
window -edit -width 200 -height 100 "MyWindow"; //resize to fix sizing issues 

//NAVIGATING LAYOUTS
//Newest window becomes default and recieves the layout until another is created
//Newest layout becomes default and recieves any components until moved back in the heirarchy
setParent ..;                 //move back one parent
setParent -menu "MyLayout"    //set as current layout

//===============================================================================================================
// ROW/COLUMN LAYOUTS
//===============================================================================================================
columnLayout -adjustableColumn true "MyColLyaout";//set the default layout
button;            
    rowLayout -numberOfColumns 2 "MyRowLayout"; //create new layout; rows must specify number of cols
    button;
setParent ..;  //move the default layout back one
button;

//===============================================================================================================
// GRID LAYOUTS
//===============================================================================================================
gridLayout -numberOfRowsColumns 2 2 -cellWidthHeight 60 50; //creates grid of 2x2
gridLayout -position "MyButton" 2  //places button in slot 2 (slots counted from base 1, across row, next row then across)

//===============================================================================================================
// FORM LAYOUT
//===============================================================================================================
//division number defines number of positions elements are snapped to (use 100 for percentage of form)
string $form = `formLayout -numberOfDivisions 100`; 
formLayout -edit 
           -attachForm "MyButton" "top" 0           //alliged with top of form
           -attachForm "MyButton" "left" 0          //alliged with left of form
           -attachForm "MyButton" "bottom" 0        //alliged with bottom of form
           -attachPosition "MyButton" "right" 0 50  //right edge placed 50% of width of form
           $form;

//===============================================================================================================
// FRAME LAYOUT
//===============================================================================================================
//consists of a label and collapse/expand button for children (can only have one child layout)
frameLayout -label "Settings" -borderStyle "etchedIn" -font "obliqueLabelFont"-collapsable true;
    columnLayout;
        button;

//===============================================================================================================
// TAB LAYOUT
//===============================================================================================================
//organises layouts into folders allowing tabbing between them
//All children must be layouts
string $tabLay = `tabLayout`;
    string $colLay = `columnLayout`;
        button;
setParent ..; //move to working with tablayout again
    string $colLay2 = `columnLayout`;
        button;
setParent ..;

tabLayout -edit
          -tabLabel $colLay "MyTab1"
          -tabLabel $colLay2 "MyTab2"
          $tabLay;

//===============================================================================================================
// SCROLL LAYOUT
//===============================================================================================================
//displays scroll bars for a child layout
scrollLayout;
    columnLayout;
        button;
        button;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MENU BARS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//MENU BAR LAYOUT (FOR MAIN FORM)
menuBarLayout;
    menu -label "File";
        menuItem -label "Exit";
    menu -label "Help" -helpMenu true;
        menuItem -label "About";

//MENU BAR LAYOUT (INSIDE ANOTHER LAYOUT)
string $TabLay = `tabLayout`;
string $MenuLay = `menuBarLayout`;
    menu -label "Colors";
        menuItem -label "Red";
        menuItem -label "Green";
tabLayout -edit- -tabLabel $TabLay "Tabname" $MenuLay;

//MENU BAR (FOR MAIN FORM ALTERNATIVE)
window -menuBar true;
    menu -label "File" -tearOff true;
        menuItem -label "New";
        menuItem -divider true;    //divider
        menuItem -label "Exit";
    menu -label "Help" -helpMenu true;
        menuItem -label "About";
        menultem -label "Save Changes" -checkBox on;    //check box
    menu -label "Options" -allowOptionBoxes true;        //option tick boxes
        radioMenultemCollection ;
        menuItem -label "One" -radioButton off;
        menuItem -label "Two" -radioButton on;
        menultem -subMenu true -label "More Options";    //submenus
            menuItem -label "Three";                    //Option box created for label Three
            menuItem -optionBox true -command "ThreeOptionFunction()";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONTROLS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

separator;
helpline; //creates box that displays annotation when a control is hovered over
control -edit -width 23 $controlName;
control -query -parent $controlName;
control -exists $controlName;

//CONNECTING ATTRIBUTES TO CONTROLS
connectControl $myControl "MyObj.attr";
connectControl -index 2 $myControlGroup "MyObj.attr";

//COMMON CONTROL OPTIONS
-l "MyLbl"           // Text displayed
-w 20                // Width
-h 20                // Height
-annotation "Txt";   // Pop-up help text, can use with helpline

// COMMON COMMANDS
-c "MyFn()"                                   // Execute function
-c "MyFn(`textField -q -tx \"MyTextField\"`)" // Execute function with arguments
-c "melCommand;"                              // Execute mel command

// BUTTONS
button "MyButton";
symbolButton -image "sphere.xpm" "MyButton";
iconTextButton -style "iconAndTextHorizontal" -image1 "cone.xpm" "MyButton";

// CHECKBOXES
checkBox -value true "MyCheckBox";
symbolCheckBox -image "circle.xpm" "MyCheckBox";
iconTextCheckBox -style "iconAndTextVertical" -imagel "cube.xpm" "MyCheckBox";

//RADIO BUTTONS (allows one choice from group)
radioCollection;
    radioButton -label "One";
    radioButton -label "Two";
radioCollection -query -select $radioCollectionName; //finds out which one is selected
iconTextRadioCollection;
    iconTextRadioButton -image1 "sphere.xpm" -label "Sphere";
    iconTextRadioButton -image1 "cone.xpm" -label "Cone";

//LISTS
//Lists are base-1 indexed
textScrollList -numberOfRows 3    
               -allowMultiSelection true
               -append "One"
               -append "Two"
               -append "Three"
               -selectedItem "One"
               -showIndexedItem 3;
textScrollList -query -selectIndexedItem &myList //array of selected indices    

//TEXT
text;
textField -tx "Text" -editable true;
scrollField -wordWrap true -tx "Text" -font boldLabelFont -editable true;
scrollField -query -text $myScrollField;    //gets text

//VALUE FIELD
intField -v 12 "myIntField";   
floatField -v 12.0 "myFltField";
$intFieldValue = `intField -query -v "myIntField"`;

//FLOAT3/INT3 GROUPS
floatFieldGrp -numberOfFields 3 "ff00"; 
floatSliderGrp -value 76 
               -field true 
               -minValue -10.0 
               -maxValue 100.0
               -fieldMinValue -100.0 
               -fieldMaxValue 100.0;

//ATTRIBUTE GROUPS
attrFieldSliderGrp -min 0 -max 10 -at "mySphere.sx";
attrFieldGrp -attribute "MyObj.scale"; //holds attributes children (x,y,z)
attrColorSliderGrp -attribute "MyObj.color";
attrNavigationControlGrp -attribute "MyObj.scale"; //allows connection of attribute

//COLOR SLIDER
colorSliderGrp -cw1 5 "MyColorSlider";
colorIndexSliderGrp;

//TEXT FIELD BUTTON GROUP
textFieldButtonGrp -text "some text"
                   -buttonLabel "Check Spelling"
                   -buttonCommand "DoSomething()";

//NAME GROUP
nameField -object $myObject    //allows changing of object's name

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMAGES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//GET IMAGE DIRECTORY
//Initially searches for images in users bitmap directory and maya_install\icons
string $BitmapDirectory = `internalVar -userBitmapsDir`;

//SHOW PICTURE
picture -image "sphere.xpm";

//GLOBAL VAR HOLDING SUPPORTED IMAGE EXTENSIONS
global string $imgExt[];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PANELS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CURRENT VIEWPORT
panelLayout;
    modelPanel;    

//CURRENT VIEWPORT/OUTLINER
panelLayout -configuration "vertical2";
    outlinerPanel;
setParent ..;
    modelPanel;

//LIST OF PANELS
modelPanel;
outlinerPanel;
hardwareRenderPanel;
nodeOutliner;
spreadSheetEditor;
hyperPanel;

//USING PANELS
getPanel -all //get list of all panels
getPanel -underPointer //get name of panel under mouse
panel -edit -menuBarVisible true $panelName //display the menu bar
panel -copy $paneIName    //create a copy of the panel

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FILES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ABOUT
about -version;           //gives version of Maya as a float
about -operatingSystem;    

//FILE
file -rename ("name" + $counter + ".ma");
file -save -type ("mayaAscii");    //mayaAscii or mayaBinary
file -import "filepath"
file -force -options "" -typ "RealFlowSD" -es "filepath";    //export as specific type

string $filepath = `file -q -sceneName`;                //query the scene path and name
string $filename = `file -q -sceneName -shortName`;        //query the scene name
string $defaultSceneFolder = `workspace -rd -q`;        //query set project scene folder location

//PLUGINS
catch(`loadPlugin "C:/Program Files/Autodesk/Maya2011/bin/plug-ins/realflow.mll"`);

//REFERENCES
file -r -type "mayaBinary" -loadReferenceDepth "all" -namespace "Instance1" -options "v=0" "filepath";



