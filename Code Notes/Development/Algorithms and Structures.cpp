////////////////////////////////////////////////////////////////////////////////////////////////////
//ALGORITHMS AND STRUCTURES
////////////////////////////////////////////////////////////////////////////////////////////////////
/*

BIG-O NOTATION:
Used to describe the performance of algorithm based on item amount
O(1) = constant time; doesn't depend on number of items
O(N) = linear time; depends on nummber of items using a power-of curve
O(logN) = logarithmic time; depends on the number of items using a log curve
N = Elements/Vertices
E = Edges connecting elements
K = Algorithm implementation dependent constant

IN-PLACE ALGORITHM: Transforms input using a data structure with a small, constant amount of storage space
STABLE SORT: Maintains the original order of equal elements
COMPARISON SORT: Examines data only by comparing two elements with operator
DISTRIBUTION SORT: Data is distributed to multiple intermediate structures

SEARCHING ALGORITHM    AVG SPEED   AVG SPACE   STRUCTURE    DESCRIPTION
Binary Search          O(logN)     O(1)        Array        Sorted arrays, compares the value with the middle element
Linear Search          O(N)        O(1)        Array        Unsorted arrays, Brute force checking
Breadth-First Search   O(N+E)      O(N)        Graph/Tree   Traverses to all children before moving down a level
Depth-First Search     O(N+E)      O(N)        Graph/Tree   Traverses graph to the greatest depth before backtracking
A*                     O(E)        O(N)        Graph/Tree   Pathfinding using heuristics to traverse
                                       
SORTING ALGORITHM      AVG SPEED   AVG SPACE   STRUCTURE    DESCRIPTION               
Bubble Sort            O(N²)       O(1)        Array        Comparison, simple, swaps elements 
Insertion Sort         O(N²)       O(1)        Array        In-place, stable, fast for small arrays
Select Sort            O(N²)       O(N)        Array        Comparison, In-place, fast for small arrays
Bucket/Bin Sort        O(N+K)      O(NK)       Array        Distribution, Partitions array into buckets
Radix Sort             O(NK)       O(N+K)      Array        Distribution, Works on arrays of numbers
Quick Sort             O(NlogN)    O(N)        Array        Comparison, recursive, faster than other O(NlogN), works well with cache
Merge Sort             O(NlogN)    O(N)        Array        Recursive, Stable, continually splits elements in half
Heap Sort              O(NlogN)    O(N)        Array        Comparison, In-place that builds heap out of data

CONTAINERS    ACESSING   SEARCHING   INSERTING   REMOVING   DESCRIPTION
Array         O(1)       O(N)        O(N)        O(N)       Block of continuous memory
List          O(N)       O(N)        O(1)        O(1)       Elements scattered and linked to each other
Stack         ---        ---         O(1)        O(1)       Last-In-First-Out
Queue         ---        ---         O(1)        O(1)       First-In-First-Out
Hash Table    O(1)       O(1)        O(1)        O(1)       Maps keys to values which live in slots
BS Tree       O(logN)    O(logN)     O(logN)     O(logN)    Binary Tree with only 2 children to each parent

////////////////////////////////////////////////////////////////////////////////////////////////////
//SORTING ALGORITHMS
////////////////////////////////////////////////////////////////////////////////////////////////////

=======================================================================================
BUBBLE SORT
=======================================================================================
1) Iterate through array once for every value
2) Each iteration, check two neighbouring values and swap largest to right

=======================================================================================
SELECTION SORT
=======================================================================================
1) Iterate through array once for every value
2) Each iteration, move the smallest value for whole array to front
3) Next iteration, iterate over remaining values

=======================================================================================
INSERTION SORT
=======================================================================================
Insertion Sort generally faster than selection/bubble
As fast as bubble if array in exact reverse order
1) Iterate through array once for every value
2) Inside a while loop for that value, check it against the previous value
3) If previous is larger, move the value before it and continue to check against the new previous value
4) Continue until the previous value is smaller than the value

=======================================================================================
MERGE SORT
=======================================================================================
1) For a list of elements, split in half and continue this until a tree with single value nodes is created
2) Move up the tree, sorting children of a parent into order and merging to become the parent
3) Continue this until reaching root node

=======================================================================================
QUICKSORT
=======================================================================================
Partitioning algorithm that continues on until elements are sectioned into single slots
Pivot value is taken via 'Median of three'
   • Middle, start and end values of array are looked at
   • The largest value of those three and smallest value are used to create a middle value
   • Middle value becomes the pivot for partitioning
   • When doing sections too small for median of three, use another sorting algorithm

=======================================================================================
RADIX SORT
=======================================================================================
Requires many containers to store temporary copies
Linked lists can be used as alot of adding/deleting
Number of passes is determined by the units of largest number (100 = 3 passes, 1000 = 4 passes)

1) First pass look at first digit on right of a number
2) Depending on the number, copy it over to a container between 0->9
3) Copy back to main container from containers 0->9, clear the temp cont.
4) Repeat for 10s and 100s etc. digits until sorted

=======================================================================================
HEAP SORT
=======================================================================================
Uses a heap structure to sort elements for an array
1) Add the unsorted array to the heap
2) The heap sorts the array weakly
3) Elements are removed from the heap in largest to smallest order
3) As elements are re-added, they are sorted properly into the array

=======================================================================================
BUCKET/BIN SORT
=======================================================================================
• Chooses amount of buckets and partitions array into those
• Buckets are sorted seperately 

////////////////////////////////////////////////////////////////////////////////////////////////////
//SEARCHING ALGORITHMS
////////////////////////////////////////////////////////////////////////////////////////////////////

=======================================================================================
LINEAR SEARCH [ARRAYS]
=======================================================================================
1) Iterate through array to find the value
2) Break if value found

=======================================================================================
BINARY SEARCH [ARRAYS]
=======================================================================================
1) Look at middle value and compare
2) If target is higher, get middle value of upper section
3) If target is lower, get middle value of lower section
4) Repeat until number if found

=======================================================================================
BREADTH-FIRST SEARCH [GRAPHS/TREES]
=======================================================================================
ADVANTAGE: Less likely to get stuck in infinite loop
DISADVANTAGE: Takes longer than depth first search
              As all possible paths are being considered nodes are never 
              deleted from memory until a terminal state is reached

1. A node is expanded and all children checked to whether they have children or not (won/loss)
2. If any have children, all their children are checked for children before moving to another depth level
3. All levels done until depth reached

=======================================================================================
DEPTH FIRST SEARCH [GRAPHS/TREES]
=======================================================================================
ADVANTAGE: Less memory used as only a few nodes need to be kept in memory
DISADVANTAGE: Possibility of getting into an infinite loop 

1. Check if current node is a goal state.
2. If not, expand the node, move to a child of the node, and repeat.
3. If a node is a terminal state or depth reached return to the parent and try another child

=======================================================================================
DIJKSTRA [UNINFORMED SEARCH METHOD]
=======================================================================================
USED: To search graphs for shortest path
ACTION: Chooses nodes with lowest cost so far value
DISADVANTAGE: Searches entire graph considering high amount of nodes; wasteful

=======================================================================================
A* [INFORMED SEARCH METHOD]
=======================================================================================
Most ideal to use priority queue with iteration for Open/Closed lists
std::priority_queue has no iteration; best to use sorted vector
USED: Search weighted graphs with heuristics for shortest path
ACTION: Chooses node with lowest estimated total cost
ADVANTAGE: Less nodes considered than Dijkstra; effecient


////////////////////////////////////////////////////////////////////////////////////////////////////
//HASH TABLES
////////////////////////////////////////////////////////////////////////////////////////////////////

• Expensive to expand- all object's IDs must be changed
• Objects inside cannot be ordered easily
• Copying table is slow
• Can create cache misses as memory is all over the place
• Load Factor: ratio of number of items to the size of the array
• Suffer from collisions/clustering of elements

1) Object is hashed into an integer using the hash function
2) This interger is within hash table's bounds; used as the object's key
3) If a collision occurs with another object already having that key,
   use open addressing/seperate chaining

COALESCED HASHING: Hybrid of open addressing and seperate chaining
ROBIN-HOOD HASHING: Variation of double hashing
PROBABILISTIC HASHING: Drops or replaces value upon collision
PERFECT HASHING: prevents collision with known keys/array size

OPEN ADDRESSING
• No additional allocation of memory to resolve collisions
• Can suffer from clustering of data
• Better for smaller tables

LINEAR PROBING
• Stepping through hash table to find first empty slot
• Suffers from clustering of objects in one section of table
• Especially slow when table is very full

QUADRIC PROBING
• Stepping through has table by constant step size n to find an empty slot
• Suffers because only checks those positions each time

DOUBLE HASHING
• Uses a secondary hash function to find a variable step size to check
• doublehash = constant - (key % constant) to find step size
• array size can't be a prime number otherwise constant looping of same values through array

SEPERATE CHAINING
• Each element in the hash table has a linked list
• Upon collision, the item to be added is inserted into the linked list
• When searching, normal searching occurs on the list for that element
• Uses less space than a large hash table with open addressing

////////////////////////////////////////////////////////////////////////////////////////////////////
//TREES/GRAPHS
////////////////////////////////////////////////////////////////////////////////////////////////////

BALANCED TREE: roughly equal nodes on right/left sides of tree (faster)
UNBALANCED TREE: right/left sides not equal in volume (slower)
HEIGHT VALUE/BALANCE FACTOR: childnode keys added for both sides and compared

BINARY TREE: balanced/unbalanced tree with only two children
B-TREE: balanced tree with multiple children nodes
AVL TREE: self-balancing binary tree that uses balance factor
RED-BLACK TREE: self-balancing binary tree that uses balance factor
2-3 TREES: self-balancing B-Tree with up to 3 child nodes
2-3-4 TREES: self-balancing B-Tree with up to 4 child nodes

EDGES: Connects nodes to each other; have weights
ADJACENT VERTICES: verts connected via an edge
VERTICES: Graph nodes
DIRECTED GRAPH: Edges have directions
WEIGHTED GRAPH: Nodes have /costs
CYCLIC GRAPH: Edge number >= vertices
ACYCLIC GRAPH: Tree
COST: Amount required to reach node (use positive values only)
HEURISTIC: The best guess on how much a node is worth (never overestimate actual cost of node)
POLICY: Solution that tells the optimal/shortest path to any goal node from any start node

=======================================================================================
HEAPS
=======================================================================================

• Weakly ordered Binary Tree that keeps node with largest key as root node
• Not used for searching; used for fast removing from top of heap
• Nodes are not guaranteed to be in order
• All nodes have a smaller value than their parent
• Heaps are implemented as arrays

INSERTING INTO HEAP
• Element is placed on bottom of heap
• Traverses up heap until it finds a node larger than it and becomes it's child

DELETING FROM HEAP
• Removing only happens from the top
• Take a node from bottom and put it on top and move it down until it fits properly

=======================================================================================
BINARY TREES
=======================================================================================

BINARY SEARCH TREE [BINARY TREE]:
• Only two children per node
• Fast insertions, deletions, searching
• Placements of nodes depend on their value

K-DIMENSIONAL TREES [BINARY TREE]:
• Binary Search Tree with keys being multi-dimensional
• Which keys are used to traverse the tree is determined by depth down tree
• On root node, start with first key and with each depth, loop through keys

=======================================================================================
BINARY SPACE PARTITIONING TREES (BSP)
=======================================================================================

• Binary search tree for polygons
• Partitions a scene using a plane in order from front to back
• Best pre-computed offline and later read into the program
• Best suited for indoor environments

1) Take a list of polygons and send it to the next node to calculate
2) Calculate a splitter plane between the polygons
3) Polys on one side of plane go into one child node, the other side goes into the other child node
4) Repeat with another list until condition (ie. node is filled with polys)

CREATING A SPLITTING PLANE
1. Loop through all polygons and create a plane for each one.
2. For each plane add up the number of polygons that are on the front side and on the back side.
3. Plane with lowest absolute difference (abs[front total – back total]) is 
   the best polygon to use as splitting plane

=======================================================================================
QUAD(2D) / OCT(3D) TREES
=======================================================================================

• Create a large bounding box around entire geometry. 
• Rrecursively divide the box into smaller boxes
• This divides the the polygons depending on what box they fall into
• Process continues until conditions are met: minimum number of polys in a node or recursion depth met
• Better for outdoor scenes

QUAD: Partitions scene into four sections; 2D Data structure
OCT: Partitions scene into eight sections; 3D Data structure

=======================================================================================
MINIMAX TREES
=======================================================================================

USED: Perfect information (No element of random chance), 2 player
GOAL: Player chooses moves to maximise the minimum payoff; tries to get the best score
      Opponent chooses moves to minimise the maximum payoff; tries to reduce player's score

MAX NODE: Node that gives the highest payoff; player chooses this
MIN NODE: Node that gives the lowest payoff; opponent chooses this
DEPTH: Level searched to give a list of leaf nodes
L or -inf: Game is lost
W of +inf: Game is won

       6        (root)
      / \
     /   \
    6     3     (player: chooses highest)
   / \   / \ 
  6   8 3   6   (opponent: chooses lowest)

1) Choose a depth to search on the tree
2) Build a list of possible moves at the required depth
3) Traverse up the list from the bottom using MINIMAXto sort values
4) Parent nodes are given the likely value chosen of their children as traversed up

αβ PRUNING:
       6
      / \
     /   \
    6     3
   / \   / \ 
  6   8 3   Pruned

Anything less than highest choice (α) for player doesn't need to be looked at
Anything more than lowest choice (β) for opponent doesn't need to be looked 
Values searched are in range [min->max] [α->β] ([-INF,INF] initially)

*////////////////////////////////////////////////////////////////////////////////////////////////////