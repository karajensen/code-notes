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
}

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

// MENUITEM
// Inherits AbstractButton
MenuItem {
}

// BUTTONGROUP
// Inherits QtObject, Mutually-exclusive group of checkable buttons
ButtonGroup {
}

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
}

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
    visible: false // Turning on/off will show popup window
    title: "Title"
    width: 300
    height: 80
    contentItem: Rectangle {}
}

// DIALOG
// Inherits Popup
Dialog {
}

// MENU
// Inherits Popup, Call using id.popup() to show at mouse position
Menu {
    visible: false // context menu start off invisible
    MenuSeparator { visible: true }
    MenuItem { text: "str" }
}

// TOOLTIP
// Inherits Popup, Provides tool tips for any control
ToolTip {
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
    background: Rectangle {} // If no size set, auto follows the control's size, must set implicit sizes
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
// QML ANIMATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TRANSITION
// Defines animated transitions that occur on state changes
Transition {
}
