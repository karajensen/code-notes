from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyQt4 import uic
import os, sys, sip

uiFile = os.path.join(os.path.dirname(__file__),"fileReader_1.ui")
    
windowTitle = "File Reader"
windowObject = "fileReaderWin"

def getMayaWindow():
    import maya.OpenMayaUI as mui
    #Get the maya main window as a QMainWindow instance
    ptr = mui.MQtUtil.mainWindow()
    return sip.wrapinstance(long(ptr), QObject)

class FileReaderWin(QMainWindow):
    def __init__(self, parent=None, startDir="", runIn="python"):
        """Super, loadUi, signal connections"""
        super(FileReaderWin, self).__init__(parent)
        
        self.runIn = runIn
        
        if not startDir:
            startDir = os.path.dirname(__file__)
            
        self.mainWidget = QWidget()
        
        #Connects the ui elements to self
        uic.loadUi(uiFile, self)
        
        self.mainWidget = QWidget()
        self.setCentralWidget(self.mainWidget)
        
        self.setObjectName(windowObject)
        self.setWindowTitle(windowTitle)
        
        self.mainWidget.setLayout(self.gridLayout)
        
        self.browse_pb.clicked.connect(self.folderBrowse)
        self.folder_le.editingFinished.connect(self.fillList)
        self.files_lw.currentItemChanged.connect(self.fillTextBrowser)
        self.files_lw_folder.itemDoubleClicked.connect(self.changeFolder)
        
        self.folder_le.setText(startDir)
        self.fillList()
        
    def folderBrowse(self):
        folderName = ""

        if self.runIn == "python":
            fileDialog = QFileDialog()
            folderName = fileDialog.getExistingDirectory(None, "Select Folder", self.folder_le.text())
        
        elif self.runIn == "maya":
            import maya.cmds as cmds
            folderName = cmds.fileDialog2(fm=3, okc="Select Folder", dir=str(self.folder_le.text()))
            if folderName:
                folderName = folderName[0]
                
        if folderName:
            self.folder_le.setText(folderName)
            self.fillList()

    def changeFolder(self,itemClicked):
        itemText = str(itemClicked.text())
        newFolder = str(self.folder_le.text())
        if itemText == ".." :
            newFolder = os.path.dirname(newFolder)
        else:
            newFolder = os.path.join(newFolder,itemText)

        if os.path.exists(newFolder):
            self.folder_le.setText(newFolder)
            self.fillList()
        else:
            self.files_lw.clear()
            self.files_lw.insertItem(0, "Folder Not Found")
            
    def fillList(self):
        self.files_lw.clear()
        self.files_lw_folder.clear()
        workFolder = str(self.folder_le.text())
        if os.path.exists(workFolder):
            contents = os.listdir(workFolder)
            contentsToUse = []
            foldersToUse = [".."]
            for obj in contents:
                if os.path.isfile(os.path.join(workFolder, obj)):
                    contentsToUse.append(obj)
                else:
                    foldersToUse.append(obj)
            self.files_lw.insertItems(0, contentsToUse)
            self.files_lw_folder.insertItems(1, foldersToUse)
        else:
            self.files_lw.insertItem(0, "Folder Not Found")
    
    def fillTextBrowser(self):
        try:
            curFile = os.path.join(str(self.folder_le.text()), str(self.files_lw.currentItem().text()))
        except AttributeError:
            self.files_tb.setPlainText("")
            return
            
        if os.path.exists(curFile):
            fObj = open(curFile, "r")
            data = fObj.read()
            fObj.close()
            self.files_tb.setPlainText(data)
    
def mayaRun(startDir="", runIn="maya"):
    import maya.cmds as cmds
    
    if cmds.window(windowObject, q=True, exists=True):
        cmds.deleteUI(windowObject)
    global gui
    gui = FileReaderWin(getMayaWindow(), startDir="", runIn=runIn)
    gui.show()
    
def run(startDir="", args=[], runIn="python"):
    app = QApplication(args)
    gui = FileReaderWin(startDir="", runIn=runIn)
    gui.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    run(startDir = "", args=sys.argv)
    
mayaRun()
