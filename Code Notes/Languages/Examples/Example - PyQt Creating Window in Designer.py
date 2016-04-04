from PyQt4 import QtGui
from PyQt4 import QtCore
from PyQt4 import uic
import maya.cmds as cmds
import sip, os

uiFile = os.path.join(os.path.dirname(__file__), "PyQt - CreatingWindowInDesigner.ui")

windowTitle = "Scene Information Window"
windowObject = "pySceneInfoWin"
KEY = 0
VALUE = 1

def getMainWindow():
    import maya.OpenMayaUI as mui
    pointer = mui.MQtUtil.mainWindow()
    return sip.wrapinstance(long(pointer), QtCore.QObject)

class SceneInfoWin(QtGui.QMainWindow):
    def __init__(self, parent=None):
        super(SceneInfoWin, self).__init__(parent)
        
        #Loads the contents of the UI file into self
        uic.loadUi(uiFile, self)
        
        #Sets the objectName and windowTitle
        self.setObjectName(windowObject)
        self.setWindowTitle(windowTitle)

        self.attributes = {"Translation":[".translate",self.trans_cb], 
                           "Rotation":[".rotate",self.rot_cb], 
                           "Scale":[".scale",self.scale_cb]}

        self.formatOptions = {"Just Get":self.getPlainText, 
                              "Round":self.getRoundedText, 
                              "String Formatting":self.getFormattedText}
        
        #Creates a mainWidget to place into the mainWindow
        #Applies the mainGrid from the uiFile into that mainWidget
        self.mainWidget = QtGui.QWidget()
        self.setCentralWidget(self.mainWidget)
        self.mainWidget.setLayout(self.mainGrid)

        #signals/slots
        self.fillList_pb.clicked.connect(self.fillList)
        self.sceneSelect_pb.clicked.connect(self.selectInScene)
        self.main_lw.currentTextChanged.connect(self.infoFill)
        self.main_cb.currentIndexChanged.connect(self.infoFill)
        for att in self.attributes.values():
            att[1].stateChanged.connect(self.infoFill)

    #Checks if the box connected to the attribute is checked
    def boxIsChecked(func):
        def new_func(self,attribute,obj):
            if attribute[VALUE][1].isChecked():
                return func(self,attribute,obj)
            return ""
        return new_func

    @boxIsChecked
    def getPlainText(self,attribute,obj):
        return ("\n" + attribute[KEY] + " : " + str(cmds.getAttr(obj+attribute[VALUE][0])))

    @boxIsChecked
    def getRoundedText(self,attribute,obj):
        return ("\n" + attribute[KEY] + " : " + str([round(x, 10) for x in cmds.getAttr(obj+attribute[VALUE][0])[0]]))

    @boxIsChecked
    def getFormattedText(self,attribute,obj):   
        text = "\n" + attribute[KEY] + " : "
        for x in cmds.getAttr(obj+attribute[VALUE][0])[0]:
            text += "%.2f   " % x
        return text
     
    def infoFill(self):
        infoPrint = ""
        if self.main_lw.currentRow() >= 0:
            obj = str(self.main_lw.item(self.main_lw.currentRow()).text())
            infoPrint = "Object: " + obj + "\n"
            for item in self.formatOptions.items():
                if str(self.main_cb.currentText()) == item[KEY]:
                    for att in self.attributes.items():
                        infoPrint += item[VALUE](att,obj)
        self.info_tb.setPlainText(infoPrint)
        
    def fillList(self):
        self.main_lw.clear()
        sel = cmds.ls(sl=True)
        self.main_lw.addItems(sel)
        
    def selectInScene(self):
        toSel = []
        for item in self.main_lw.selectedItems():
            toSel.append( item.text() )
        cmds.select(toSel)
        
def mayaRun():
    if cmds.window(windowObject, q=True, exists=True):
        cmds.deleteUI(windowObject)
    global gui
    gui = SceneInfoWin(getMainWindow())
    gui.show()
    
mayaRun()
