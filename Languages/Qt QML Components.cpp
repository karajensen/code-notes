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
    anchors.top
    anchors.bottom
    anchors.right
    anchors.left
    anchors.horizontalCenter
    anchors.verticalCenter
    anchors.baseLine
    anchors.fill // Takes QML Item parent or sibling, set to undefined to detach
    anchors.centerIn // Takes QML Item parent or sibling, set to undefined to detach
    anchors.margins // Set value for all margins
    anchors.topMargin // Set value for top margin
    anchors.bottomMargin // Set value for bottom margin
    anchors.leftMargin // Set value for left margin
    anchors.rightMargin // Set value for right margin
    anchors.horizontalCenterOffset // Value offset from horizontal center
    anchors.verticalCenterOffset // Value offset from vertical center
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
        Rotation // rotate item around its center, requires item id
        {
            angle: angleDegrees
            origin.x: item.width / 2
            origin.y: item.height / 2
        },
        Translate // using x/y will change center of item, requires item id
        {
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
Component {
    Rectangle {
        signal mySignal(int value)
    }
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
// Will become active and assign value to myProperty when myBoolean becomes true
// When active, will disable any direct bindings myProperty may have until myBoolean is false
Binding {
    target: item // required if not a child of item with property
    property: "myProperty" // can be QML basic type attribute (eg. "myRectProperty.x")
    when: myBoolean
    value: 10 // Can be value, another property etc
    delayed: true // wait until event queue cleared before assigning
}

------------------------------------------------------------------------------------------------------------

// REPEATER
// import QtQuick 2.11
// Inherits Item, instantiates n items
// creates all of its delegate items when the repeater is first created
// Changing model or setting to null will destroy all previous items
Repeater {
    id: repeater
    model: 3
    Text { text: "Item " + index + "/" + repeater.count }
}
Repeater {
    model: ["one", "two", "three"]
    Text { text: "Data: " + modelData }
}
Repeater {
    model: listView
    Text { text: "Data: " + modelData.role_name }
}

------------------------------------------------------------------------------------------------------------

// INSTANTIATOR
// import QtQml 2.11
// Dynamically create objects parented to the Instantiator
Instantiator {
   active: true // Changing will create/destroy objects
   asynchronous: true 
   model: myModel
   delegate: Rectangle { index } // delegate Component to be instantiated, int index avaliable
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
        anchors.left
        anchors.right
        anchors.horizontalCenter
        anchors.top
        anchors.bottom
        anchors.verticalCenter
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
        x: 0.0 // New offset from new parent
        y: 0.0 // New offset from new parent
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

------------------------------------------------------------------------------------------------------------

// FLOW
// import QtQuick 2.11
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML CONTROLS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONTROL
// import QtQuick.Controls 2.4
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

------------------------------------------------------------------------------------------------------------

// COMBOBOX
// import QtQuick.Controls 2.4
// Inherits Control, Combined button and popup list for selecting options
ComboBox {
    acceptableInput
    count
    currentIndex
    currentText
    delegate
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
BusyIndicator {
    running
}

------------------------------------------------------------------------------------------------------------

// SCROLLINDICATOR
// import QtQuick.Controls 2.4
// Inherits Control, Vertical or horizontal non-interactive scroll indicator.
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
ToolSeparator {
    horizontal
    orientation
    vertical
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

------------------------------------------------------------------------------------------------------------

// BUTTON
// import QtQuick.Controls 2.4
// Inherits AbstractButton
Button {
    autoRepeat: false // default, whether repeats pressed, released and clicked signals
    flat: false // default, whether draws a background when pressed or checked
}
btn.highlighted // Whether button is highlighted

------------------------------------------------------------------------------------------------------------

// ROUNDBUTTON
// import QtQuick.Controls 2.4
// Inherits AbstractButton, Button with rounded corners
RoundButton {
    radius
}

------------------------------------------------------------------------------------------------------------

// CHECKBOX
// import QtQuick.Controls 2.4
// Inherits AbstractButton
CheckBox {
    checkState
    tristate
}

------------------------------------------------------------------------------------------------------------

// RADIOBUTTON
// import QtQuick.Controls 2.4
// Inherits AbstractButton, Exclusive radio button that can be toggled on or off
RadioButton {
}

------------------------------------------------------------------------------------------------------------

// TABBUTTON
// import QtQuick.Controls 2.4
// Inherits AbstractButton, Button with a look suitable for a TabBar
TabButton {
}

------------------------------------------------------------------------------------------------------------

// SWITCH
// import QtQuick.Controls 2.4
// Inherits AbstractButton, Switch button that can be toggled on or off
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
   subMenu: Menu {} // Submenu to show if a submenu
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
    
------------------------------------------------------------------------------------------------------------

// PANE
// import QtQuick.Controls 2.4
// Inherits Control, Provides a background matching with the application style and theme
Pane {
    contentChildren
    contentData
    contentHeight
    contentWidth
}

------------------------------------------------------------------------------------------------------------

// FRAME
// import QtQuick.Controls 2.4    
// Inherits Pane, Visual frame for a logical group of controls
Frame {
}

------------------------------------------------------------------------------------------------------------

// MENUBAR
// import QtQuick.Controls 2.4
// Inherits Container, Provides a window menu bar
MenuBar {
    contentHeight
    contentWidth
    delegate
    menus
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
TabBar {
    contentHeight
    contentWidth
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
ToolBar {
    position
}

------------------------------------------------------------------------------------------------------------

// GROUPBOX
// import QtQuick.Controls 2.4
// Inherits Frame, Visual frame and title for a logical group of controls
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
// import QtQuick.Controls 1.4
// No QML Controls 2 version
ControlsLegacy.SplitView {
    handleDelegate
    orientation
    resizing
}
view.addItem(item)
view.removeItem(item)
    
------------------------------------------------------------------------------------------------------------
   
// SCROLLVIEW
// import QtQuick.Controls 2.4
// Inherits Control, Auto uses Flickable if child
ScrollView {
    clip: true // defaults off, clips contents when scrolling outside width/height
    contentHeight: 100 // Height of the scrollable content, if not set, auto calculated based off contents
    contentWidth: 100 // Width of the scrollable content, if not set, auto calculated based off contents
}
scroll.contentChildren // list<Item> of children, does not include non-visual QML objects
scroll.contentData //  list<Object> of children, does include non-visual QML objects
    
------------------------------------------------------------------------------------------------------------
   
// STACKVIEW
// import QtQuick.Controls 2.4
// Inherits Control, Provides a stack-based navigation mode
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
    visible
    width
    height
    x
    y
    z
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
Drawer {
    dragMargin
    edge
    interactive
    position
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

------------------------------------------------------------------------------------------------------------

// TEXTLINE
// lineLaidOut signal object
line.number // Read-only property
line.x / line.y // Can modify to change position of line
line.width // Can modify to change width of line
line.height // Can modify to change height of line 

------------------------------------------------------------------------------------------------------------
    
// TEXT
// import QtQuick 2.11
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

------------------------------------------------------------------------------------------------------------
    
// TEXTINPUT
// import QtQuick 2.11
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
    
------------------------------------------------------------------------------------------------------------

// TEXTEDIT
// import QtQuick 2.11
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
 
------------------------------------------------------------------------------------------------------------
    
// LABEL
// import QtQuick.Controls 2.4
// Inherits Text, Styled text label
Label {
    background: Rectangle {} // If no size set, auto follows the control's size, must set implicit sizes if using
}
lbl.palette // QML palette used for control, default application palette

------------------------------------------------------------------------------------------------------------
    
// TEXTFIELD
// import QtQuick.Controls 2.4    
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
  
------------------------------------------------------------------------------------------------------------
  
// TEXTAREA
// import QtQuick.Controls 2.4
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

------------------------------------------------------------------------------------------------------------
    
// TEXTMETRICS
// import QtQuick 2.11
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
    
------------------------------------------------------------------------------------------------------------
  
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
// import QtQuick 2.11
// Instantiates QIntValidator
IntValidator {
    bottom: -1 // default -infinity
    top: 1 // default infinity
} 
  
------------------------------------------------------------------------------------------------------------

// DOUBLEVALIDATOR
// import QtQuick 2.11
// Instantiates QDoubleValidator
DoubleValidator {
    bottom: -1.0 // default -infinity
    top: 1.0 // default infinity
    decimals: 1 // n digits after decimal point, default 1000
    notation: DoubleValidator.ScientificNotation // default 
}
DoubleValidator.StandardNotation     // disables E in value
DoubleValidator.ScientificNotation   // allow E in value

------------------------------------------------------------------------------------------------------------
    
// REGEXPVALIDATOR
// import QtQuick 2.11
// Instantiates QRegExpValidator
RegExpValidator {
    regExp
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML GRAPHICS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RECTANGLE
// import QtQuick 2.11
// Inherits Item
Rectangle {
    color: "red"
    radius: 2
    antialiasing: true // Default true if using radius, false otherwise, gives performance hit
    border.color: "red"
    border.width: 1
    gradient: Gradient {}
}

// Slice off rounded corners on one side
Item {
    anchors.fill: parent
    clip: true
    Rectangle {
        anchors.fill: parent
        anchors.topMargin: -radius
        radius: 10
    }
}    

------------------------------------------------------------------------------------------------------------

// IMAGE
// import QtQuick 2.11
// SVG must have <style type="text/css"> not <style>
// Can have artifacts if some graphics effects are children
Image {
    asynchronous
    autoTransform
    cache
    fillMode
    horizontalAlignment
    mipmap
    mirror
    paintedHeight
    paintedWidth
    progress
    smooth
    source
    sourceSize
    status
    verticalAlignment
    
    // Image with rounded corners
    OpacityMask {
        maskSource: Rectangle {
            anchors.fill: parent
            radius: 6
        }  
    }
}

------------------------------------------------------------------------------------------------------------

// BORDERIMAGE
// import QtQuick 2.11
// Inherits Item, paints a border based on an image
BorderImage {
    asynchronous
    border.left 
    border.right 
    border.top 
    border.bottom 
    cache
    horizontalTileMode
    mirror
    progress
    smooth
    source
    sourceSize 
    status
    verticalTileMode
}

------------------------------------------------------------------------------------------------------------

// TRANSITION
// import QtQuick 2.11
// Defines animated transitions that occur on state changes
Transition {
    animations
    enabled
    from
    reversible
    running
    to    
}

------------------------------------------------------------------------------------------------------------
   
// BLEND
// import QtGraphicalEffects 1.0
// Inherits Item, Merges two source items by using a blend mode
Blend {
    cached
    foregroundSource
    mode
    source
}
 
------------------------------------------------------------------------------------------------------------
 
// BRIGHTNESSCONTRAST
// import QtGraphicalEffects 1.0    
// Inherits Item, Adjusts brightness and contrast
BrightnessContrast {
    brightness
    cached
    contrast
    source    
}

------------------------------------------------------------------------------------------------------------

// COLOROVERLAY
// import QtGraphicalEffects 1.0    
// Inherits Item, Alters the colors of the source item by applying an overlay color
ColorOverlay {
    cached
    color
    source    
}

------------------------------------------------------------------------------------------------------------

// COLORIZE
// import QtGraphicalEffects 1.0    
// Inherits Item, Sets the color in the HSL color space
Colorize {
    cached
    color
    source    
}

------------------------------------------------------------------------------------------------------------

// DESATURATE
// import QtGraphicalEffects 1.0    
// Inherits Item, Reduces the saturation of the colors
Desaturate {
    cached
    desaturation
    source    
}

------------------------------------------------------------------------------------------------------------

// GAMMAADJUST
// import QtGraphicalEffects 1.0    
// Inherits Item, Alters the luminance of the source item
GammaAdjust {
    cached
    gamma
    source    
}

------------------------------------------------------------------------------------------------------------

// HUESATURATION
// import QtGraphicalEffects 1.0    
// Inherits Item, Alters the source item colors in the HSL color space
HueSaturation {
    cached
    hue
    lightness 
    saturation
    source
}

------------------------------------------------------------------------------------------------------------

// LEVELADJUST
// import QtGraphicalEffects 1.0    
// Inherits Item, Adjusts color levels in the RGBA color space
LevelAdjust {
    cached
    gamma
    maximumInput
    maximumOutput
    minimumInput
    minimumOutput
    source    
}

------------------------------------------------------------------------------------------------------------

// GRADIENT
// import QtQuick 2.11
Gradient {
    stops
}

------------------------------------------------------------------------------------------------------------

// CONICALGRADIENT
// import QtGraphicalEffects 1.0
// Inherits Item, Draws a conical gradient
ConicalGradient {
    angle
    cached
    gradient
    horizontalOffset
    source
    verticalOffset    
}

------------------------------------------------------------------------------------------------------------

// LINEARGRADIENT
// import QtGraphicalEffects 1.0
// Inherits Item, Draws a linear gradient
LinearGradient {
    cached
    end
    gradient
    source
    start    
}

------------------------------------------------------------------------------------------------------------

// RADIALGRADIENT
// import QtGraphicalEffects 1.0    
// Inherits Item, Draws a radial gradient
RadialGradient {
    angle
    cached
    gradient
    horizontalOffset
    horizontalRadius
    source
    verticalOffset
    verticalRadius    
}

------------------------------------------------------------------------------------------------------------

// DISPLACE
// import QtGraphicalEffects 1.0    
// Inherits Item, Moves the pixels of the source item according to a displacement map
Displace {
    cached
    displacement
    displacementSource
    source    
}

------------------------------------------------------------------------------------------------------------

// DROPSHADOW
// import QtGraphicalEffects 1.0    
// Inherits Item, Generates a soft shadow behind the source item
DropShadow {
    cached
    color
    horizontalOffset
    radius
    samples
    source
    spread
    transparentBorder
    verticalOffset    
}

------------------------------------------------------------------------------------------------------------

// INNERSHADOW
// import QtGraphicalEffects 1.0    
// Inherits Item, Generates a colorized and blurred shadow inside the source
InnerShadow {
    cached
    color
    fast
    horizontalOffset
    radius
    samples
    source
    spread
    verticalOffset
}

------------------------------------------------------------------------------------------------------------

// FASTBLUR
// import QtGraphicalEffects 1.0    
// Inherits Item, Applies a fast blur effect to one or more source items
FastBlur {
    id: fastBlur
    radius: 64 // Amount of blurring [0,64]
    cached
    transparentBorder   
    source: ShaderEffectSource {
        sourceItem: myItem // Can't be parent of fastBlur
        sourceRect: Qt.rect(0, 0, fastBlur.width, fastBlur.height)
    }
}

------------------------------------------------------------------------------------------------------------

// GAUSSIANBLUR
// import QtGraphicalEffects 1.0    
// Inherits Item, Applies a higher quality blur effect
GaussianBlur {
    cached
    deviation
    radius
    samples
    source
    transparentBorder    
}

------------------------------------------------------------------------------------------------------------

// MASKEDBLUR
// import QtGraphicalEffects 1.0    
// Inherits Item, Applies a blur effect with a varying intesity
MaskedBlur {
    cached
    maskSource
    radius
    samples
    source    
}

------------------------------------------------------------------------------------------------------------

// RECURSIVEBLUR
// import QtGraphicalEffects 1.0    
// Inherits Item, Blurs repeatedly, providing a strong blur effect
RecursiveBlur {
    cached
    loops
    progress
    radius
    source
    transparentBorder    
}

------------------------------------------------------------------------------------------------------------

// DIRECTIONALBLUR
// import QtGraphicalEffects 1.0    
// Inherits Item, Applies blur effect to the specified direction
DirectionalBlur {
    angle
    cached
    length
    samples
    source
    transparentBorder    
}

------------------------------------------------------------------------------------------------------------

// RADIALBLUR
// import QtGraphicalEffects 1.0    
// Inherits Item, Applies blur in a circular direction around the item center point
RadialBlur {
    angle
    cached
    horizontalOffset
    samples
    source
    transparentBorder
    verticalOffset    
}

------------------------------------------------------------------------------------------------------------

// ZOOMBLUR
// import QtGraphicalEffects 1.0    
// Inherits Item, Applies directional blur effect towards source items center point
ZoomBlur {
    cached
    horizontalOffset 
    length
    samples
    source
    transparentBorder
    verticalOffset    
}

------------------------------------------------------------------------------------------------------------

// GLOW
// import QtGraphicalEffects 1.0    
// Inherits Item, Generates a halo like glow around the source item
Glow {
    cached
    color
    radius
    samples
    source
    spread
    transparentBorder    
}

------------------------------------------------------------------------------------------------------------

// RECTANGULARGLOW
// import QtGraphicalEffects 1.0    
// Inherits Item, Generates a blurred and colorized rectangle
RectangularGlow {
    cached
    color
    cornerRadius
    glowRadius
    spread    
}

------------------------------------------------------------------------------------------------------------
    
// OPACITYMASK
// import QtGraphicalEffects 1.0    
// Inherits Item, Masks the source item with another item
// By default only draws parts of source inside maskSource
OpacityMask {
    cached: false // Default, caches results, use if not animated, improves performance
    invert: false // Default, inverts the mask to only draw what's outside it
    maskSource: Rectangle {}
    source: myItem // Can't be parent of OpacityMask
}

------------------------------------------------------------------------------------------------------------

// THRESHOLDMASK
// import QtGraphicalEffects 1.0    
// Inherits Item, Masks the source item with another item and applies a threshold value
ThresholdMask {
    cached
    maskSource
    source
    spread
    threshold
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML SHAPES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SHAPE
// import QtQuick.Shapes 1.0
// Inherits Item, defines area which any child paths will be drawn
Shape {
    asynchronous
    containsMode
    data
    rendererType
    status
    vendorExtensionsEnabled
}

------------------------------------------------------------------------------------------------------------

// PATH
// import QtQuick 2.11
Path {
    closed
    pathElements
    startX
    startY
}

------------------------------------------------------------------------------------------------------------

// SHAPEPATH
// import QtQuick.Shapes 1.0
// Inherits Path
// First PathLine draws from startX/Y to x/y, next PathLine draws from previous to x/y etc.
// Can't be used with MouseArea (only Shape can)
ShapePath {
    capStyle
    dashOffset
    dashPattern: [3, 2] // [n * strokeWidth dash, n * strokeWidth blank]
    fillColor
    fillGradient
    fillRule
    joinStyle
    miterLimit
    strokeColor
    strokeWidth: 2
    strokeStyle: ShapePath.DashLine
               
    PathLine { 
        x
        y
    }

    PathArc {
        x
        y
        radiusX
        radiusY
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML LOCATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// COORDINATE
// import QtPositioning 5.11
// Auto converts to/from QGeoCoordinate
property var coord: QtPositioning.coordinate()
property var coord: QtPositioning.coordinate(latitude, longitue, altitude)
coord.altitude // double
coord.isValid // const bool
coord.latitude // double
coord.longitude // double
coord.distanceTo(coord2) // returns real distance in meters
coord.azimuth(coord2) // returns real angle [0, 360) of vector betweens coordinate to up vector
coord.atDistanceAndAzimuth(distance, angle) // returns coord distance (m) along vector at angle from up vector
    
------------------------------------------------------------------------------------------------------------

// MAP
// import QtLocation 5.11
// Values like center will not be valid until mapReady is true
Map {
    activeMapType
    bearing
    center
    color
    copyrightsVisible
    error
    errorString
    fieldOfView
    gesture
    mapItems
    mapParameters
    mapReady 
    maximumFieldOfView
    maximumTilt
    maximumZoomLevel
    minimumFieldOfView
    minimumTilt
    minimumZoomLevel
    plugin
    supportedMapTypes
    tilt
    visibleRegion
    zoomLevel    
}
map.addMapItem(item) // Add MapItem
map.addMapItemGroup(itemGroup) // Add MapItemGroup
map.addMapItemView(itemView) // Add MapItemView
map.addMapParameter(parameter) // Add MapParameter
map.alignCoordinateToPoint(coordinate, point)
map.clearData()
map.clearMapItems()
map.clearMapParameters()
map.fitViewportToMapItems()
map.fitViewportToVisibleMapItems()
map.fromCoordinate(coordinate, clipToViewPort) // Returns point, out of bounds is NaN unless clip is false
map.pan(dx, dy)
map.prefetchData()
map.removeMapItem(item) // Remove MapItem
map.removeMapItemGroup(itemGroup) // Remove MapItemGroup
map.removeMapItemView(itemView) // Remove MapItemView
map.removeMapParameter(parameter) // Remove MapParameter
map.setBearing(bearing, coordinate)
map.toCoordinate(position, clipToViewPort) // Returns coordinate, out of bounds is NaN unless clip is false
    
------------------------------------------------------------------------------------------------------------    
    
// MAPCIRCLE
// import QtLocation 5.11
// Auto transforms with Map if added to it
MapCircle {
    center: QtPositioning.coordinate()
    border.width
    border.color
    color
    opacity
    radius
}

------------------------------------------------------------------------------------------------------------

// MAPPOLYGON
// import QtLocation 5.11
// Auto transforms with Map if added to it
// Modifying elements of path does not auto update path, have to reassign whole path
MapPolygon {
    border.width
    border.color
    color
    path
}

------------------------------------------------------------------------------------------------------------

// MAPRECTANGLE
// import QtLocation 5.11
// Auto transforms with Map if added to it
MapRectangle {
    border.width 
    border.color
    bottomRight
    color
    opacity
    topLeft    
}

------------------------------------------------------------------------------------------------------------

// MAPQUICKITEM
// import QtLocation 5.11
// Auto translates (no scaling) with Map if added to it
// Requires zoomLevel to be set for scaling
MapQuickItem {
    anchorPoint
    coordinate
    sourceItem
    zoomLevel
}    

------------------------------------------------------------------------------------------------------------

// MapItemGroup 
// import QtLocation 5.11
// Groups any map items together, can add to map as a single group
MapItemGroup {
}
