
proc SurfaceShatterSpecial(int $shardNo)
{
    string $myNewList[] = `ls -sl -tr`;
    string $shatName = $myNewList[0] + "s";
    surfaceShatter($shatName, $shardNo, 1, 1, 0, -0.1, 0, 0, 3, "shapes", 0, 1);
    
    //rename
    string $tempsel[] = `ls -sl -tr`;
    select -hi $tempsel[0];
    select -d $tempsel[0];
    string $shardSel[] = `ls -sl -tr`;    
    select -cl;
    string $shardName = $shatName + "s";
    for($t = 0; $t < size($shardSel); $t++)
    {
        select -r $shardSel[$t];
        polySoftEdge -a 0 -ch 0 $shardSel[$t];
    }
    select -cl;
    select $shardSel;   
    DeleteHistory;
    renameSelectionList($shardName);
    select -cl;
}
proc SolidShatterSpecial(int $shardNo)
{

    string $myNewList[] = `ls -sl -tr`;
    string $shatName = $myNewList[0] + "s";
    solidShatter($shatName, $shardNo, 0, 1, 0, 2, 1, 0, 3, "shapes", 0, 1);
    
    //rename
    string $tempsel[] = `ls -sl -tr`;
    select -hi $tempsel[0];
    select -d $tempsel[0];
    string $shardSel[] = `ls -sl -tr`;    
    select -cl;
    string $shardName = $shatName + "s";
    for($t = 0; $t < size($shardSel); $t++)
    {
        select -r $shardSel[$t];
        polySoftEdge -a 0 -ch 0 $shardSel[$t];
    }
    select -cl;
    select $shardSel;   
    DeleteHistory;
    renameSelectionList($shardName);
    select -cl;
}
proc SolidShatterSpecialGroup()
{
    string $sel[] = `ls -sl`;
    select -hi $sel[0];
    select -d $sel[0];
    string $myNewList[] = `ls -sl -tr`;
    select -cl;
    int $RandNo;
    
    for($i = 0; $i < size($myNewList); $i++)
    {
        select $myNewList[$i];
        string $shatName = $myNewList[$i] + "s";
        $RandNo = rand(2,4);
        solidShatter( $shatName, $RandNo, 0, 1, 0, 2, 1, 0, 3, "shapes", 0, 1);
        
        //rename
        string $tempsel[] = `ls -sl -tr`;
        select -hi $tempsel[0];
        select -d $tempsel[0];
        string $shardSel[] = `ls -sl -tr`;    
        select -cl;
        string $shardName = $shatName + "s";
        for($t = 0; $t < size($shardSel); $t++)
        {
            select -r $shardSel[$t];
            polySoftEdge -a 0 -ch 0 $shardSel[$t];
        }
        select -cl;
        select $shardSel;   
        DeleteHistory;
        renameSelectionList($shardName);
        select -cl;
    }
}

//CHECK WINDOW EXISTS
if(`window -exists SpecialShatter`)
{
    deleteUI -window SpecialShatter;    //deletes window if already exists in scene
}

//CREATE WINDOW
string $myUI = `window    -title "SpecialShatter"
                        -wh    128 256            //width/height
                        SpecialShatter`;            //name of window element

//CREATE WINDOW LAYOUT
rowColumnLayout -numberOfColumns 1
                -cw 1 60;            //1st column is 16 pixels wide

/*Row1*/ intField -v 3 "myIntField";
/*Row1*/ button    -label "Surface" -c ("SurfaceShatterSpecial(" + `intField -query -v "myIntField"` +")");    
/*Row2*/ button -label "Solid" -c ("SolidShatterSpecial(" + `intField -query -v "myIntField"` +")");    
/*Row2*/ button -label "Solid Group" -c "SolidShatterSpecialGroup()";

//SHOW THE WINDOW
showWindow $myUI;







