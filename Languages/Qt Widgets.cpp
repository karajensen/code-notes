
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT WIDGETS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QWidget
// If no parent, window for widgets based applications (non-QML), else base class for widgets
// Inherits QObject and QPaintDevice, inherited by QOpenGLWidget and QWidget components (eg. QLabel)
// 'Native' Widgets are a toplevel window, QGLWidget, or has had winId() called to create a WId
QWidget widget;
widget.acceptDrops // Whether dropping is enabled
widget.baseSize // QSize
widget.childrenRect // QRect of the children (excluding hidden)
widget.childrenRegion // QRegion of the children (excluding hidden)
widget.contextMenuPolicy // Qt::ContextMenuPolicy, how the widget shows a context menu
widget.cursor // QCursor
widget.enabled
widget.focus // readonly
widget.focusPolicy // Qt::FocusPolicy
widget.font // QFont
widget.frameGeometry // QRect geometry of the window including its window frame
widget.frameSize // QSize geometry of window including parents including window frame
widget.fullScreen // Whether fullscreen window mode
widget.geometry // QRect geometry of window excluding window frame
widget.height / widget.width
widget.inputMethodHints // Qt::InputMethodHints
widget.isActiveWindow // Whether this widget's window is the active window
widget.layoutDirection // Qt::LayoutDirection
widget.locale // QLocale, if not set will use parents or default locale
widget.maximized // Whether maximised window mode
widget.minimized // Whether minimized window mode
widget.maximumHeight / widget.minimumHeight
widget.maximumWidth / widget.minimumWidth
widget.maximumSize / widget.minimumSize // QSize
widget.minimumSizeHint // QSize recommended minimum size for the widget
widget.modal // whether the widget is a modal widget
widget.mouseTracking // default false, same as hoverEnabled
widget.normalGeometry // QRect used when not maximized or full screen, empty for child widgets
widget.palette // QPalette
widget.pos // QPoint
widget.rect // QRect without window frame
widget.size // QSize without window frame
widget.sizeHint // QSize recommended size for the widget
widget.sizeIncrement // QSize to increment window when resizing
widget.sizePolicy // QSizePolicy
widget.statusTip // QString
widget.styleSheet // QString
widget.toolTip // QString
widget.toolTipDuration // ms display time, -1 (default) auto calculates based on length
widget.updatesEnabled // Whether to prevent update/repaint calls, to help prevent flickering when resizing
widget.visible
widget.whatsThis // QString What's This help text
widget.filePath // the file name this window is representing
widget.windowFlags // Qt::WindowFlags
widget.windowIcon // QIcon
widget.windowModality // Qt::WindowModality
widget.windowModified // Whether the document shown in the window has unsaved changes
widget.windowOpacity // [0.0, 1.0]
widget.windowTitle // QString
widget.x / widget.y
widget.adjustSize() // Adjusts the size of the widget to fit its contents
widget.backgroundRole() / widget.setBackgroundRole() // QPalette::ColorRole
widget.forgroundRole() / widget.setForegroundRole() // QPalette::ColorRole
widget.backingStore() // Returns the QBackingStore* this widget will be drawn into
widget.childAt(x, y) // Returns QWidget*
widget.childAt(point) // Returns QWidget*, QPoint 
widget.clearFocus() // Takes keyboard input focus from the widget
widget.contentsMargins() // QMargins
widget.contentsRect() // QRect area inside the widget's margins
widget.ensurePolished() // Force update widget
widget.find(id) // Returns QWidget*, takes WId
widget.focusNextChild() // Force focus onto next in tab chain
widget.focusNextPrevChild() // Force focus onto previous in tab chain
widget.nextInFocusChain() // QWidget*
widget.previousInFocusChain() // QWidget*
widget.focusWidget() // QWidget* in focus
widget.fontInfo() // Returns QFontInfo for widget
widget.fontMetrics() // Returns QFontMetrics for widget
widget.getContentsMargins(left, top, right, bottom) // Takes int*
widget.grab(rect, size) // Render widget and children into optional rect/size, returns QPixmap
widget.grabKeyboard() / widget.releaseKeyboard() // Sets whether keyboard events all forced to window
widget.grabMouse() / widget.releaseMouse() // Sets whether mouse events all forced to window
widget.isAncestorOf(child) // Whether a parent of QWidget* child
widget.isEnabledTo(ancestor) // if this widget would become enabled if ancestor is enabled
widget.isHidden() // Not the same as !isVisible(), can be hidden if parent is hidden etc.
widget.isEnabledTo(ancestor) // if this widget would become enabled if ancestor is enabled
widget.isVisibleTo(ancestor) // if this widget would become visible if ancestor is shown
widget.isWindow() // Returns true if the widget is an independent window
widget.layout() // Returns QLayout*
widget.lower() // Lower the window below other windows
widget.raise() // Raise the window above other windows
widget.mapFromGlobal(pos) // Global QPoint screen coord to window QPoint coord
widget.mapFrom(parent, pos) // QPoint pos in QWidget parent coord to window QPoint coord, must be a parent
widget.mapFromParent(pos) // QPoint pos in QWidget parent coord to window QPoint coord
widget.mapTo(parent, pos) // Window QPoint coord to QWidget parent coord, must be a parent
widget.mapToParent(pos) // Window QPoint coord to QWidget parent coord
widget.mapToGlobal(pos) // Window QPoint coord to Global QPoint screen coord
widget.parentWidget() // Returns QWidget*
widget.repaint() // Force render the widget
widget.resize(w, h) // Resize the widget
widget.actions() // QList<QAction*> of actions0assigned to this widget
widget.addAction(action) // Assign QAction* to this widget, ownership not transferred
widget.addActions(actions) // Assign QList<QAction*> to this widget, ownership not transferred    
widget.insertAction(before, action) // Insert QAction* before QAction*
widget.insertActions(before, actions) // Insert QList<QAction*> before QAction*
widget.removeAction(action) // QAction*
widget.restoreGeometry(geometry) // QByteArray
widget.saveGeometry() // QByteArray
widget.scroll(dx, dy) // Scrolls widget including children, can be negative values
widget.setFocus(reason) // Qt::FocusReason optional
widget.setHidden(hidden) // setVisible(!hidden)
widget.setLayout(layout) // QLayout*, will take ownership
widget.setWindowFlag(flag, on) // Sets Qt::WindowType flag to on/off
widget.windowState() / widget.setWindowState(state) // Qt::WindowState
widget.hide() // Hides the window
widget.show() // Shows the window
widget.showFullScreen() // Shows the window as fullscreen
widget.showMaximized() // Shows the window as maximised
widget.showMinimized() // Shows the window as minimised
widget.showNormal() // Shows the window as default state based on platform
widget.close()
widget.stackUnder(widget) // Places under widget in parent's stack. Must be siblings
widget.underMouse() // Whether mouse hovered
widget.effectiveWinId() // WId platform id of first native widget, may change
widget.id() // WId platform id, may change, if non-native widget, will create an id
widget.window() // Returns QWidget* for widget's window (or itself if a window)
widget.windowHandle() // Returns QWindow* if a toplevel window, QGLWidget, or has had winId called
QWidget::setTabOrder(first, second) // QWidget*, QWidget*

// QMainWindow
// Inherits QWidget, must have a central widget set
QMainWindow window;
window.animated // Whether docking/tool bars are animated
window.dockOptions // QMainWindow::DockOption / QMainWindow::DockOptions
window.documentMode // Whether tab bar for tabbed dockwidgets is set to document mode
window.iconSize // QSize
window.tabShape // QTabWidget::TabShape
window.toolButtonStyle // Qt::ToolButtonStyle
window.addDockWidget(area, widget, orientation) // Qt::DockWidgetArea, QDockWidget*, Qt::Orientation
window.addToolBar(area, toolbar) // Qt::ToolBarArea, QToolBar*
window.addToolBar(title) // returns QToolBar* parented to window
window.centralWidget() // returns QWidget*
window.corner(corner) // returns Qt::DockWidgetArea for Qt::Corner
window.createPopupMenu() // returns QMenu*, ownership transfers to caller
window.dockWidgetArea(widget) // returns Qt::DockWidgetArea for QDockWidget*
window.insertToolBar(before, toolbar) // QToolBar*
window.menuBar() // returns main QMenuBar*, creates and returns if does not exist
window.menuWidget() // returns main QWidget*, returns null if does not exist
window.removeDockWidget(widget) // remove QDockWidget*
window.removeToolBar(toolbar) // remove QToolBar*
window.resizeDocks(docks, sizes, orientation) // QList<QDockWidget*>, QList<int>, Qt::Orientation
window.restoreState(state) // const QByteArray&
window.saveState() // QByteArray
window.setCentralWidget(widget) // QWidget*, takes ownership
window.setCorner(corner, area) // Qt::Corner, Qt::DockWidgetArea
window.setMenuBar(menuBar) // QMenuBar*, takes ownership
window.setMenuWidget(menuBar) // QWidget*, takes ownership
window.setStatusBar(statusbar) // QStatusBar*, takes ownership
window.setTabPosition(areas, tabPosition) // Qt::DockWidgetAreas, QTabWidget::TabPosition
window.statusBar() // returns QStatusBar*, creates and returns if does not exist
window.tabPosition(area) // returns QTabWidget::TabPosition, takes Qt::DockWidgetArea
window.takeCentralWidget() // removes and returns QWidget*, transfers ownership to caller
window.toolBarArea(toolbar) // Returns Qt::ToolBarArea, takes QToolBar*
    
// QOpenGLWidget
// Inherits QWidget but uses QOpenGLContext for rendering with OpenGL into a framebuffer object
QOpenGLWidget widget
widget.context() // returns QOpenGLContext*
widget.initializeGL() // Reimplement this to initialize any needed resources
widget.paintGL() // Reimplement this for when the widget needs to be rendered
widget.resizeGL(w, h) // Reimplement this for when the widget needs to be resized   

// QLabel
QLabel lbl("Message") // Allows use of html tags to customise text

// QPushButton
QPushButton btn("Text")
QObject::connect(button, SIGNAL(clicked()), fn)  // Connect to button's click event

// QSpinBox
QSpinBox spinbox
spinbox.setRange(min, max)
spinBox.setValue(value)
QObject::connect(spinBox, SIGNAL(valueChanged(int)), fn)

// QSlider 
QSlider slider(Qt::Horizontal)
slider.setRange(min, max)
slider.setValue(value)
QObject::connect(slider, SIGNAL(valueChanged(int)), fn)

// QHBoxLayout
// Lays out widgets horizontally from left to right
QHBoxLayout layout
layout.addWidget(spinBox) // Add a widget to the layout, automatically parents and resizes

// QVBoxLayout
// Lays out widgets vertically from top to bottom
QVBoxLayout layout
layout.addWidget(spinBox) // Add a widget to the layout, automatically parents and resizes

// QGridLayout
// Lays out widgets in a grid.
QGridLayout layout
layout.addWidget(spinBox, r, c) // Add a widget to the layout, automatically parents and resizes
