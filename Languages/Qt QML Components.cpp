/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML COMPONENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QTOBJECT
// lightweight non-visual element
QtObject {
   objectName: "name"
}

// COMPONENT
// Instantiates QQmlComponent, Used for sourceComponent and contentItem properties
Component {
    Rectangle {
        signal mySignal(int value)
    }
}

// CONNECTIONS
// Access a signal outside of the object that emits it, required for Loader items
Connections {
    target: loader.item
    onMySignal: { value }
}

// BINDING
// Will become active and assign value to myProperty when myBoolean becomes true
// When active, will disable any direct bindings myProperty may have until myBoolean is false
Binding {
    target: item // required if not a child of item with property
    property: "myProperty" // can be QML basic type attribute (eg. "myRectProperty.x")
    when: myBoolean
    value: 10 // Can be value, another property etc
    delayed: true // wait until event queue cleared before assigning
}

// REPEATER
// Inherits Item, Usually in Row/Column, instantiates n items
// creates all of its delegate items when the repeater is first created
Repeater {
    id: repeater
    model: 3
    Text { text: "Item " + indeX + "/" + repeater.count }
}
Repeater {
    model: ["one", "two", "three"]
    Text { text: "Data: " + modelData }
}
Repeater {
    model: listView
    Text { text: "Data: " + modelData.role_name }
}

// STATEGROUP
// State support for non QML Item derived components, see Item for State {}
StateGroup {
    state: "state1" // QString state name, default empty
    states: [State { name: "state1" }, State { name: "state2" }]
}

// TIMER
// Triggers a handler at a specified interval
Timer {
    interval: 500 // milliseconds
    running: true
    repeat: true
    triggeredOnStart: true // default false, triggered signal emitted once extra on timer start
    onTriggered: {}
}
timer.restart()
timer.start()
timer.stop()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML WINDOWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
// WINDOW ATTACHED PROPERTIES
Item {
    Window.active
    Window.activeFocusItem
    Window.contentItem
    Window.height
    Window.visibility
    Window.width
    Window.window
    ApplicationWindow.activeFocusControl
    ApplicationWindow.contentItem
    ApplicationWindow.footer
    ApplicationWindow.header
    ApplicationWindow.menuBar
    ApplicationWindow.window
}
   
// WINDOW
// Instantiates QQuickWindow, Creates a new top-level window 
Window {
    active
    activeFocusItem
    color
    contentItem
    contentOrientation
    data
    flags
    height
    maximumHeight
    maximumWidth
    minimumHeight
    minimumWidth
    modality
    opacity
    screen
    title
    visibility
    visible
    width
    x
    y
    onClosing: {}
}
window.alert(msec)
window.close()
window.hide()
window.lower()
window.raise()
window.requestActivate()
window.show()
window.showFullScreen()
window.showMaximized()
window.showMinimized()
window.showNormal()

// APPLICATIONWINDOW
// Inherits Window, Styled top-level window
ApplicationWindow {
    activeFocusControl
    background
    contentData
    contentItem
    font
    footer
    header
    locale
    menuBar
    palette
}
   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML LAYOUTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LAYOUT ATTACHED PROPERTIES
// Use these on any components inside the layout
Layout.alignment // Layout Alignment Flags
Layout.bottomMargin // Overrides margin property if set
Layout.column // column position of an item in a GridLayout
Layout.columnSpan // column span of an item in a GridLayout
Layout.fillHeight // Uses preferredHeight if false
Layout.fillWidth // Uses preferredWidth if false
Layout.leftMargin // Overrides margin property if set
Layout.margins // Spacing between items
Layout.maximumHeight // Number.POSITIVE_INFINITY default
Layout.maximumWidth // Number.POSITIVE_INFINITY default
Layout.minimumHeight // 0 default
Layout.minimumWidth // 0 default
Layout.preferredHeight // if -1 (default), will be ignored, and item's implicitHeight used instead
Layout.preferredWidth // if -1 (default), will be ignored, and item's implicitWidth used instead
Layout.rightMargin // Overrides margin property if set
Layout.row // row position of an item in a GridLayout
Layout.rowSpan // row span of an item in a GridLayout
Layout.topMargin // Overrides margin property if set

// ROWLAYOUT
// Inherits Item, Aligns elements after each other in a single row
RowLayout {
    anchors.fill: parent // Still use anchors on base
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    spacing: 5 // default, spacing between each cell
}

// ROW
// Inherits Item, Positions its child items along a single row
Row {
    bottomPadding: 1.0 // padding around the content, overrides 'padding'
    leftPadding: 1.0 // padding around the content, overrides 'padding'
    rightPadding: 1.0 // padding around the content, overrides 'padding'
    topPadding: 1.0 // padding around the content, overrides 'padding'
    padding: 1.0 // padding around the content
    spacing: 0 // default, amount in pixels left empty between adjacent items
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    add: Transition {} // Effect to apply when items added/visibility changed
    move: Transition {} // Effect to apply when items move
    populate: Transition {} // Effect to apply when first populated with items
    onPositioningComplete: {} // When positioning has been completed
}
row.forceLayout() // Triggers an update instead of waiting for scheduled one

// COLUMNLAYOUT
// Inherits Item, Aligns elements after each other in a single column
ColumnLayout {
    anchors.fill: parent // Still use anchors on base
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    spacing: 5 // default, spacing between each cell
}

// COLUMN
// Inherits Item, Positions its child items along a single column
Column {
    bottomPadding: 1.0 // padding around the content, overrides 'padding'
    leftPadding: 1.0 // padding around the content, overrides 'padding'
    rightPadding: 1.0 // padding around the content, overrides 'padding'
    topPadding: 1.0 // padding around the content, overrides 'padding'
    padding: 1.0 // padding around the content
    spacing: 0 // default, amount in pixels left empty between adjacent items
    add: Transition {} // Effect to apply when items added/visibility changed
    move: Transition {} // Effect to apply when items move
    populate: Transition {} // Effect to apply when first populated with items
    onPositioningComplete: {} // When positioning has been completed
}
column.forceLayout() // Triggers an update instead of waiting for scheduled one

// GRIDLAYOUT
// Inherits Item, Aligns elements in a grid with n columns
GridLayout {
    anchors.fill: parent // Still use anchors on base
    columnSpacing: 5 // default, spacing between each column
    columns: 3 // column limit if flow is GridLayout.LeftToRight, default is no limit
    flow: <T>.LeftToRight // default, GridLayout Flow Enum, item wrapping with columns/rows properties
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    rowSpacing: 5 // default, spacing between each row
    rows: 3 // row limit if flow is GridLayout.LeftToRight, default is no limit
}

// GRID
// Inherits Item, Positions its child items in grid formation
Column {
    bottomPadding: 1.0 // padding around the content, overrides 'padding'
    leftPadding: 1.0 // padding around the content, overrides 'padding'
    rightPadding: 1.0 // padding around the content, overrides 'padding'
    topPadding: 1.0 // padding around the content, overrides 'padding'
    padding: 1.0 // padding around the content
    columnSpacing: 1 // default not set, spacing in pixels between columns
    columns: 4 // default, number of columns in grid
    flow: <T>.LeftToRight // default, Grid Flow Enum, item wrapping with columns/rows properties
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    rowSpacing: 1 // default not set, spacing in pixels between rows
    rows: 4 // default, number of rows in grid    
    spacing: 0 // default, amount in pixels left empty between adjacent items    
    add: Transition {} // Effect to apply when items added/visibility changed
    move: Transition {} // Effect to apply when items move
    populate: Transition {} // Effect to apply when first populated with items
    onPositioningComplete: {} // When positioning has been completed
}
grid.forceLayout() // Triggers an update instead of waiting for scheduled one

// FLOW
// Inherits Item, Positions its children side by side, wrapping as necessary
Flow {
    bottomPadding: 1.0 // padding around the content, overrides 'padding'
    leftPadding: 1.0 // padding around the content, overrides 'padding'
    rightPadding: 1.0 // padding around the content, overrides 'padding'
    topPadding: 1.0 // padding around the content, overrides 'padding'
    padding: 1.0 // padding around the content
    flow: <T>.LeftToRight // default, Grid Flow Enum, item wrapping with columns/rows properties
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    spacing: 0 // default, amount in pixels left empty between adjacent items    
    add: Transition {} // Effect to apply when items added/visibility changed
    move: Transition {} // Effect to apply when items move
    populate: Transition {} // Effect to apply when first populated with items    
    onPositioningComplete: {} // When positioning has been completed
}
flow.forceLayout() // Triggers an update instead of waiting for scheduled one

// Layout Alignment Flags
Qt.AlignLeft       Qt.AlignTop
Qt.AlignHCenter    Qt.AlignVCenter
Qt.AlignRight      Qt.AlignBottom
Qt.AlignBaseline

// Layout Direction Enum
Qt.LeftToRight
Qt.RightToLeft

// Flow / Grid / GridLayout Flow Enum
<T>.LeftToRight
<T>.TopToBottom
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML ACTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// ACTION
// Inherits QtObject, used in AbstractButton
Action {
    ActionGroup.group: myAction // Add the action to the group
    checkable: true // defaults false
    checked: true
    icon.width: 100 // maximum width of the icon
    icon.height: 100 // maximum height of the icon
    icon.color: "red" // tints with colour    
    icon.source: "qrc:///icon.png"
    text: "str"
    shortcut: StandardKey.Copy
    onTriggered: { source }
    onToggled: { source }
}
action.toggle(source) // Toggle the action/emit signal, source defaults to null
action.trigger(source) // Trigger the action/emit signal, source defaults to null

// ACTIONGROUP
// Inherits QtObject, Groups actions together
// Can add items as children, through ActionGroup.group attached property or addAction()
ActionGroup {
    Action { checkable: true } // Add action as children, 'checkable' required
    checkedAction: myAction // Currently selected/checked action
    enabled: true // False disables all actions, true enables except for those explicity disabled
    exclusive: true // Default true, if false checkedAction is always null
    onTriggered: { action } // When an action is triggered
}
group.actions // list<Action> of actions
group.addAction(myAction) // Add an action
group.removeAction(myAction) // Remove an action

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML CONTROLS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONTROL
// Inherits Item, base class for all controls
// Controls (except non-interactive indicators) do not let clicks/touches through to children
Control {
    bottomPadding: 1 // padding around the contentItem, overrides 'padding'
    leftPadding: 1 // padding around the contentItem, overrides 'padding'
    rightPadding: 1 // padding around the contentItem, overrides 'padding'
    topPadding: 1 // padding around the contentItem, overrides 'padding'
    padding: 1 // padding around the contentItem
    background: Rectangle {}
    contentItem: Label {} // Item automatically resized to fit within the padding of the control
    focusPolicy: Qt.NoFocus // Control Focus Policy Enum, the way the control accepts focus
    font: Qt.font() // QML font used
    hoverEnabled: true // Whether the control accepts hover events
    locale: Locale {} // Locale specific properties for formatting data and numbers
    mirrored: true // Whether the control is mirrored
    spacing: 1.0 // Spacing for control, each derived class uses it differently
    wheelEnabled: true // Whether the control handles wheel events, default false
}
control.availableHeight // Height available to the contentItem after deducting vertical padding
control.availableWidth // Width available to the contentItem after deducting horizontal padding
control.focusReason // Holds the reason of the last focus change, Input Focus Reason enum
control.hovered // Whether the control is hovered
control.palette // QML palette used for control, default application palette, changing also changes children
control.visualFocus // If has activefocus and with FocusReason Tab, Backtab or Shortcut

// Control Focus Policy Enum
Qt.TabFocus     // The control accepts focus by tabbing
Qt.ClickFocus   // The control accepts focus by clicking
Qt.StrongFocus  // The control accepts focus by both tabbing and clicking
Qt.WheelFocus   // The control accepts focus by tabbing, clicking, and using the mouse wheel
Qt.NoFocus      // The control does not accept focus

// COMBOBOX
// Inherits Control, Combined button and popup list for selecting options
ComboBox {
}

// SPINBOX
// Inherits Control, Allows the user to select from a set of preset values
SpinBox {
}

// DIAL
// Inherits Control, Circular dial that is rotated to set a value
Dial {
}

// BUSYINDICATOR
// Inherits Control, Indicates background activity
BusyIndicator {
}

// PROGRESSBAR
// Inherits Control, Indicates the progress of an operation
ProgressBar {
}

// SLIDER
// Inherits Control, Used to select a value by sliding a handle along a track
Slider {
}

// RANGESLIDER
// Inherits Control, Used to select a range of values by sliding two handles along a track
RangeSlider {
}

// TUMBLER
// Inherits Control, Spinnable wheel of items that can be selected
Tumbler {
}

// SCROLLBAR
// Inherits Control, Vertical or horizontal interactive scroll bar
ScrollBar {
    contentItem.opacity: 1 // Make always visible
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML BUTTONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ABSTRACTBUTTON
// Inherits Control, base class for all buttons
AbstractButton {
    text: "str"
    action: myAction
    autoExclusive: true // checkable btns with same parent auto-group, doesn't affect if part of ButtonGroup
    checkable: true // defaults false
    checked: true
    display: AbstractButton.IconOnly // Abstract Button Display Enum
    icon.width: 100 // maximum width of the icon
    icon.height: 100 // maximum height of the icon
    icon.color: "red" // tints with colour    
    icon.source: "qrc:///icon.png"
    onCanceled: {} // When loses mouse grab when pressed or not inside button when released emitted
    onClicked: {} // When button is clicked by user via touch, mouse or keyboard
    onDoubleClicked: {} // When button is double clicked by user via touch or mouse
    onPressAndHold: {} // When the button is pressed and held down by user via touch or mouse
    onPressed: {} // When button is pressed by user via touch, mouse, or keyboard
    onReleased: {} // When button is released by user via touch, mouse, or keyboard
    onToggled: {} // When checkable button is toggled by the user via touch, mouse, or keyboard
}
button.down // Whether button visually down
button.pressed // Read-only, whether button visually down
button.toggle() // Toggles the checked state of the button

// Abstract Button Display Enum
AbstractButton.IconOnly	
AbstractButton.TextOnly
AbstractButton.TextBesideIcon

// BUTTON
// Inherits AbstractButton
Button {
    autoRepeat: false // default, whether repeats pressed, released and clicked signals
    flat: false // default, whether draws a background when pressed or checked
}
btn.highlighted // Whether button is highlighted

// ROUNDBUTTON
// Inherits AbstractButton, Button with rounded corners
RoundButton {
}

// CHECKBOX
// Inherits AbstractButton
CheckBox {
}

// RADIOBUTTON
// Inherits AbstractButton, Exclusive radio button that can be toggled on or off
RadioButton {
}

// TABBUTTON
// Inherits AbstractButton, Button with a look suitable for a TabBar
TabButton {
}

// SWITCH
// Inherits AbstractButton, Switch button that can be toggled on or off
Switch {
}

// BUTTONGROUP
// Inherits QtObject, Mutually-exclusive group of checkable buttons
ButtonGroup {
}

// MENUITEM
// Inherits AbstractButton
MenuItem {
   menu: myMenu // Parent menu of the item
   subMenu: Menu {} // Submenu to show if a submenu
   onTriggered: {} // Emitted when the menu item is triggered by the user
}
menuItem.highlighted // Whether is highlighted by the user

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML CONTAINERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONTAINER
// Inherits Control, Abstract base class for some containers
Container {
}

// FLICKABLE
// Inherits Item, Provides a surface that can be "flicked"
Flickable {
    ScrollBar.vertical: ScrollBar { } // Add a vertical scrollbar
    ScrollBar.horizontal: ScrollBar { } // Add a horizontal scrollbar
    atXBeginning
    atXEnd
    atYBeginning
    atYEnd
    bottomMargin
    boundsBehavior
    boundsMovement
    contentHeight
    contentItem
    contentWidth
    contentX
    contentY
    dragging
    draggingHorizontally
    draggingVertically
    flickDeceleration
    flickableDirection
    flicking
    flickingHorizontally
    flickingVertically
    horizontalOvershoot
    horizontalVelocity
    interactive
    leftMargin
    maximumFlickVelocity
    moving
    movingHorizontally
    movingVertically
    originX
    originY
    pixelAligned
    pressDelay
    rebound
    rightMargin
    topMargin
    verticalOvershoot
    verticalVelocity
    visibleArea.xPosition
    visibleArea.widthRatio
    visibleArea.yPosition
    visibleArea.heightRatio
    onFlickEnded: {}
    onFlickStarted: {}
    onMovementEnded: {}
    onMovementStarted: {}
}
flick.cancelFlick()
flick.flick(xVelocity, yVelocity)
flick.resizeContent(width, height, center)
flick.returnToBounds()

// PANE
// Inherits Control, Provides a background matching with the application style and theme
Pane {
}

// FRAME
// Inherits Pane, Visual frame for a logical group of controls
Frame {
}

// SCROLLVIEW
// Inherits Control, Auto uses Flickable if child has one
ScrollView {
}

// SWIPEVIEW
// Inherits Container, Enables the user to navigate pages by swiping sideways
SwipeView {
}

// MENUBAR
// Inherits Container, Provides a window menu bar
MenuBar {
}

// TABBAR
// Inherits Container, Allows the user to switch between different views or subtasks
TabBar {
}

// TOOLBAR
// Inherits Pane, Container for context-sensitive controls
ToolBar {
}

// GROUPBOX
// Inherits Frame, Visual frame and title for a logical group of controls
GroupBox {
}

// SPLITVIEW
// No QML Controls 2 version
ControlsLegacy.SplitView {
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML POPUPS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// POPUP
// Inherits QtObject, base class for all popups
Popup {
    activeFocus: true // Read only, whether item has active focus
    background: Item {} // If no size set, auto follows the control's size, must set implicit sizes if using
    bottomMargin: -1 // default no margin
    leftMargin: -1 // default no margin
    rightMargin: -1 // default no margin
    topMargin: -1 // default no margin
    margins: -1 // default no margins
    bottomPadding: 1 // padding around the contentItem, overrides 'padding'
    leftPadding: 1 // padding around the contentItem, overrides 'padding'
    rightPadding: 1 // padding around the contentItem, overrides 'padding'
    topPadding: 1 // padding around the contentItem, overrides 'padding'
    padding: 1 // padding around the contentItem
    clip: false // default, whether clipping is enabled
    closePolicy: Popup.CloseOnEscape|Popup.CloseOnPressOutside // default, Popup Close Policy Enum
    contentChildren
    contentData
    contentHeight
    contentItem
    contentWidth
    dim
    enabled
    enter
    exit
    focus
    font
    implicitHeight
    implicitWidth
    locale
    mirrored
    modal
    opacity
    opened
    palette
    parent
    scale
    spacing    
    transformOrigin
    visible: false // Turning on/off will show popup window
    width: 200
    height: 200
    x: 50
    y: 50
    z: 50
    onAboutToHide: {}
    onAboutToShow: {}
    onClosed: {}
    onOpened: {}
}
popup.availableHeight // height available to contentItem after deducting vertical padding popup height
popup.availableWidth // width available to contentItem after deducting horizontal padding popup width
popup.close()
popup.forceActiveFocus(reason)
popup.open()
   
// Popup Close Policy Enum
Popup.NoAutoClose                  // The popup will only close when manually instructed
Popup.CloseOnPressOutside          // The popup will close when mouse is pressed outside of it
Popup.CloseOnPressOutsideParent    // The popup will close when mouse is pressed outside of its parent
Popup.CloseOnReleaseOutside        // The popup will close when mouse is released outside of it
Popup.CloseOnReleaseOutsideParent  // The popup will close when mouse is released outside of its parent
Popup.CloseOnEscape                // The popup will close when escape key is pressed while has active focus

// DIALOG
// Inherits Popup
Dialog {
}

// MENU
// Inherits Popup, For context and popup menus
Menu {
    cascade: true // default true for desktops, whether submenus offset or fill over parent menus
    currentIndex: 0 // Index of highlighted item
    overlap: 1 // Pixels the menu horizontally overlaps its parent menu, only for cascade
    title: "title"
    MenuSeparator { } // Inherits Control
    MenuItem { }  // See Button Section
}
menu.contentData // list<Object> of children of the menu
menu.contentModel // model for the menu to use in a view
menu.count // Number of menu children
menu.actionAt(index) // Returns Action or null at index
menu.addAction(action) // Appends an Action
menu.addItem(item) // Appends an Item
menu.addMenu(menu) // Appends a submenu Menu
menu.dismiss() // Closes all menus in the hierarchy that this menu belongs to
menu.insertAction(index, action) // Insert Action at index
menu.insertItem(index, item) // Insert Item at index
menu.insertMenu(index, menu) // Insert a submenu Menu at index
menu.itemAt(index) // Returns Item at index
menu.menuAt(index) // Returns Menu at index
menu.moveItem(from, to) // Moves an item from one index to another
menu.popup(parent, x, y) // Show at x,y in parent coordinate system
menu.popup(x, y) // Show at x,y in menu's coordinate system
menu.popup(parent, pos) // Show at QML point in parent coordinate system
menu.popup(pos) // Show at QML point in menu's coordinate system
menu.popup(parent) // Centers over the parent item
menu.removeAction(action) // Removes Action
menu.removeItem(item) // Removes Item
menu.removeMenu(menu) // Removes submenu Menu
menu.takeAction(index) // Removes and returns Action at index
menu.takeItem(index) // Removes and returns MenuItem at index
menu.takeMenu(index) // Removes and returns Menu at index

// TOOLTIP
// Inherits Popup, Provides tool tips for any control
ToolTip {
   text: "str" // text to show
   delay: 0 // delay in ms after which the tool tip is shown, default 0, negative shown immediately
   timeout: -1 // timeout in ms after which the tool tip is hidden, default -1, 0 hidden immediately
}
Item {
    ToolTip.visible: true // Whether currently visible
    ToolTip.text: "str" // text to show
    ToolTip.delay: 0 // delay in ms after which the tool tip is shown, default 0, negative shown immediately
    ToolTip.timeout: -1 // timeout in ms after which the tool tip is hidden, default -1, 0 hidden immediately
    ToolTip.toolTip: myToolTip
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML TEXT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEXT / TEXTINPUT / TEXTEDIT SHARED PROPERTIES
{
    text: "str"
    color: "red" // text color
    renderType: Text.QtRendering // RenderType Enum, Default given by QQuickWindow::textRenderType
    horizontalAlignment: <T>.AlignHCenter // Alignment Enum
    verticalAlignment: <T>.AlignVCenter // Alignment Enum    
    contentHeight: 200 // height of the unclipped text
    contentWidth: 200 // width of the unclipped text
    bottomPadding: 1.0 // padding around the content, not part of contentHeight, overrides 'padding'
    leftPadding: 1.0 // padding around the content, not part of contentWidth, overrides 'padding'
    rightPadding: 1.0 // padding around the content, not part of contentWidth, overrides 'padding'
    topPadding: 1.0 // padding around the content, not part of contentHeight, overrides 'padding'
    padding: 1.0 // padding around the content, not part of contentHeight/contentHeight
    font.bold: true
    font.capitalization: Font.MixedCase // default, see QML font type for enums
    font.family: "Helvetica"
    font.hintingPreference: Font.PreferDefaultHinting // default, see QML font type for enums
    font.italic: true
    font.kerning: true // Whether to auto adjust character spacing, default enabled
    font.letterSpacing: 1 // real, spacing between characters
    font.pointSize 16 // real, device independent
    font.pixelSize: 5 // Overrides pointSize, int, device dependent
    font.preferShaping: true // Whether to enable display/spacing rules, default enabled
    font.strikeout: true
    font.underline: true
    font.weight: Font.Normal // default, see QML font type for enums
    font.wordSpacing: 1 // real, spacing between words
    wrapMode: <T>.NoWrap // default, Wrap Mode Enum    
}

// TEXTLINE
// lineLaidOut signal object
line.number // Read-only property
line.x / line.y // Can modify to change position of line
line.width // Can modify to change width of line
line.height // Can modify to change height of line 

// TEXT
// Inherits item, Styled text label
Text {
    baseUrl: "http://qt-project.org/" // Used to resolve relative URLs within the text (eg. images/logo.png)
    clip: true // Whether the text is clipped
    elide: Text.ElideNone // default, Elide Mode Enum
    fontSizeMode: Text.FixedSize // default, Font Size Mode Enum
    hoveredLink: "" // link string when the user hovers a link embedded in the text
    lineHeight: 1.0 // Text line height, in pixels or a multiplier depending on lineHeightMode
    lineHeightMode: Text.ProportionalHeight // default, Line Height Mode Enum
    linkColor: "red" // Color of links in the text, RichText unsupported
    maximumLineCount: 1 // Limit the number of lines that the text item will show, RichText unsupported
    minimumPixelSize: 1 // Minimum font pixel size, requires !Text.FixedSize and font.pixelSize != -1
    minimumPointSize: 1 // Minimum font point size, requires !Text.FixedSize and font.pointSize != -1
    style: Text.Normal // Text Style Enum
    styleColor: "red" // Color used depending on style property
    textFormat: Text.PlainText // Text Format Enum
    onLineLaidOut: { line } // Emitted for each line of text that is laid out during the layout process
    onLinkActivated: { link } // when the user clicks on a link embedded in the text, link is string
    onLinkHovered: { link } // when the user hovers on a link embedded in the text, link is string    
}
text.advance // pixel distance from first char of text to first char of another Text if in a text flow
text.lineCount // Number of lines visible in the text item
text.truncated // If the text has been truncated due to maximumLineCount or elid, RichText unsupported
text.forceLayout() // Triggers a re-layout of the displayed text
text.linkAt(x, y) // Returns ink string at point x, y in content coordinates, empty if nothing there

// TEXTINPUT
// Inherits Item, single line of editable plain text
TextInput {
    displayText: "str" // Dependent on echo mode, holds input as editing    
    activeFocusOnPress: true // If gain active focus on a mouse press
    autoScroll: true
    cursorDelegate: Rectangle {} // Override cursor
    echoMode: TextInput.Normal // Echo Mode Enum
    inputMask: ">AAAAA-AAAAA-AAAAA;#" // Input Mask Characters
    inputMethodHints: Qt.ImhDigitsOnly | Qt.ImhTime // Input Method Hints Flags
    validator: myValidator
    maximumLength: 100 // truncates/prevents input, default 32767
    mouseSelectionMode: TextInput.SelectCharacters // Requires selectByMouse true, Selection Mode Enum
    overwriteMode: true // Whether text inserted will overrite (insert key behavior)
    passwordCharacter: "*" // Character used with echomode Password, only first char is used
    passwordMaskDelay: 10 // ms delay before masking the character for echomode Password
    persistentSelection: true // Whether keep selection when focus lost, default false
    readOnly: true
    selectByMouse: true // Allow mouse to select, default false
    selectedTextColor: "red" // text
    selectionColor: "red" // background
    onAccepted: {} // when Return/Enter key pressed and text passed validation
    onEditingFinished: {} // when Return/Enter key pressed or focus lost and text passed validation
    onTextEdited: {} // whenever the text is edited by user, not explicitly set
}
input.acceptableInput // if validator/input mask has been set, true if valid, if not set, always true
input.canUndo // If writable and there are previous operations that can be undone
input.canPaste // If writable and the content of the clipboard can be pasted into input
input.canRedo // If writable and there are undone operations that can be redone
input.cursorPosition // position of the cursor in input
input.cursorRectangle // rectangle where the cursor is rendered within input
input.cursorVisible // True when input shows a cursor
input.length // Length of text, if has inputMask will include mask characters
input.preeditText // partial text input from an input method
input.selectedText // currently selected text
input.selectionEnd // index after last character where selection ends in 'text', read-only
input.selectionStart // index of first character where selection starts in 'text', read-only
input.clear() // clears text
input.copy() // Copies selected text to system clipboard, won't work for Password echomode
input.cut() // Cuts selected text to system clipboard, won't work for Password echomode
input.deselect() // Removes selection
input.ensureVisible(position) // Scrolls the contents to position
input.getText(start, end) // Returns section of text between start and end positions
input.insert(position, "str") // Inserts at position
input.isRightToLeft(start, end) // true if natural reading direction between start/end is right to left
input.moveCursorSelection(position, selectionMode) // Moves cursor and selects while moving
input.paste() // Replaces the currently selected text by the contents of the system clipboard
input.positionAt(x, y, cursorPosition) // Returns position from topleft of input based on Cursor Position Enum
input.positionToRectangle(position) // Returns QML rect that cursor would occupy if placed at char position
input.redo() // Redos if possible
input.remove(start, end) // Removes section of text between start and end position
input.select(start, end) // Selects start to end char position, if out of range does no selection change
input.selectAll() // Causes all text to be selected
input.selectWord() // Selects word closest to the current cursor position
input.undo() // Undos if possible

// TEXTEDIT
// Inherits Item, multiple lines of editable formatted text
// Requires Flickable or ScrollView to implement scrolling, following the cursor etc
TextEdit {
    activeFocusOnPress: true // If gain active focus on a mouse press
    baseUrl: "http://qt-project.org/" // Used to resolve relative URLs within the text (eg. images/logo.png)
    cursorDelegate: Rectangle {} // Override cursor
    hoveredLink: "" // link string when the user hovers a link embedded in the text
    inputMethodComposing: true // whether the textedit has partial text input from an input method
    inputMethodHints: Qt.ImhDigitsOnly | Qt.ImhTime // Input Method Hints Flags
    mouseSelectionMode: TextInput.SelectCharacters // Requires selectByMouse true, Selection Mode Enum
    overwriteMode: true // Whether text inserted will overrite (insert key behavior)
    persistentSelection: true // Whether keep selection when focus lost, default false
    readOnly: true
    selectByKeyboard: true // User can use the keyboard to select text, default false if read-only
    selectByMouse: true // Allow mouse to select, default false
    selectedTextColor: "red" // text
    selectionColor: "red" // background
    tabStopDistance: 1.0 // default distance, in device units, between tab stops
    textFormat: TextEdit.PlainText // Text Format Enum
    onEditingFinished: {} // when the text edit loses focus
    onLinkActivated: { link } // when the user clicks on a link embedded in the text, link is string
    onLinkHovered: { link } // when the user hovers on a link embedded in the text, link is string
}
edit.canUndo // If writable and there are previous operations that can be undone
edit.canPaste // If writable and the content of the clipboard can be pasted into textedit
edit.canRedo // If writable and there are undone operations that can be redone
edit.cursorPosition // position of the cursor in textedit, Cursor Position Enum
edit.cursorRectangle // rectangle where the cursor is rendered within textedit
edit.cursorVisible // True when textedit shows a cursor
edit.length // Length of text
edit.lineCount // Total amount of lines in textedit
edit.preeditText // partial text input from an input method
edit.selectedText // currently selected text
edit.selectionEnd // index after last character where selection ends in 'text', read-only
edit.selectionStart // index of first character where selection starts in 'text', read-only
edit.textDocument // Returns QQuickTextDocument, can be used to implement syntax highlighting
edit.append("str") // Appends a new paragraph to text
edit.clear() // clears text
edit.copy() // Copies selected text to system clipboard
edit.cut() // Cuts selected text to system clipboard
edit.deselect() // Removes selection
edit.getFormattedText(start, end) // Returns formatted section of text between start/end positions
edit.getText(start, end) // Returns section of text between start/end positions
edit.insert(position, "str") // Inserts at position
edit.isRightToLeft(start, end) // true if natural reading direction between start/end is right to left
edit.linkAt(x, y) // Returns ink string at point x, y in content coordinates, empty if nothing there
edit.moveCursorSelection(position, selectionMode) // Moves cursor and selects while moving
edit.paste() // Replaces the currently selected text by the contents of the system clipboard
edit.positionAt(x, y, cursorPosition) // Returns position from topleft of input based on cursorPosition
edit.positionToRectangle(position) // Returns QML rect that cursor would occupy if placed at char position
edit.redo() // Redos if possible
edit.remove(start, end) // Removes section of text between start and end position
edit.select(start, end) // Selects start to end char position, if out of range does no selection change
edit.selectAll() // Causes all text to be selected
edit.selectWord() // Selects word closest to the current cursor position
edit.undo() // Undos if possible
 
// LABEL
// Inherits Text, Styled text label
Label {
    background: Rectangle {} // If no size set, auto follows the control's size, must set implicit sizes if using
}
lbl.palette // QML palette used for control, default application palette

// TEXTFIELD
// Inherits TextInput, Displays a single line of editable plain text
TextField {
    background: Rectangle {} // If no size set, auto follows the control's size, must set implicit sizes
    hoverEnabled: true // Whether the control accepts hover events
    placeholderText: "str" // Text shown before user inputs
    onPressAndHold: { event } // MouseEvent given on a long press
    onPressed: { event } // MouseEvent given on press
    onReleased: { event } // MouseEvent given on release
}
field.focusReason // Holds the reason of the last focus change, Input Focus Reason enum
field.hovered // Whether the control is hovered
field.palette // QML palette used for control, default application palette
  
// TEXTAREA
// Inherits TextEdit, Displays multiple lines of editable formatted text
TextArea {
    background: Rectangle {} // If no size set, auto follows the control's size, must set implicit sizes
    hoverEnabled: true // Whether the control accepts hover events
    placeholderText: "str" // Text shown before user inputs
    onPressAndHold: { event } // MouseEvent given on a long press
    onPressed: { event } // MouseEvent given on press
    onReleased: { event } // MouseEvent given on release
}
area.focusReason // Holds the reason of the last focus change, Input Focus Reason enum
area.hovered // Whether the control is hovered
area.palette // QML palette used for control, default application palette

// TEXTMETRICS
// Provides metrics for a given font and text
TextMetrics {
    text: "str"
}
metrics.advanceWidth // Distance from the position of str where the next string should be drawn in pixels
metrics.boundingRect // Bounding rectangle of str
metrics.elide // Elide Mode Enum
metrics.elideWidth // Largest width str can have in pixels before eliding will occur
metrics.elidedText // Elided version of the string
metrics.font // QML font used for the metrics calculations
metrics.height // Height of the bounding rectangle
metrics.tightBoundingRect // Tight bounding rectangle of str
metrics.width // Width of the bounding rectangle
  
// Text / TextInput / TextEdit RenderType Enum
Text.QtRendering        // advanced features (transformations)
Text.NativeRendering    // look native on the target platform, no advanced features (transformations)  
  
// Text / TextInput / TextEdit Alignment Enum
<T>.AlignLeft   
<T>.AlignRight  
<T>.AlignHCenter
<T>.AlignTop    
<T>.AlignBottom 
<T>.AlignVCenter

// Text / TextInput / TextEdit Wrap Mode Enum
<T>.NoWrap         // no wrapping
<T>.WordWrap       // wrapping done on word boundaries only
<T>.WrapAnywhere   // wrapping is done at any point on a line, even in the middle of a word
<T>.Wrap           // if possible, Text.WordWrap, else Text.WrapAnywhere

// Text / TextMetrics Elide Mode Enum
Qt.ElideNone       // No eliding
Qt.ElideLeft       // For example: "...World"
Qt.ElideMiddle     // For example: "He...ld"
Qt.ElideRight      // For example: "Hello..."

// Text / TextEdit Text Format Enum
// PlainText/StyledText offer better performance at cost of formatting
<T>.AutoText       // Will auto determine whether text should be treated as rich text
<T>.PlainText      // Contains no formatting, only line breaks and spacing
<T>.RichText       // Contains formatting (font sizes, colors, bolding, italics etc)
Text.StyledText    // Optimized RichText format with some formatting 

// TextInput / TextEdit Selection Mode Enum
<T>.SelectCharacters  // Selects all characters between selection start/end pos
<T>.SelectWords       // Selects all words between selection start/end pos, partial words included

// TextInput / TextEdit Input Method Hints Flags
Qt.ImhNone                   // No hints
Qt.ImhHiddenText             // Characters should be hidden, auto set when echoMode is TextInput.Password
Qt.ImhSensitiveData          // Typed text should not be stored in persistent storage (dictionary lookup)
Qt.ImhNoAutoUppercase        // Should not try to auto switch to upper case when a sentence ends
Qt.ImhPreferNumbers          // Numbers are preferred (but not required)
Qt.ImhPreferUppercase        // Upper case letters are preferred (but not required)
Qt.ImhPreferLowercase        // Lower case letters are preferred (but not required)
Qt.ImhNoPredictiveText       // Do not use predictive text (dictionary lookup) while typing
Qt.ImhDate                   // The text editor functions as a date field
Qt.ImhTime                   // The text editor functions as a time field.
Qt.ImhMultiLine              // Don't stop input when Return or Enter key is pressed
Qt.ImhDigitsOnly             // Only digits are allowed
Qt.ImhFormattedNumbersOnly   // Only number input is allowed, includes decimal point and minus sign
Qt.ImhUppercaseOnly          // Only upper case letter input is allowed
Qt.ImhLowercaseOnly          // Only lower case letter input is allowed
Qt.ImhDialableCharactersOnly // Only characters suitable for phone dialing are allowed
Qt.ImhEmailCharactersOnly    // Only characters suitable for email addresses are allowed
Qt.ImhUrlCharactersOnly      // Only characters suitable for URLs are allowed

// TextInput Input Mask Characters
A    // ASCII alphabetic character required. A-Z, a-z
a    // ASCII alphabetic character permitted but not required
N    // ASCII alphanumeric character required. A-Z, a-z, 0-9
n    // ASCII alphanumeric character permitted but not required
X    // Any character required
x    // Any character permitted but not required
9    // ASCII digit required. 0-9
0    // ASCII digit permitted but not required
D    // ASCII digit required. 1-9
d    // ASCII digit permitted but not required (1-9)
#    // ASCII digit or plus/minus sign permitted but not required
H    // Hexadecimal character required. A-F, a-f, 0-9
h    // Hexadecimal character permitted but not required
B    // Binary character required. 0-1
b    // Binary character permitted but not required
>    // All following alphabetic characters are uppercased
<    // All following alphabetic characters are lowercased
!    // Switch off case conversion
\    // To escape the special characters listed above to use them as separators

// TextInput Echo Mode Enum
TextInput.Normal              // Displays the text as it is (default)
TextInput.Password            // Displays platform-dependent password mask characters instead
TextInput.NoEcho              // Displays nothing
TextInput.PasswordEchoOnEdit  // Displays characters as they are entered while editing, otherwise password

// TextInput Cursor Position Enum
TextInput.CursorBetweenCharacters  // Returns the position between characters that is nearest x
TextInput.CursorOnCharacter        // Returns the position before the character that is nearest x

// Text Font Size Mode Enum
Text.FixedSize       // The size specified by font.pixelSize or font.pointSize is used
Text.HorizontalFit   // Largest size up to set max that fits the width of the item without wrapping is used
Text.VerticalFit     // Largest size up to set max that fits the height of the item is used
Text.Fit             // Largest size up to set max that fits within the width/height of the item is used

// Text Line Height Mode Enum
Text.ProportionalHeight  // Use a multiplier for line height (eg. 2.0 doubles height)
Text.FixedHeight         // Use a fixed pixel height

// Text Style Enum
Text.Normal      Text.Raised
Text.Outline     Text.Sunken

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML VALIDATORS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INTVALIDATOR
// Instantiates QIntValidator
IntValidator {
    bottom: -1 // default -infinity
    top: 1 // default infinity
} 
  
// DOUBLEVALIDATOR
// Instantiates QDoubleValidator
DoubleValidator {
    bottom: -1.0 // default -infinity
    top: 1.0 // default infinity
    decimals: 1 // n digits after decimal point, default 1000
    notation: DoubleValidator.ScientificNotation // default 
}
DoubleValidator.StandardNotation     // disables E in value
DoubleValidator.ScientificNotation   // allow E in value

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML GRAPHICS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RECTANGLE
// Inherits Item
Rectangle {
    color: "red"
    radius: 2
    antialiasing: true // Default true if using radius, false otherwise, gives performance hit
    border.color: "red"
    border.width: 1
    gradient: Gradient {}
}

// GRADIENT
Gradient {
}
   
// TRANSITION
// Defines animated transitions that occur on state changes
Transition {
}
