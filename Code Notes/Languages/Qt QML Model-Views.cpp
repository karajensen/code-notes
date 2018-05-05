
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT MODELS / VIEWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************************************************
• Model: Contains the data and its structure
• View: A container that displays the data. The view might display the data in a list or a grid.
• Delegate: Determines how each element of data should appear in the view. Can also access each element.
• Role: Used to access different attributes of a data element in the model
**************************************************************************************************************/

ScrollView {
    Layout.fillWidth: true
    Layout.fillHeight: true 
    ListView {
        id: listView
        Layout.fillWidth: true
        Layout.fillHeight: true
        model: context_model // Set through C++

        onCurrentIndexChanged: {
            console.log("Selected " + currentIndex);
        }          
        onCurrentItemChanged: {
            console.log("Selected " + currentItem);
        }
        
        // Each item of the model is instantiated with the delegate
        delegate: Item {
            id: del
            property bool isHighlighted: mouseArea.containsMouse
            property bool isSelected: listView.currentIndex == index
            property bool isSelected: ListView.isCurrentItem // Alternative
              
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onPressed: { listView.currentIndex = index; }
                onClicked: { listView.currentIndex = index; }
            }                   
            Text {
                width: listView.width
                height: 30
                text: role_name // Set through C++
            }
        }
    }
}

//===========================================================================================================
// QML VIEWS
//===========================================================================================================

// LISTVIEW / GRIDVIEW / PATHVIEW SHARED PROPERTIES
{
    currentIndex: 0 // Index of currently selected item, -1 is no selection
    delegate: Component {} // Template defining each item instantiated by the view
    highlight: Component {} // Only creates one which follows selected item
    highlightItem: Item {} // Only creates one which follows selected item 
    highlightMoveDuration: -1 // Default -1, take as many seconds as needed
    highlightRangeMode: <T>.NoHighlightRange // Default, View Highlight Range Enum
    preferredHighlightBegin: 1.0 // Preferred range of the highlight, affected by highlightRangeMode
    preferredHighlightEnd: 2.0 // Preferred range of the highlight, affected by highlightRangeMode
    snapMode: <T>.NoSnap // default, View Snap Mode Enum
    model: myModel // Contains data to display            
}
view.currentItem // Currently selected Item, null is no selection
view.count // Number of items in the view
view.indexAt(x, y) // Returns index of item containing the point x, y in content coords, or -1
view.itemAt(x, y) // Returns item containing the point x, y in content coords, or null
view.positionViewAtIndex(index, mode) // Positions at index by View Position View Mode Enum

// LISTVIEW / GRIDVIEW SHARED PROPERTIES
{
    cacheBuffer: 20 // Explicitly set the buffer size for caching delegates outside the view 
    footer: Component {} // Component to use as the footer
    footerItem: Item {} // Item to use as the footer
    header: Component {} // Component to use as the header
    headerItem: Item {} // Item to use as the header
    highlightFollowsCurrentItem: true // Whether highlight positioning is managed by view
    keyNavigationEnabled: true // Whether the key navigation enabled, bound to Flickable.interactive
    keyNavigationWraps: true // Key navigation that puts selection out of bounds will wrap
    layoutDirection: Qt.LeftToRight // default, View Layout Direction Enum
    verticalLayoutDirection: <T>.TopToBottom // default, View Vertical Layout Direction Enum   
    add: Transition {} // On add of an item
    addDisplaced: Transition {} // On move of items when displaced from an item add
    displaced: Transition {} // On generic displace of items, overridden by add/moveDisplaced
    move: Transition {} // On move of an item
    moveDisplaced: Transition {} // On move of items when displaced from an item move
    populate: Transition {} // On initial populate of items
    remove: Transition {} // On remove of an item
    removeDisplaced: Transition {} // On move of items when displaced from an item remove 
}
view.forceLayout() // Forces an update of the view, otherwise updates batched to happen once per frame
view.positionViewAtBeginning() // Positions the view at the beginning
view.positionViewAtEnd() // Positions the view at the end
  
// LISTVIEW
// Inherits Flickable, Display items from a model in a list
// Delegates are instantiated as needed and may be destroyed at any time
ListView {
    currentSection: "section" // Section that is currently at the beginning of the view
    footerPositioning: ListView.InlineFooter // ListView Footer Positioning Enum
    headerPositioning: ListView.InlineHeader // ListView Header Positioning Enum
    highlightMoveVelocity: 400 // Default 400 pixels/second
    highlightResizeDuration: -1 // Default -1, take as many seconds as needed
    highlightResizeVelocity: 400 // Default 400 pixels/second
    orientation: ListView.Vertical // ListView Orientation Enum
    section.property: "section" // Name of section
    section.criteria: ViewSection.FullString // default, View Section Criteria Enum
    section.delegate: Component {} // Instantiated for each section header
    section.labelPositioning: ViewSection.InlineLabels // default, View Section Positioning
    spacing: 0 // default, Spacing between items
}
view.decrementCurrentIndex() // Decrements the current index, will wrap depending on keyNavigationWraps
view.incrementCurrentIndex() // Increments the current index, will wrap depending on keyNavigationWraps
  
// GRIDVIEW
// Inherits Flickable, Display items from a model in a grid
GridView {
    cellHeight: 100 // default, height of each cell in the grid
    cellWidth: 100 // default, width of each cell in the grid
    flow: GridView.FlowLeftToRight // default, GridView Flow Enum
}
view.moveCurrentIndexDown() // Moves selected down one, will wrap if keyNavigationWraps is true
view.moveCurrentIndexLeft() // Moves selected left one, will wrap if keyNavigationWraps is true
view.moveCurrentIndexRight() // Moves selected right one, will wrap if keyNavigationWraps is true
view.moveCurrentIndexUp() // Moves selected up one, will wrap if keyNavigationWraps is true

// PATHVIEW
// Inherits Item, Lays out model-provided items on a path
PathView {
    cacheItemCount
    dragMargin
    dragging
    flickDeceleration
    flicking
    interactive
    maximumFlickVelocity
    movementDirection
    moving
    offset
    path
    pathItemCount
    onDragEnded: {}
    onDragStarted: {}
    onFlickEnded: {}
    onFlickStarted: {}
    onMovementEnded: {}
    onMovementStarted: {}
}
view.decrementCurrentIndex() // Decrements the current index
view.incrementCurrentIndex() // Increments the current index

// View Layout Direction Enum
Qt.LeftToRight   // Items will be laid out from left to right
Qt.RightToLeft   // Items will be laid out from right to left
  
// View Section Positioning
ViewSection.InlineLabels         // Section labels scroll inline
ViewSection.CurrentLabelAtStart  // Section labels stick to top when scrolling
ViewSection.NextLabelAtEnd       // Section labels stick to end when scrolling
  
// View Section Criteria Enum
ViewSection.FullString      // Sections created based on the section.property value
ViewSection.FirstCharacter  // Sections created based on the first char of the section.property value

// ListView / GridView / PathView Snap Mode Enum
// How the view scrolling will settle following a drag or flick
<T>.NoSnap         // Stops anywhere within the visible area
<T>.SnapToItem     // Settles with an item aligned with the start of the view
<T>.SnapOneItem    // Settles no more than one item away from first visible item on mouse release

// ListView / GridView / PathView Highlight Range Enum
<T>.ApplyRange            // Can move outside of range at the end of list or due to mouse interaction
<T>.StrictlyEnforceRange  // Never move outside range, changes selected item if outside range
<T>.NoHighlightRange      // No range used

// ListView / GridView / PathView Position View Mode Enum
<T>.Beginning      // Position at start
<T>.Center         // Position at center
<T>.End            // Position at end
<T>.Visible        // Ensure a part of the item is visible
<T>.Contain        // Ensure the entire item is visible
<T>.SnapPosition   // Position at preferredHighlightBegin, only for StrictlyEnforceRange or !NoSnap

// ListView / GridView Vertical Layout Direction Enum
<T>.TopToBottom    // Items laid out top to bottom
<T>.BottomToTop    // Items laid out bottom to top

// ListView Header/Footer Positioning Enum
ListView.InlineFooter      // Positioned at the end, connected/will move as a normal item
ListView.OverlayFooter     // Positioned at the end, won't move
ListView.PullBackFooter    // Positioned at the end, can be pushed/pulled
ListView.InlineHeader      // Positioned at the start, connected/will move as a normal item
ListView.OverlayHeader     // Positioned at the start, won't move
ListView.PullBackHeader    // Positioned at the start, can be pushed/pulled

// ListView Orientation Enum
ListView.Horizontal        // Items are laid out horizontally
ListView.Vertical          // Items are laid out vertically

// GridView Flow Enum
GridView.FlowLeftToRight   // Items are laid out from left to right, and the view scrolls vertically
GridView.FlowTopToBottom   // Items are laid out from top to bottom, and the view scrolls horizontally

//===========================================================================================================
// QML DELEGATES
//===========================================================================================================

// DELEGATE DEFAULT ROLES
display       // Qt::DisplayRole, QString
decoration    // Qt::DecorationRole, QColor, QIcon or QPixmap
edit          // Qt::EditRole, QString    
toolTip       // Qt::ToolTipRole, QString  
statusTip     // Qt::StatusTipRole, QString
whatsThis     // Qt::WhatsThisRole, QString

// DELEGATE PROPERTIES
// Given to any delegate Item, don't have to use ItemDelegate type
Item {
    <T>.onAdd: {} // Emitted immediately after an item is added to the view for List/GridView
    <T>.onRemove: {} // Emitted immediately before an item is removed from the view for List/GridView
} 
del.model // Role data for each delegate item, eg. model.role_name
del.modelData // If view's model has no roles, use to access item data for delegate
del.index // Index in view, can be -1 if removed from view
del.<T>.view // Use to access List/Grid/PathView if delegate created outside it
del.<T>.isCurrentItem // Whether the delegate is the currently selected item of List/Grid/PathView
del.<T>.delayRemove // Whether delegate has to delay destruction (eg. to finish animation) of List/GridView
del.ListView.nextSection // Section string of the next item
del.ListView.previousSection  // Section string of the previous item
del.ListView.section // Section string of the item
del.PathView.onPath // Whether the item is currently on the path

// ITEMDELEGATE
// Inherits AbstractButton, Basic item delegate
ItemDelegate {
    highlighted: ListView.isCurrentItem // set whether the delegate is highlighted
}

// CHECKDELEGATE
// Inherits ItemDelegate, has check indicator that can be toggled on or off
CheckDelegate {
}

// RADIODELEGATE
// Inherits ItemDelegate, has radio indicator that can be toggled on or off
RadioDelegate {
}

// SWITCHDELEGATE
// Inherits ItemDelegate, has a switch indicator that can be toggled on or off
SwitchDelegate {
}

// SWIPEDELEGATE
// Inherits ItemDelegate, Swipable item delegate
SwipeDelegate {
}

//===========================================================================================================
// QML MODELS
//===========================================================================================================

// DERIVED QABSTRACTITEMMODELS
// Parent is const QModelIndex&, get using model.index
model.match(index, role, value) // Returns QModelIndexList of first item in index's column with role with value
model.match(index, role, value, hits) // Number of items to look for, use -1 to return all matches
model.match(index, role, value, hits, flags) // MatchFlags with default Qt.MatchStartsWith | Qt.MatchWrap
model.headerData(section, orientation, role) // Default role display, Orientation Enum, returns QVariant
model.setData(index, value, role) // Default role edit, true if successful
model.data(index, role) // Default role display, returns QVariant
model.hasChildren(parent) // parent optional, whether parent has child items
model.columnCount(parent) // parent optional, amount of columns
model.rowCount(parent) // parent optional, amount of rows
model.sibling(row, column, index) // Returns QModelIndex, row/column relative to index
model.hasChildren(parent) // parent optional, whether parent has child items
model.index(row, column, parent) // parent optional, returns QModelIndex
model.hasIndex(row, column, parent) // parent optional, whether index is valid
model.parent(index) // Returns QModelIndex

// LISTMODEL
// free-form list data source
ListModel {
}

// XMLLISTMODEL
// read-only model using XPath expressions
XmlListModel {
}

// OBJECTMODEL
// Defines a set of items to be used as a model
ObjectModel {
}

// ITEMSELECTIONMODEL
// Instantiates QItemSelectionModel, Allows keeping the selection state of multiple views in sync
// QML views do not use QModelIndex, need to convert to it when using ItemSelectionModel
ItemSelectionModel {
}
var modelIndex = model.index(view.currentIndex, 0) // Get QModelIndex from view
ism.select(modelIndex, ItemSelectionModel.Select | ItemSelectionModel.Current)
  
// QAbstractItemModel Orientation Enum
Qt.Horizontal   
Qt.Vertical

// QAbstractItemModel MatchFlags
Qt.MatchExactly          // Performs QVariant-based matching
Qt.MatchFixedString      // Performs string-based matching, case-insensitive unless MatchCaseSensitive flag
Qt.MatchContains         // The search term is contained in the item
Qt.MatchStartsWith       // The search term matches the start of the item
Qt.MatchEndsWith         // The search term matches the end of the item
Qt.MatchCaseSensitive    // The search is case sensitive
Qt.MatchRegExp           // Performs string-based matching using a regular expression as the search term
Qt.MatchWildcard         // Performs string-based matching using a string with wildcards as the search term
Qt.MatchWrap             // Perform a search that wraps around so all items are searched
Qt.MatchRecursive        // Searches the entire hierarchy including children
