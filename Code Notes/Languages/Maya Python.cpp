/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PYTHON FOR MAYA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// All python commands match MEL ones
import maya.cmds as cmds
from maya.OpenMaya import MVector

cmds.warning("Please select from the list first")
cmds.delete(listOfSelectionNames)
cmds.FrameSelected(objName) //zooms in on object in Maya scene

// Object creation
cmds.sphere(radius = 4)
cmds.polySphere(radius = 4)
cmds.shadingNode("file", asTexture = True)
cmds.shadingNode("bump2d", asUtility = True)

// Object Selection
cmds.objExists(objName) //returns if object exists in Maya scene
cmds.select(myMeshList) //select all meshes in list
cmds.select(listOfSelectionNames)
cmds.ls(sl = True) //return list of selected objects
cmds.ls(type = "geometryShape")

// Object Attributes
cmds.getAttr("MySphere.attribute")
cmds.setAttr("MySphere.attribute", value)
cmds.connectAttr(attr1,attr2,force=True)
cmds.listConnections(attr, destination=False) //get attribute connected to attr
cmds.listRelatives(myObj, type = "transform", parent = True)

// File output
cmds.file(filename, force=True, options="", typ="OBJexport", stx="never", es=True)

// Vectors
myVec = MVector(1.0, 0.2, 0.3)
myVec.x / myVec.y / myVec.z
myVec.length()
myVec.normal()
myVec ^ myVec2      // Cross product
myVec * myVec2      // Dot product

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PYQT FOR MAYA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Copy the PyQt4 folder, and the sip.pyd file from your python26/lib/site-packages 
//directory into the Maya install /python/lib/site-packages directory.

from PyQt4 import QtGui // uses namespace for access
from PyQt4 import QtCore // uses namespace for access
from PyQt4.QtCore import * // doesn't use namespace
from PyQt4.QtGui import * // doesn't use namespace
import maya.cmds as cmds
import sip

windowTitle = "My Window Name"
windowObject = "pyMyTitle_kpj"

//CREATE WINDOW
class MyWindow(QMainWindow):

    //##
    //# Constructor
    //# @param the parent of this window
    def __init__(self, parent=None):

        super(MyWindow, self).__init__(parent)

        //Load the designer UI file
        uic.loadUi(uiFile, self)

        //Setup the main widget
        self.setObjectName(windowObject)
        self.setWindowTitle(windowTitle)
        self.setFocusPolicy(QtCore.Qt.StrongFocus)
        self.mainWidget = QtGui.QWidget()
        self.setCentralWidget(self.mainWidget)
        self.mainWidget.setLayout(self.gridLayout)

        self.resize(575, 560)
        self.setMinimumWidth(575)
        self.setMaximumWidth(575)
        self.setMinimumHeight(150)

        //Main window status bar
        self.statusBar().showMessage("Message to show", timeInMsToShowMessage)

        //Buttons
        self.myButton.clicked.connect(self.myFunction)

        //Line Edit/Labels
        self.myLineEdit.setText("Some Text")
        self.myLabel.setText("Some Text")
        self.myLabel.text() //returns Qstring with text
        self.myLineEdit.text() //returns Qstring with texts

        //List Widgets
        self.myListWidget.itemDoubleClicked.connect(self.focusOnNode)
        self.myListWidget.currentItemChanged.connect(self.listViewChanged)
        self.myListWidget.count()
        self.myListWidget.item(1) //return QListWidgetItem at row 1
        self.myListWidget.findItems("myItem",Qt.MatchExactly) //returns list of items
        self.myListWidget.selectedItems() //returns list of selected items
        self.myListWidget.setSelectionMode(QtGui.QAbstractItemView.ExtendedSelection) //allows multiple selection
        self.myListWidget.sortItems() //sorts in descending alphabetical order
        self.myListWidget.addItems(["item1","item2"])
        self.myListWidget.clear()
        self.myListWidget.takeItem(row) //removes item from row, need to use del removedItem
        self.myListWidget.row(item) //takes QListWidgetItem returns row it's in

        //Custom context menu (right mouse click menu)
        self.myListWidget.setContextMenuPolicy(Qt.CustomContextMenu)
        self.myListWidget.customContextMenuRequested.connect(self.rightClickMenu)
        
        //List Widget Items
        self.myListView.item(1).text()
        self.myListView.item(1).setBackgroundColor(QColor(r,g,b,a)) //0->255

        //Spacer Items
        QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)

        //Combo Boxes
        self.myComboBox.clear()
        self.myComboBox.activated.connect(self.comboBoxChange)
        self.myComboBox.addItems(["item1","item2"])
        index = self.myComboBox.findText("item1") //returns index item is at
        self.myComboBox.setCurrentIndex(index) //set selected index

        //Check Boxes
        self.myCheckBox.isChecked()
        self.myCheckBox.setChecked(False)
        self.myCheckBox.stateChanged.connect(self.checkBoxChanged)

        //Spin Boxes
        self.mySpinBox.value()
        self.mySpinBox.setSingleStep(0.05) 
        self.mySpinBox.setValue(0.0)
        self.mySpinBox.valueChanged.connect(self.spinBoxChanged)
        self.mySpinBox.editingFinished.connect(self.spinBoxEditingFinished)
        self.mySpinBox.lineEdit().textEdited.connect(self.spinBoxEditText)
        self.mySpinBox.lineEdit().isEditingText = False

        //Script jobs
        self.scriptJobs = []
        self.scriptJobs.append(cmds.scriptJob(kws=True, event=["Undo",self.fillSceneList]))
        self.scriptJobs.append(cmds.scriptJob(kws=True, event=["Redo",self.fillSceneList]))
        self.scriptJobs.append(cmds.scriptJob(kws=True, event=["DagObjectCreated",self.fillSceneList]))
        self.scriptJobs.append(cmds.scriptJob(kws=True, event=["NameChanged",self.fillSceneList]))

        self.isSetup = 1


    //##
    //# Toggles whether the spin box is currently being edited
    def spinBoxEditText(self):
        self.sender().isEditingText = True

    //##
    //# On loss of focus or return of a spin box
    def spinBoxEditingFinished(self):
        self.sender().lineEdit().isEditingText = False
        self.myMethod()

    //##
    //# On value change of spin box
    def spinBoxChanged(self):    
        if not self.sender().lineEdit().isEditingText:
            self.myMethod()

    //##
    //# On change of selected combo box item
    //# check for user change as called when value changed in code as well
    def comboBoxChange(self):
        if self.sender().keyPressed:
            self.myMethod()

    //##
    //# On change of selected list view item
    //# Change the background colour so when out of focus its still selected
    def listViewChanged(self,item):
        if type(item) is type(QtGui.QListWidgetItem()):
            for i in range(self.myListView.count()):
                    self.myListView.item(i).setBackgroundColor(QColor(0,0,0,0))
            selItems = self.myListView.findItems(item.text(), Qt.MatchExactly)
            if len(selItems) != 0:
                selItems[0].setBackgroundColor(QColor(103,141,178))

    //##
    //# @return all meshes in the scene
    def getScene(self):
        scene = cmds.ls(type="geometryShape")
        if len(scene) > 0:
            return cmds.listRelatives(scene,type="transform",parent=True)
        return scene

    //##
    //# Saves each mesh in the scene as an obj
    def saveMeshesAsOBJ(self):
        scene = self.getScene()
        for mesh in scene:
            filename = os.path.join(self.meshesFolder,mesh+".obj")
            cmds.file(filename, force=True, options="", typ="OBJexport", stx="never", es=True)
        files = os.listdir(self.meshesFolder)
        for f in files:
            if self.isValidImage(f) or self.hasExtension(f,"mtl"):
                os.remove(os.path.join(self.meshesFolder,f))

    //##
    //# On close of the main window
    def closeEvent(self, event): 
        if hasattr(self, "isSetup"):
            if self.isSetup == 1:
                self.isSetup = 0
                self.deleteScriptJobs(self.scriptJobs)
                self.scriptJobs = []
                QMainWindow.closeEvent(self, event)

    //##
    //# Force kills script jobs in Maya
    //# @param list of script job numbers to delete
    def deleteScriptJobs(self,jobList):
        if len(jobList) > 0:
            for job in jobList:
                try:
                    if cmds.scriptJob(exists=job) == True:
                        cmds.scriptJob(kill=job)
                except RuntimeError as err:
                    pass

    //##
    //# Opens a custom dialog
    def openDialog(self):
        self.dialog = DialogBox(self)
        self.dialog.accepted.connect(lambda: self.chosenPath = self.dialog.chosenPath)
        self.dialog.open()

    //##
    //# On key press event
    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Escape:
            self.close()
        if event.key() == Qt.Key_A:
            print "A"     
        if event.key() == Qt.Key_Z:
            print "Z" 
        super(CombinedWin, self).keyPressEvent(event)

    //##
    //# On right mouse click
    def rightClickMenu(self, pos):
        newPos = QPoint(pos.x(), pos.y())
        menu = QMenu()        
        menu.addAction("Button1", self.method1)
        menu.addSeparator()
        menu.addAction("Button2", self.method2)
        menu.exec_(self.sender().mapToGlobal(newPos))

    //##
    //# Pops up a message box 
    def popUpMessageBox(self):
        mBox = QMessageBox()
        result = mBox.question(self, "Test for message box", buttons= mBox.Ok|mBox.Cancel)
        if result == mBox.Ok:
            pass

//CREATING CUSTOM WIDGET
//Class needs to be in extendedComboBox.py to use with designer promotion
from PyQt4 import QtGui
class ExtendedComboBox(QtGui.QComboBox):
    def __init__(self, parent=None):
        super(ExtendedComboBox, self).__init__(parent)
        self.keyPressed = False
    def mousePressEvent(self,e):
        self.keyPressed = True
        QtGui.QComboBox.mousePressEvent(self,e)
    def mouseReleaseEvent(self,e):
        self.keyPressed = False
        QtGui.QComboBox.mouseReleaseEvent(self,e)


//CREATING CUSTOM DIALOG BOX
uiDialog = os.path.join(os.path.dirname(__file__),"dialog.ui")
class DialogBox(QDialog):

    def __init__(self, parent):
        super(DialogBox, self).__init__(parent)
        uic.loadUi(uiDialog, self)
        self.CancelButton.clicked.connect(lambda: self.reject())
        self.AcceptButton.clicked.connect(lambda: self.accept())
        self.MyButton.clicked.connect(self.openFileBrowser)

    //##
    //# Opens a file browser to choose a file from
    def openFileBrowser(self):
         self.chosenPath = QFileDialog.getOpenFileName()


//TESTING WINDOW IN MAYA
def getMainWindow():
    import maya.OpenMayaUI as mui
    pointer = mui.MQtUtil.mainWindow()
    return sip.wrapinstance(long(pointer), QObject)

def runInMaya():
    if cmds.window(windowObject, exists=True):
        cmds.deleteUI(windowObject)
    global gui
    gui = MyWindow(getMainWindow())
    gui.show()

runInMaya()

//RUNNING STANDALONE
def run(startDir="", args=[], runIn="python"):
    app = QApplication(args)
    gui = MyWindow()
    gui.show()
    sys.exit(app.exec_())
