/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML COMPONENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ITEM
// import QtQuick 2.11
// Base for most QML components, instantiates QQuickItem
Item {
    activeFocusOnTab // Whether included in active focus on tab, default false
    antialiasing // Whether antialiasing enable, default false
    baselineOffset // Position offset, default 0, used for text
    clip // Whether clipping enabled, default false, hides part of item/children, performance hit
    enabled // Recursive, whether the item receives mouse and keyboard events
    focus // Whether item has input focus
    height // Actual height of item
    width // Actual width of item
    implicitHeight // Default height of the Item if no height is specified
    implicitWidth // Default width of the Item if no width is specified
    opacity // Alpha of item, values outside [0,1] clamped
    objectName // Inherited from QObject
    parent // returns Item, visual parent of the item
    rotation // rotation of the item in degrees clockwise around its transformOrigin, default 0
    scale // size of item, negative mirror's item, default 1
    smooth // Image interpolation, true is linear, false is nearest neighbour, default true
    transformOrigin // TransformOrigin type which scale/rotate use
    visible // Recursive, whether item is rendered
    x / y / z // Position and stacking depth of item, negative z draws under parent
    anchors.top / bottom / right / left
    anchors.horizontalCenter / verticalCenter
    anchors.baseLine
    anchors.fill // Takes QML Item parent or sibling, set to undefined to detach
    anchors.centerIn // Takes QML Item parent or sibling, set to undefined to detach
    anchors.margins // Set value for all margins
    anchors.topMargin / bottomMargin / leftMargin / rightMargin
    anchors.horizontalCenterOffset / verticalCenterOffset
    anchors.baselineOffset // Value offset from position
    anchors.alignWhenCentered // forces centered anchors to align to a whole pixel, default true
    state // QString state name, default empty
    transitions // list<Transition>, transitions to be applied to the item whenever it changes its state     
        
    layer.effect: OpacityMask {} // QtGraphicalEffects
    layer.enabled // Whether the item is layered or not, disabled by default
    layer.format // Enum, internal OpenGL format of the texture
    layer.mipmap // Whether mipmaps are generated for the texture
    layer.samplerName // Name of the effect's source texture property
    layer.samples // Enum, allows requesting multisampled rendering in the layer
    layer.smooth // Whether the layer is smoothly transformed
    layer.sourceRect // The rectangular area of the item that should be rendered into the texture
    layer.textureMirroring // Enum, how the generated OpenGL texture should be mirrored
    layer.textureSize // Pixel size of the layers texture, if empty (default) uses item's size
    layer.wrapMode // Enum, OpenGL wrap modes associated with the texture
        
    /* list<Transform>, list of transformations to apply */
    transform: [  
        Rotation { // rotate item around its center, requires item id
            angle: angleDegrees
            origin.x: item.width / 2
            origin.y: item.height / 2
        },
        Translate { // using x/y will change center of item, requires item id
            x: -item.width / 2
            y: -item.height / 2
        }
    ]           
   
    /* list<State>, if multiple 'when' true, first is chosen */
    states: [
        State {
            name: "state1"
            when: myBoolProperty
        },
        State { 
            name: "state2" 
            when: myFunction
        }
    ]  
}

item.activeFocus // Read only, whether item has active focus
item.childrenRect // Read only, QML rect collective position and size of the item's children
item.data // list<Object> of both visual children and resources
item.resources // list<Object>, contains non-visual children
item.visibleChildren // list<Item>, contains visual children
item.childAt(x, y) // Returns first visible QML Item child found at point within item coord system
item.contains(point) // If item contains QML point (in local coordinates)
item.forceActiveFocus(reason) // Focuses item and any parent FocusScopes, reason optional
item.grabToImage(callback, targetSize) // Grabs the item into an in-memory image
item.grabToImage(function(result) { result.saveToFile("/Folder/image.png"); }) // Save as image
item.mapFromGlobal(x, y) // Converts global coords into item local coords, retuns QML point
item.mapFromItem(item2, x, y, w, h) // Converts item2 local coords into item local coords, retuns QML rect
item.mapFromItem(item2, x, y) // Converts item2 local coords into item local coords, retuns QML point
item.mapToGlobal(x, y) // Converts item local coords into global coords, returns QML point
item.mapToItem(item2, x, y, w, h) // Converts item local coords into item2 local coords, returns QML rect
item.mapToItem(item2, x, y) // Converts item local coords into item2 local coords, returns QML point
item.nextItemInFocusChain(forward) // Returns item next in the focus chain, forward optional

------------------------------------------------------------------------------------------------------------
    
// QTOBJECT
// import QtQml 2.11
// lightweight non-visual element
QtObject {
   objectName: "name"
}

------------------------------------------------------------------------------------------------------------

// COMPONENT
// import QtQml 2.11
// Instantiates QQmlComponent, Used for sourceComponent and contentItem properties
// Template for creating a type, no memory allocated until dynamically created
Component {
    Rectangle {
    }
}
component MyObject: Rectangle {
}

------------------------------------------------------------------------------------------------------------

// CONNECTIONS
// import QtQml 2.11
// Access a signal outside of the object that emits it, required for Loader items
// Signals auto disconnected when Connections object destroyed
Connections {
    target: loader.item
    ignoreUnknownSignals: true // if onMySignal does not exist, do not produce runtime errors
    onMySignal: { value }
}

------------------------------------------------------------------------------------------------------------

// BINDING
// import QtQml 2.11
// Overrides the current binding/value when active, when inactive reassigns binding/value
// < 5.14 restoreMode not avaliable and uses Binding.RestoreBinding (value not restored)
Binding {
    target: item // required if not a child of item with property
    property: "myProperty" // can be QML basic type attribute (eg. "myRectProperty.x")
    when: myBoolean
    value: 10 // Can be value, another property etc
    delayed: true // wait until event queue cleared before assigning
    restoreMode: Binding.RestoreBinding // default pre 6.0, Binding.RestoreBindingOrValue 6.0+
}
Binding on x { // Automatically assigns target as parent and property as "x"
    value: 10
}

// Binding Restore Mode
Binding.RestoreNone    // The original value is not restored at all
Binding.RestoreBinding // The original value is restored if it was another binding
Binding.RestoreValue   // The original value is restored if it was a plain value rather than a binding
Binding.RestoreBindingOrValue // The original value is always restored

------------------------------------------------------------------------------------------------------------

// REPEATER
// import QtQuick 2.11
// Inherits Item, instantiates n items
// creates all of its delegate items when the repeater is first created
// Changing model or setting to null will destroy all previous items
// Delegate has properties 'index' and 'modelData'
// Delegate cannot be switched at runtime
Repeater {
    id: repeater
    model: 3
    Text { text: "Item " + index + "/" + repeater.count }
}
Repeater {
    model: ["one", "two", "three"] /*or*/ myList
    Text { text: "Data: " + modelData }
}
Repeater {
    model: myModel // doesn't use modelData, access roles directly
    Text { text: "Data: " + role_name }
}

------------------------------------------------------------------------------------------------------------

// INSTANTIATOR
// import QtQml 2.11
// Dynamically create objects parented to the Instantiator
// Delegate has properties 'index' and 'modelData'
Instantiator {
   active: true // Changing will create/destroy objects
   asynchronous: true 
   model: myModel
   delegate: Rectangle { index }
   onObjectAdded: { index, object }
   onObjectRemoved: { index, object }
}

instantiator.count // Number of current objects
instantiator.objectAt(index) // Takes int index, returns QtObject
    
------------------------------------------------------------------------------------------------------------
    
// STATE
// import QtQuick 2.11
State {
    extend: "state1" // state to inherit all changes from
    name: "state2" // name of state
    when: myBoolean // when the state should be triggered
        
    /* Change all properties except parent and some anchors */
    PropertyChanges {
        target: item // item to change when state triggered
        explicit
        restoreEntryValues
        myProperty: 2 
    }
    
    /* Change some anchors */
    AnchorChange {
        anchors.left / right / top / bottom
        anchors.horizontalCenter / verticalCenter
        anchors.baseline
        target
    }
    
    /* Change parent */
    ParentChange {
        height: 0.0 // New height after parent change
        parent: item // New parent
        rotation: 0.0 // New rotation after parent change
        scale: 0.0 // New scale after parent change
        target: item // Item to reparent
        width: 0.0 // New width after parent change
        x / y: 0.0 // New offset from new parent
    }
}
    
------------------------------------------------------------------------------------------------------------
    
// STATEGROUP
// import QtQuick 2.11
// State support for non QML Item derived components, see Item for State {}
StateGroup {
    state: "state1" // QString state name, default empty
    states: [State { name: "state1" }, State { name: "state2" }]
}

------------------------------------------------------------------------------------------------------------

// TIMER
// import QtQml 2.11
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
   
// WINDOW
// import QtQuick.Window 2.11
// Instantiates QQuickWindow, Creates a new top-level window 
Window {
    active
    activeFocusItem
    color
    contentItem
    contentOrientation
    data
    flags
    height / width
    maximumHeight / maximumWidth
    minimumHeight / minimumWidth
    modality
    opacity
    screen
    title
    visibility
    visible
    x / y
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
    
// Window Attached Properties
Item {
    Window.active
    Window.activeFocusItem
    Window.contentItem
    Window.height
    Window.visibility
    Window.width
    Window.window
}

------------------------------------------------------------------------------------------------------------

// APPLICATIONWINDOW
// import QtQuick.Controls 1.4
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

// ApplicationWindow Attached Properties
Item {
    ApplicationWindow.activeFocusControl
    ApplicationWindow.contentItem
    ApplicationWindow.footer
    ApplicationWindow.header
    ApplicationWindow.menuBar
    ApplicationWindow.window
}

------------------------------------------------------------------------------------------------------------
	
// SCREEN
// import QtQuick.Window 2.11
// Provides information about the screen of the parent
Screen {
    desktopAvailableHeight / desktopAvailableWidth
    devicePixelRatio
    height / width
    manufacturer
    model
    name
    orientation
    orientationUpdateMask
    pixelDensity
    primaryOrientation
    serialNumber
    virtualX / virtualY
}
   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML LAYOUTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LAYOUT ATTACHED PROPERTIES
// Use these on any components inside the layout
Layout.alignment // Layout Alignment Flags
Layout.column // column position of an item in a GridLayout
Layout.columnSpan // column span of an item in a GridLayout
Layout.fillHeight / fillWidth // Uses preferredHeight / Width if false
Layout.leftMargin / rightMargin / topMargin / bottomMargin // Overrides margin property if set
Layout.margins // Spacing between items
Layout.maximumHeight / maximumWidth // Number.POSITIVE_INFINITY default
Layout.minimumHeight / minimumWidth // 0 default
Layout.preferredHeight / preferredWidth // if -1 (default), will be ignored, and item's implicit used instead
Layout.row // row position of an item in a GridLayout
Layout.rowSpan // row span of an item in a GridLayout
    
// POSITIONER ATTACHED PROPERTIES
// Attach to top-level children within a Column, Row, Flow or Grid
Positioner.index
Positioner.isFirstItem
Positioner.isLastItem
    
------------------------------------------------------------------------------------------------------------

// ROWLAYOUT
// import QtQuick.Layouts 1.11
// Inherits Item, Aligns elements after each other in a single row
RowLayout {
    anchors.fill: parent // Still use anchors on base
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    spacing: 5 // default, spacing between each cell
}

------------------------------------------------------------------------------------------------------------

// ROW
// import QtQuick 2.11
// Inherits Item, Positions its child items along a single row
Row {
    bottomPadding / leftPadding / rightPadding / topPadding // padding around the content
    spacing: 0 // default, amount in pixels left empty between adjacent items
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    add: Transition {} // Effect to apply when items added/visibility changed
    move: Transition {} // Effect to apply when items move
    populate: Transition {} // Effect to apply when first populated with items
    onPositioningComplete: {} // When positioning has been completed
}

row.forceLayout() // Triggers an update instead of waiting for scheduled one

------------------------------------------------------------------------------------------------------------

// COLUMNLAYOUT
// import QtQuick.Layouts 1.11
// Inherits Item, Aligns elements after each other in a single column
ColumnLayout {
    anchors.fill: parent // Still use anchors on base
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    spacing: 5 // default, spacing between each cell
}

------------------------------------------------------------------------------------------------------------

// COLUMN
// import QtQuick 2.11
// Inherits Item, Positions its child items along a single column
Column {
    bottomPadding / leftPadding / rightPadding / topPadding // padding around the content
    spacing: 0 // default, amount in pixels left empty between adjacent items
    add: Transition {} // Effect to apply when items added/visibility changed
    move: Transition {} // Effect to apply when items move
    populate: Transition {} // Effect to apply when first populated with items
    onPositioningComplete: {} // When positioning has been completed
}

column.forceLayout() // Triggers an update instead of waiting for scheduled one

------------------------------------------------------------------------------------------------------------

// GRIDLAYOUT
// import QtQuick.Layouts 1.11
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

------------------------------------------------------------------------------------------------------------

// GRID
// import QtQuick 2.11
// Inherits Item, Positions its child items in grid formation
Grid {
    bottomPadding / leftPadding / rightPadding / topPadding // padding around the content
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

------------------------------------------------------------------------------------------------------------

// FLOW
// import QtQuick 2.11
// Inherits Item, Positions its children side by side, wrapping as necessary
Flow {
    bottomPadding / leftPadding / rightPadding / topPadding // padding around the content
    flow: <T>.LeftToRight // default, Grid Flow Enum, item wrapping with columns/rows properties
    layoutDirection: Qt.LeftToRight // default, Layout Direction Enum, item add/insert direction
    spacing: 0 // default, amount in pixels left empty between adjacent items    
    add: Transition {} // Effect to apply when items added/visibility changed
    move: Transition {} // Effect to apply when items move
    populate: Transition {} // Effect to apply when first populated with items    
    onPositioningComplete: {} // When positioning has been completed
}

flow.forceLayout() // Triggers an update instead of waiting for scheduled one

------------------------------------------------------------------------------------------------------------

// STACKLAYOUT
// import QtQuick 2.11
// Inherits Item, Stack of items where only one item is visible at a time
StackLayout {
    count
    currentIndex: 0 // Current visible item
    Page {} // item 1
    Page {} // item 2
}

------------------------------------------------------------------------------------------------------------

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
// import QtQuick.Controls 2.4
// Inherits QtObject, used in AbstractButton
Action {
    ActionGroup.group: myAction // Add the action to the group
    checkable: true // defaults false
    checked: true
    icon.width / height: 100 // maximum width / height of the icon
    icon.color: "red" // tints with colour    
    icon.source: "qrc:///icon.png"
    text: "str"
    shortcut: StandardKey.Copy
    onTriggered: { source }
    onToggled: { source }
}

action.toggle(source) // Toggle the action/emit signal, source defaults to null
action.trigger(source) // Trigger the action/emit signal, source defaults to null

------------------------------------------------------------------------------------------------------------

// ACTIONGROUP
// import QtQuick.Controls 2.4
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

------------------------------------------------------------------------------------------------------------

// SHORTCUT
// import QtQuick 2.11
// Window or application wide key listening
Shortcut  {
    sequence: "F5" // Can also use StandardKey enum (eg. StandardKey.Cut)
    sequences: ["Ctrl+E,Ctrl+W"]
    autoRepeat: true // Default, whether user can continue to use it after once
    context: Qt.WindowShortcut // Default, other option is Qt.ApplicationShortcut
    enabled: true // Default, whether allowed to use
    onActivated: {}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML CONTROLS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONTROL
// import QtQuick.Controls 2.4
// Inherits Item, base class for all controls
// Controls (except non-interactive indicators) do not let clicks/touches through to children
Control {
    bottomPadding / leftPadding / rightPadding / topPadding // padding around the contentItem, overrides 'padding'
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

------------------------------------------------------------------------------------------------------------

// COMBOBOX
// import QtQuick.Controls 2.4
// Inherits Control, Combined button and popup list for selecting options
// Delegate has properties 'index' and 'modelData'
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-combobox
ComboBox {
    acceptableInput
    count
    currentIndex
    currentText
    displayText
    down
    editText
    editable
    flat
    highlightedIndex 
    indicator
    inputMethodComposing
    inputMethodHints
    model
    popup
    pressed
    textRole
    validator
    onAccepted: {}
    onActivated: { index }
    onHighlighted: { index }
    delegate: MenuItem {
        width: cb.width
        highlighted: cb.highlightedIndex == index
        hoverEnabled: cb.hoverEnabled
    }    
}

cb.decrementCurrentIndex()
cb.find(text, flags)
cb.incrementCurrentIndex()
cb.selectAll()
cb.textAt(index)

------------------------------------------------------------------------------------------------------------

// SPINBOX
// import QtQuick.Controls 2.4
// Inherits Control, Allows the user to select from a set of preset values
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-spinbox
SpinBox {
    down.pressed
    down.indicator
    down.hovered
    editable
    from
    inputMethodComposing
    inputMethodHints
    stepSize
    textFromValue
    to
    up.pressed
    up.indicator
    up.hovered
    validator
    value
    valueFromText
    wrap
    onValueModified: {}
}

sb.increase()
sb.decrease()

------------------------------------------------------------------------------------------------------------

// DIAL
// import QtQuick.Controls 2.4
// Inherits Control, Circular dial that is rotated to set a value
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-dial
Dial {
    angle
    from
    handle
    live
    position
    pressed
    snapMode
    stepSize
    to
    value
    wrap
    onMoved: {}
}

dial.increase()
dial.decrease()

------------------------------------------------------------------------------------------------------------

// BUSYINDICATOR
// import QtQuick.Controls 2.4
// Inherits Control, Indicates background activity
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-busyindicator
BusyIndicator {
    running
}

------------------------------------------------------------------------------------------------------------

// SCROLLINDICATOR
// import QtQuick.Controls 2.4
// Inherits Control, Vertical or horizontal non-interactive scroll indicator
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-scrollindicator
ScrollIndicator {
    active
    horizontal
    orientation
    position
    size
    vertical
}

Flickable {
    ScrollIndicator.vertical: ScrollIndicator { }
    ScrollIndicator.horizontal: ScrollIndicator { }
}
    
------------------------------------------------------------------------------------------------------------

// PROGRESSBAR
// import QtQuick.Controls 2.4
// Inherits Control, Indicates the progress of an operation
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-progressbar
ProgressBar {
    from
    indeterminate
    position
    to
    value
    visualPosition
}

------------------------------------------------------------------------------------------------------------

// SLIDER
// import QtQuick.Controls 2.4
// Inherits Control, Used to select a value by sliding a handle along a track
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-slider
Slider {
    from 
    handle
    horizontal
    live
    orientation
    position
    pressed
    snapMode
    stepSize
    to
    value
    vertical
    visualPosition
    onMoved: {}
}

slider.decrease()
slider.increase()
slider.valueAt(real position)

------------------------------------------------------------------------------------------------------------

// RANGESLIDER
// import QtQuick.Controls 2.4
// Inherits Control, Used to select a range of values by sliding two handles along a track
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-rangeslider
RangeSlider {
    first.value
    first.position
    first.visualPosition
    first.handle
    first.pressed
    first.hovered
    from
    horizontal
    live
    orientation
    second.value
    second.position
    second.visualPosition
    second.handle
    second.pressed
    second.hovered
    snapMode
    stepSize
    to
    vertical
}

slider.first.decrease()
slider.first.increase()
slider.second.decrease()
slider.second.increase()
slider.setValues(firstValue, secondValue)

------------------------------------------------------------------------------------------------------------

// TUMBLER
// import QtQuick.Controls 2.4
// Inherits Control, Spinnable wheel of items that can be selected
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-tumbler
Tumbler {
    count
    currentIndex
    currentItem
    delegate
    model
    moving
    visibleItemCount
    wrap
}

------------------------------------------------------------------------------------------------------------

// SCROLLBAR
// import QtQuick.Controls 2.4
// Inherits Control, Vertical or horizontal interactive scroll bar
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-scrollbar
ScrollBar {
    horizontal: true // Whether horizontal
    interactive: true // Default, whether interactible
    orientation: Qt.Vertical // Default, ScrollBar Orientation Enum
    policy: ScrollBar.AsNeeded // Default, ScrollBar Policy Enum
    position: 0.5 // Position of scroll [0.0, 1.0]
    size: 0.5 // Size of scroll [0.0, 1.0]
    snapMode: ScrollBar.NoSnap // Default, ScrollBar SnapMode Enum
    stepSize: 0.0 // Default, Snap step size
    vertical: true // Whether vertical
}

bar.active // When it's pressed or the attached Flickable is moving
bar.pressed // When the user is pressing it
bar.increase() // Increases the position by stepSize or 0.1 if stepSize is 0.0
bar.decrease() // Decreases the position by stepSize or 0.1 if stepSize is 0.0

// Adding ScrollBar to Flickable / ScrollView
Flickable {
    ScrollBar.vertical: ScrollBar { } // Add a vertical scrollbar
    ScrollBar.horizontal: ScrollBar { } // Add a horizontal scrollbar
    Keys.onUpPressed: scrollBar.decrease()
    Keys.onDownPressed: scrollBar.increase() 
}
    
// ScrollBar SnapMode Enum
ScrollBar.NoSnap         // The scrollbar does not snap
ScrollBar.SnapAlways     // The scrollbar snaps while dragged
ScrollBar.SnapOnRelease  // The scrollbar does not snap while being dragged, but only after released
    
// ScrollBar Policy Enum
ScrollBar.AsNeeded	     // The scroll bar is only shown when the content is too large to fit
ScrollBar.AlwaysOff	     // The scroll bar is never shown
ScrollBar.AlwaysOn	     // The scroll bar is always shown
    
// ScrollBar Orientation Enum
Qt.Vertical    Q.Horizontal

------------------------------------------------------------------------------------------------------------

// TOOLSEPARATOR
// import QtQuick.Controls 2.4
// Inherits Control, Separates a group of items in a toolbar from adjacent items
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-toolseparator
ToolSeparator {
    horizontal
    orientation
    vertical
}

------------------------------------------------------------------------------------------------------------

// PAGE
// import QtQuick.Controls 2.4
// Inherits Control, Styled page control with support for a header and footer
Page {
    contentChildren
    contentData
    contentHeight
    contentWidth
    footer
    header
    title
}

------------------------------------------------------------------------------------------------------------

// PAGEINDICATOR
// import QtQuick.Controls 2.4
// Inherits Control, Indicates the currently active page in a container or layout of multiple pages
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-pageindicator
PageIndicator {
    currentIndex: stackLayout.currentIndex
    count: stackLayout.count
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML BUTTONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ABSTRACTBUTTON
// import QtQuick.Controls 2.4
// Inherits Control, base class for all buttons
AbstractButton {
    text: "str"
    action: myAction
    autoExclusive: true // checkable btns with same parent auto-group, doesn't affect if part of ButtonGroup
    checkable: true // defaults false
    checked: true
    display: AbstractButton.IconOnly // Abstract Button Display Enum
    icon.width / height: 100 // maximum width / height of the icon
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

------------------------------------------------------------------------------------------------------------

// BUTTON
// import QtQuick.Controls 2.4
// Inherits AbstractButton
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-button
Button {
    autoRepeat: false // default, whether repeats pressed, released and clicked signals
    flat: false // default, whether draws a background when pressed or checked
}

btn.highlighted // Whether button is highlighted

------------------------------------------------------------------------------------------------------------

// DELAYBUTTON
// import QtQuick.Controls 2.4
// Inherits AbstractButton, Button with that checks when pressed long enough
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-delaybutton
DelayButton {
    delay: 3000 // Default in ms
    progress: 0.0 // Pressed progress from 0.0->1.0
    transition
    onActivated: {}
}

------------------------------------------------------------------------------------------------------------

// ROUNDBUTTON
// import QtQuick.Controls 2.4
// Inherits AbstractButton, Button with rounded corners
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-roundbutton
RoundButton {
    radius
}

------------------------------------------------------------------------------------------------------------

// CHECKBOX
// import QtQuick.Controls 2.4
// Inherits AbstractButton
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-checkbox
CheckBox {
    checkState
    tristate
}

------------------------------------------------------------------------------------------------------------

// RADIOBUTTON
// import QtQuick.Controls 2.4
// Inherits AbstractButton, Exclusive radio button that can be toggled on or off
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-radiobutton
RadioButton {
}

------------------------------------------------------------------------------------------------------------

// TABBUTTON
// import QtQuick.Controls 2.4
// Inherits AbstractButton, Button with a look suitable for a TabBar
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-tabbutton
TabButton {
}

------------------------------------------------------------------------------------------------------------

// TOOLBUTTON
// import QtQuick.Controls 2.4
// Inherits Button, Button with a look that is more suitable within a ToolBar
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-toolbutton
ToolButton {
}

------------------------------------------------------------------------------------------------------------

// SWITCH
// import QtQuick.Controls 2.4
// Inherits AbstractButton, Switch button that can be toggled on or off
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-switch
Switch {
    position
    visualPosition
}

------------------------------------------------------------------------------------------------------------

// BUTTONGROUP
// import QtQuick.Controls 2.4
// Inherits QtObject, Mutually-exclusive group of checkable buttons
ButtonGroup {
    buttons
    checkedButton
    exclusive
    onClicked: { button }
}

grp.addButton(button)
grp.removeButton(button)
    
// ButtonGroup Attached Properties
AbstractButton {
    ButtonGroup.group
}

------------------------------------------------------------------------------------------------------------

// MENUITEM
// import QtQuick.Controls 2.4    
// Inherits AbstractButton
MenuItem {
   menu: myMenu // Parent menu of the item
   subMenu: Menu {} // Submenu to show if a submenu, default property
   onTriggered: {} // Emitted when the menu item is triggered by the user
}

menuItem.highlighted // Whether is highlighted by the user

------------------------------------------------------------------------------------------------------------

// MENUBARITEM
// import QtQuick.Controls 2.4    
// Inherits AbstractButton
MenuBarItem {
    highlighted
    menu
    menuBar
    onTriggered: {}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML CONTAINERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONTAINER
// import QtQuick.Controls 2.4
// Inherits Control, Abstract base class for some containers
Container {
    contentChildren
    contentData
    contentModel
    count
    currentIndex
    currentItem
}

cont.addItem(Item item)
cont.decrementCurrentIndex()
cont.incrementCurrentIndex()
cont.insertItem(index, item)
cont.itemAt(index) // Returns Item
cont.moveItem(from, to)
cont.removeItem(item)
cont.setCurrentIndex(index)
cont.takeItem(index) // Returns Item

------------------------------------------------------------------------------------------------------------
    
// FLICKABLE
// import QtQuick 2.11    
// Inherits Item, Provides a surface that can be "flicked"
Flickable {    
    atXBeginning
    atXEnd
    atYBeginning
    atYEnd
    bottomMargin / topMargin / leftMargin / rightMargin
    boundsBehavior
    boundsMovement
    contentHeight / contentWidth
    contentItem
    contentX / contentY
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
    interactive: false // Disable scrolling for the view
    maximumFlickVelocity
    moving
    movingHorizontally
    movingVertically
    originX / originY
    pixelAligned
    pressDelay
    rebound
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
    
------------------------------------------------------------------------------------------------------------

// PANE
// import QtQuick.Controls 2.4
// Inherits Control, Provides a background matching with the application style and theme
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-pane
Pane {
    contentChildren
    contentData
    contentHeight / contentWidth
}

------------------------------------------------------------------------------------------------------------

// FRAME
// import QtQuick.Controls 2.4    
// Inherits Pane, Visual frame for a logical group of controls
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-frame
Frame {
}

------------------------------------------------------------------------------------------------------------

// MENUBAR
// import QtQuick.Controls 2.4
// Inherits Container, Provides a window menu bar
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-menubar
// QQC1 provides default styles for submenus but no dynamic options
// Mac 'Quit' and 'About' default menus overidden by last MenuItem that uses specific shortcuts/title
MenuBar {
    contentHeight / contentWidth
    delegate: MenuItem {} // Top level menu buttons
    menus: [ // default property
        Menu {
            title: qsTr("&File")
            MenuItem { text: "&Open..." }
            MenuSeparator {}
            Action { text: "&New..." } // Will be internally wrapped in MenuItem
            Menu {} // Submenu, will be internally wrapped in MenuItem
        }
    ]
}

menu.addMenu(menu)
menu.insertMenu(index, menu)
menu.menuAt(index)
menu.removeMenu(menu)
menu.takeMenu(index)

------------------------------------------------------------------------------------------------------------

// TABBAR
// import QtQuick.Controls 2.4
// Inherits Container, Allows the user to switch between different views or subtasks
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-tabbar
TabBar {
    contentHeight / contentWidth
    position
        
    // TabBar Attached poperties to every button child
    TabButton {
        TabBar.index
        TabBar.position
        TabBar.tabBar
    }
}

------------------------------------------------------------------------------------------------------------

// TOOLBAR
// import QtQuick.Controls 2.4
// Inherits Pane, Container for context-sensitive controls
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-toolbar
ToolBar {
    position
}

------------------------------------------------------------------------------------------------------------

// GROUPBOX
// import QtQuick.Controls 2.4
// Inherits Frame, Visual frame and title for a logical group of controls
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-groupbox
GroupBox {
    label
    title
}

------------------------------------------------------------------------------------------------------------

// DIALOGBUTTONBOX
// import QtQuick.Controls 2.4
// Inherits Container, A button box used in dialogs
DialogButtonBox {
    delegate: Button { // Use DialogButtonBox.buttonBox for parent if floating delegate
        DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
    }   
    alignment
    position
    standardButtons
    onAccepted: {}
    onApplied: {}
    onClicked: { button }
    onDiscarded: {}
    onHelpRequested: {}
    onRejected: {}
    onReset: {}
}

box.standardButton(button) // Returns AbstractButton

------------------------------------------------------------------------------------------------------------
    
// SPLITVIEW
// import QtQuick.Controls 2.14
// inherits Control
SplitView {
    handle
    orientation
    resizing

    // Each child is auto added to 'handle', layed out by orientation and have attached properties
    Item {
        SplitView.minimumWidth / minimumHeight
        SplitView.preferredWidth / preferredHeight
        SplitView.maximumWidth / maximumHeight
        SplitView.fillWidth / fillHeight // true for only one child
        SplitHandle.hovered
        SplitHandle.pressed
    }
}

------------------------------------------------------------------------------------------------------------
   
// SCROLLVIEW
// import QtQuick.Controls 2.4
// Inherits Control, Auto uses single child's Flickable if it has one
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-scrollview
ScrollView {
    clip: true // defaults off, clips contents when scrolling outside width/height
        
    // Width/Height of the scrollable content
    // Needs to be set if ScrollView has more than 1 child to scroll
    // If not set, auto calculated based off contents
    // Set -1 to disable scroll, if inherting Flickable use interactive: false
    contentHeight / contentWidth
}

scroll.contentChildren // list<Item> of children, does not include non-visual QML objects
scroll.contentData //  list<Object> of children, does include non-visual QML objects
    
------------------------------------------------------------------------------------------------------------
   
// STACKVIEW
// import QtQuick.Controls 2.4
// Inherits Control, Provides a stack-based navigation mode
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-stackview
StackView {
    busy
    currentItem
    depth
    empty
    initialItem
    popEnter
    popExit
    pushEnter
    pushExit
    replaceEnter
    replaceExit
        
    // StackView Attached Properties for each child
    pushEnter: Item {
        StackView.index
        StackView.status
        StackView.view
        StackView.visible
        StackView.onActivated: {}
        StackView.onActivating: {}
        StackView.onDeactivated: {}
        StackView.onDeactivating: {}
        StackView.onRemoved: {}
    }
}

view.clear(transition)
view.find(callback, behavior)
view.get(index, behavior)
view.pop(item, operation)
view.push(item, properties, operation)
view.replace(target, item, properties, operation)

------------------------------------------------------------------------------------------------------------
    
// SWIPEVIEW
// import QtQuick.Controls 2.4
// Inherits Container, Enables the user to navigate pages by swiping sideways
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-swipeview
SwipeView {
    horizontal
    interactive
    orientation
    vertical
        
    // SwipeView Attached Properties for each child
    Item {
        index
        isCurrentItem
        isNextItem
        isPreviousItem
        view
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML POPUPS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// POPUP
// import QtQuick.Controls 2.4
// Inherits QtObject, base class for all popups
// 'margins' property determines if auto moves to be inside window, defaults to -1 or 'don’t auto move'
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-popup
Popup {
    activeFocus: true // Read only, whether item has active focus
    background: Item {} // If no size set, auto follows the control's size, must set implicit sizes if using
    bottomMargin: -1 // default no margin, ensures inside window if not -1
    leftMargin: -1 // default no margin, ensures inside window if not -1
    rightMargin: -1 // default no margin, ensures inside window if not -1
    topMargin: -1 // default no margin, ensures inside window if not -1
    margins: -1 // default no margins, ensures inside window if not -1
    bottomPadding: 1 // padding around the contentItem, overrides 'padding'
    leftPadding: 1 // padding around the contentItem, overrides 'padding'
    rightPadding: 1 // padding around the contentItem, overrides 'padding'
    topPadding: 1 // padding around the contentItem, overrides 'padding'
    padding: 1 // padding around the contentItem
    clip: false // default, whether clipping is enabled
    closePolicy: Popup.CloseOnEscape|Popup.CloseOnPressOutside // default, Popup Close Policy Enum
    background: Item {} // Auto sizes to fit popup
    contentItem: Item {} // If popup has explicit size, auto sets size on item. If not, item's implicit sizes used
    contentChildren
    contentData
    contentHeight / contentWidth
    dim
    enabled
    enter
    exit
    focus
    font
    implicitHeight / implicitWidth
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
    visible
    width / height
    x / y / z
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

------------------------------------------------------------------------------------------------------------
    
// DIALOG
// import QtQuick.Controls 2.4
// Inherits Popup, Popup with standard buttons and a title
Dialog {
    footer
    header
    result
    standardButtons
    title
    onAccepted: {}
    onApplied: {}
    onDiscarded: {}
    onHelpRequested: {}
    onRejected: {}
    onReset: {}
}

dialog.accept()
dialog.done(result)
dialog.reject()
dialog.standardButton(button) // Returns AbstractButton

------------------------------------------------------------------------------------------------------------
    
// MENU
// import QtQuick.Controls 2.4
// Inherits Popup, For context and popup menus
// Guarantees auto placement inside application window
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-menu
Menu {
    cascade: true // default true for desktops, whether submenus offset or fill over parent menus
    currentIndex: 0 // Index of highlighted item
    overlap: 1 // Pixels the menu horizontally overlaps its parent menu, only for cascade
    title: "title"
    MenuSeparator { } // Inherits Control
    MenuItem { }  // See Button Section
    
    // Create menu items from a model
    Instantiator {
       model: myModel
       MenuItem { text: model.text }
       onObjectAdded: menu.insertItem(index, object)
       onObjectRemoved: menu.removeItem(object)
    }
	
    // Automatically size menu item based on content
    onOpened: {
        var menuItemWidth = 0;
        for (var i = 0; i < count; i++) {
            var menuItem = itemAt(i);
            if (menuItem.visible) {
                menuItemWidth = Math.max(menuItemWidth, menuItem.implicitWidth);
            }
        }
        menuItemWidth = Math.min(Math.max(menuItemWidth, minMenuItemWidth), maxMenuItemWidth);
        for (var i = 0; i < count; i++) {
            itemAt(i).width = menuItemWidth;
        }
        control.width = menuItemWidth;
    }
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
    
------------------------------------------------------------------------------------------------------------

// TOOLTIP
// import QtQuick.Controls 2.4
// Inherits Popup, Provides tool tips for any control
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-tooltip
ToolTip {
   text: "str" // text to show
   delay: 0 // delay in ms after which the tool tip is shown, default 0, negative shown immediately
   timeout: -1 // timeout in ms after which the tool tip is hidden, default -1, 0 hidden immediately
}

// ToolTip Attached Properties
Item {
    ToolTip.visible: true // Whether currently visible
    ToolTip.text: "str" // text to show
    ToolTip.delay: 0 // delay in ms after which the tool tip is shown, default 0, negative shown immediately
    ToolTip.timeout: -1 // timeout in ms after which the tool tip is hidden, default -1, 0 hidden immediately
    ToolTip.toolTip: myToolTip
}

------------------------------------------------------------------------------------------------------------

// DRAWER
// import QtQuick.Controls 2.4
// Inherits Popup, Side panel that can be opened and closed using a swipe gesture
// https://doc.qt.io/qt-5.11/qtquickcontrols2-customize.html#customizing-drawer
Drawer {
    dragMargin
    edge
    interactive
    position
}
