from PyQt4 import QtGui
from PyQt4 import QtCore
import maya.cmds as cmds
import sip

windowTitle = "Scene Manip"
windowObject = "pySceneManipWin"

def getMainWindow():
    import maya.OpenMayaUI as mui
    pointer = mui.MQtUtil.mainWindow()
    return sip.wrapinstance(long(pointer), QtCore.QObject)

class SceneManipWin(QtGui.QMainWindow):
    def __init__(self, parent=None):
        super(SceneManipWin, self).__init__(parent)
        
        self.setObjectName(windowObject)
        self.setWindowTitle(windowTitle)
        
        self.mainWidget = QtGui.QWidget()
        self.setCentralWidget(self.mainWidget)
        
        #Building a layout
        self.gridLayout = QtGui.QGridLayout()
        self.mainWidget.setLayout(self.gridLayout)
        
        #Objects for our window
        self.label = QtGui.QLabel("Work Area")
        self.main_lw = QtGui.QListWidget()
        self.main_lw.setSelectionMode(QtGui.QAbstractItemView.ExtendedSelection)
        self.fillList_pb = QtGui.QPushButton("Fill List")
        self.clearList_pb = QtGui.QPushButton("Clear List")
        self.appendList_pb = QtGui.QPushButton("Append to List")
        self.removeList_pb = QtGui.QPushButton("Remove from List")
        self.sceneSelect_pb = QtGui.QPushButton("Select in Scene")
        self.sceneDelete_pb = QtGui.QPushButton("Delete in Scene")
        
        #Label layout setup
        self.labelLayout = QtGui.QHBoxLayout()
        self.labelLayout.addItem(QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum))
        self.labelLayout.addWidget(self.label)
        self.labelLayout.addItem(QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum))
        
        #Button Layout
        self.btnLayout = QtGui.QGridLayout()
        self.btnLayout.addWidget(self.fillList_pb, 0, 0)
        self.btnLayout.addWidget(self.clearList_pb, 0, 1)
        self.btnLayout.addWidget(self.appendList_pb, 1, 0)
        self.btnLayout.addWidget(self.removeList_pb, 1, 1)
        self.btnLayout.addWidget(self.sceneSelect_pb, 2, 0)
        self.btnLayout.addWidget(self.sceneDelete_pb, 2, 1)

        #Adding the objects into gridLayout
        self.gridLayout.addLayout(self.labelLayout, 0, 0, 1, 1)
        self.gridLayout.addWidget(self.main_lw, 1, 0, 1, 1)
        self.gridLayout.addLayout(self.btnLayout, 2, 0, 1, 1)
        
        #signals/slots
        self.fillList_pb.clicked.connect(self.fillList) 
        self.sceneSelect_pb.clicked.connect(self.selectInScene)
        self.clearList_pb.clicked.connect(self.clearList)
        self.appendList_pb.clicked.connect(self.appendList)
        self.removeList_pb.clicked.connect(self.removeList)
        self.sceneDelete_pb.clicked.connect(self.deleteInScene)
        self.main_lw.itemDoubleClicked.connect(self.focusOnNode)

    def focusOnNode(self,item):
        itemName = str(item.text())
        if cmds.objExists(itemName):
            cmds.select([itemName])
            cmds.FrameSelected(itemName)
        else:
            cmds.warning(itemName + " No longer exists")
            removedItem = self.main_lw.takeItem(self.main_lw.row(item))
            del removedItem

    def listHasSelectedMembers(self):                 
        if len(self.main_lw.selectedItems()) == 0:
            cmds.warning("Please select from the list first")
            return False
        return True

    def fillList(self):
        self.main_lw.clear()
        self.main_lw.addItems(cmds.ls(type='transform'))
        self.main_lw.sortItems()              

    def appendList(self):
        sel = cmds.ls(sl=True)
        if(len(sel) > 0):
            for item in sel:
                if not len(self.main_lw.findItems(item,QtCore.Qt.MatchExactly)):
                    self.main_lw.addItem(item)
            self.main_lw.sortItems()
        else:
            cmds.warning("Please select from the scene to append to list")

    def removeList(self):
        if self.listHasSelectedMembers():
            for item in self.main_lw.selectedItems():
                removedItem = self.main_lw.takeItem(self.main_lw.row(item))
                del removedItem

    def clearList(self):
        self.main_lw.clear()
        
    def selectInScene(self):
        if self.listHasSelectedMembers():
            toSel = []
            for item in self.main_lw.selectedItems():
                toSel.append(item.text())
            cmds.select(toSel)

    def deleteInScene(self):
        if self.listHasSelectedMembers():
            toSel = []
            for item in self.main_lw.selectedItems():
                toSel.append(item.text())
                removedItem = self.main_lw.takeItem(self.main_lw.row(item))
                del removedItem
            cmds.delete(toSel)

def mayaRun():
    if cmds.window(windowObject, q=True, exists=True):
        cmds.deleteUI(windowObject)
    global gui
    gui = SceneManipWin(getMainWindow())
    gui.show()
    
mayaRun()
