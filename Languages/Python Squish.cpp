/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT STRINGS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//===============================================================================================================
// Test Case
//===============================================================================================================
 
# 'names' has map of Qt objects
# myObj = {"objectName": "cancel", "type": "QPushButton"}
import names
 
def init():
    # Test data saved is also in current working dir of exe
    # can also give full path
    # Moves from resources to working dir
    testData.put("filename.txt")
    
    # Reference directly testData
    path = findFile("testdata", "filename.txt")
    
def main():
    startApplication("appname")
    sendEvent("QMoveEvent", waitForObject(names.myObj), 0, 0, 0, 0)
    test.log("message")
    
    # Waiting
    snooze(4)
    waitForSignal(waitForObject(names.myObj), "windowTitleChanged(QString)")
    waitForObject(names.myObj)
    waitForObjectExists(names.myObj)
    waitForObjectItem(names.myObj, "name")
    waitFor(lambda: myBoolLamda(), 4000)
    
    # Use custom module
    import MyFile
    MyFile.fn()
    
    # Interaction
    clickButton(waitForObject(names.myObj))  # Buttons
    type(waitForObject(names.myObj), "text") # Text
    activateItem(waitForObject(names.myObj)) # Menus
    
    # Verification
    test.verify(waitForObject(names.myObj).visible)
    test.compare(waitForObject(names.myObj).visible, True)
    test.fail("message")
    test.passes("message")
    
def cleanup():
    testData.remove("filename.txt")
    
//===============================================================================================================
// MyFile.py
//===============================================================================================================
from squish import *
import test
import names
 
def fn():
    test.fixateResultContext()
    test.restoreResultContext()
