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
Radix Sort             O(NK)       O(N+K)      Array        Distribution, Works on arrays of numbers, can be stable sort
Quick Sort             O(NlogN)    O(N)        Array        Comparison, recursive, faster than other O(NlogN), works well with cache
Merge Sort             O(NlogN)    O(N)        Array        Recursive, Stable, continually splits elements in half

CONTAINERS         ACCESS    SEARCH    INSERT     REMOVE    DESCRIPTION
Array              O(1)      O(N)      O(N)       O(N)      Block of continuous memory
List               O(N)      O(N)      O(1)       O(1)      Elements scattered and linked to each other
Stack              ---       ---       O(1)       O(1)      Last-In-First-Out
Queue              ---       ---       O(1)       O(1)      First-In-First-Out
Priority Queue     ---       ---       O(logN)    O(1)      Largest sorted to front of queue
Hash Table         O(1)      O(1)      O(1)       O(1)      Maps keys to values which live in slots
BS Trees           O(logN)   O(logN)   O(logN)    O(logN)   2 children per node, no duplicate, left child is lower, right higher
Heap               ---       O(N)      O(logN)    O(logN)   Weakly ordered binary tree where root is highest value
B-Tree             O(logN)   O(logN)   O(logN)    O(logN)   Tree with more than 2 children per node

////////////////////////////////////////////////////////////////////////////////////////////////////
//SEARCH/SORT ALGORITHMS
////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
 BUBBLE SORT
 Sorts in ascending order
 1) Iterate through array once for every value
 2) Each iteration, check two neighbouring values and swap largest to right
*********************************************************************************/
void BubbleSort(std::vector<int>& values)
{
    int temporary = 0;
    for(unsigned int i = 0; i < values.size(); ++i)
    {
        for(unsigned int j = 0; j < values.size()-i-1; ++j)
        {
            if(values[j] > values[j + 1])
            {
                temporary = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temporary;
            }
        }
    }
}

/********************************************************************************
 RADIX SORT
 Sorts in ascending order
 1) Find the maximum number
 2) For each significant position in the maximum number (1, 10, 100...)
    - Find the amount of occurances of each digit from the values and store in bucket
    - Convert this amount to index positions for the sorted array
    - Build the sorted array backwards changing the 
      index position for a digit when a place is filled
*********************************************************************************/
void RadixSort(std::vector<int>& values)
{
    auto getDigit = [](int number, int position) { return number/position % 10; };

    int max = *std::max_element(values.begin(), values.end());
    std::array<int, 10> digitBucket;

    // for each radix significant position in the maximum number (1, 10, 100...)
    for (int position = 1; max/position > 0; position *= 10)
    {
        std::vector<int> sorted(values.size());
        digitBucket.assign(0);

        // Find amount of occurances of each digit
        for (int i = 0; i < static_cast<int>(values.size()); ++i)
        {
            const int digit = getDigit(values[i], position);
            digitBucket[digit]++;
        }

        // Convert this amount to index positions for the sorted array
        for (int i = 1; i < static_cast<int>(digitBucket.size()); ++i)
        {
            digitBucket[i] += digitBucket[i - 1];
        }
        
        // Build the sorted array backwards changing the index 
        // position for a digit when a place is filled
        for (int i = static_cast<int>(values.size())-1; i >= 0; --i)
        {
            const int digit = getDigit(values[i], position);
            digitBucket[digit]--;
            sorted[digitBucket[digit]] = values[i];
        }
        
        std::copy(sorted.begin(), sorted.end(), values.begin());
    }
}

/********************************************************************************
 MERGE SORT
 1)
 2)
*********************************************************************************/
void MergeSort(std::vector<int>& values)
{


}

/********************************************************************************
 QUICK SORT
 Sorts in ascending order
 1) Partition the container to values lower than pivot and values higher
 2) For each partition created, repeat step one if there are values
*********************************************************************************/
void QuickSort(std::vector<int>& values, int minIndex, int maxIndex)
{
    int p2MinIndex = minIndex;
    int p1MaxIndex = maxIndex;
    const int pivot = values[(maxIndex + minIndex)/2];
    
    // Partition the container to values lower than pivot and values higher
    // Creates: p1 -> p1MaxIndex -> p2MinIndex -> p2 (pivot value exists in p2)
    while (p2MinIndex <= p1MaxIndex) 
    {
        while(values[p2MinIndex] < pivot)
            ++p2MinIndex;
    
        while(values[p1MaxIndex] > pivot)
            --p1MaxIndex;
    
        if(p2MinIndex <= p1MaxIndex)
        {
            // Swap the values into the correct partition
            const int temporary = values[p2MinIndex];
            values[p2MinIndex] = values[p1MaxIndex];
            values[p1MaxIndex] = temporary;
            p2MinIndex++;
            p1MaxIndex--;
        }
    }

    // check if first partition needs partitioning
    if(minIndex < p1MaxIndex)
    {
        QuickSort(values, minIndex, p1MaxIndex);
    }

    // check if second partition needs partitioning
    if(p2MinIndex < maxIndex)
    {
        QuickSort(values, p2MinIndex, maxIndex); 
    }
}

/********************************************************************************
 BINARY SEARCH
 Requires ascending sort. Swap end/start assignment in loop for descending sort.
 1) Look at middle value and check if required value
 2) If target is higher, get middle value of upper section
 3) If target is lower, get middle value of lower section
*********************************************************************************/
bool BinarySearch(std::vector<int>& values, int searchvalue)
{
    int start = 0;
    int end = static_cast<int>(values.size()) - 1;

    while(start <= end)
    {
        const int middle = (end + start) / 2;

        if (searchvalue == values[middle])
        {
            return true;
        }
        else if (searchvalue < values[middle])
        {
            end = middle - 1; //start = middle + 1; for descending
        }
        else
        {
            start = middle + 1; //end = middle - 1; for descending
        }
    }
    return false;
}

/********************************************************************************
 BREADTH FIRST SEARCH
 1) Add root to a queue
 2) While the queue is not empty:
    - Pop the front of the queue and check if goal node
    - If not, add all children to the end of the queue
 Advantage: Less likely to get stuck in infinite loop
 Disadvantage: Slower, all nodes kept in memory
*********************************************************************************/
bool BreadthFirstSearch(Node& root, int searchvalue)
{
    std::queue<const Node*> searchqueue;
    searchqueue.push(&root);

    while(!searchqueue.empty())
    {
        const Node* node = searchqueue.front();
        searchqueue.pop();

        // Check for goal node
        if(node->value == searchvalue)
        {
            return true;
        }

        // Add all children to end of queue in any order
        for(const Node& child : node->children)
        {
            searchqueue.push(&child);
        }
    }
    return false;
}

/********************************************************************************
 DEPTH FIRST SEARCH
 1) Add root to a stack
 2) While the stack is not empty:
    - Pop the top of the stack and check if goal node
    - If not, add all children to the top of the stack
 Advantage: Faster, less nodes kept in memory
 Disadvantage: Possibility of getting into an infinite loop 
*********************************************************************************/
bool DepthFirstSearch(Node& root, int searchvalue)
{
    std::stack<const Node*> searchstack;
    searchstack.push(&root);

    while(!searchstack.empty())
    {
        const Node* node = searchstack.top();
        searchstack.pop();

        // Check for goal node
        if(node->value == searchvalue)
        {
            return true;
        }

        // Add all children to top of stack in any order
        for(const Node& child : node->children)
        {
            searchstack.push(&child);
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//HASH TABLES
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
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
//TREES
////////////////////////////////////////////////////////////////////////////////////////////////////

BALANCED TREE: roughly equal nodes on right/left sides of tree (faster)
UNBALANCED TREE: right/left sides not equal in volume (slower)
HEIGHT VALUE/BALANCE FACTOR: childnode keys added for both sides and compared
BINARY TREE: Tree with only two children
B-TREES: Tree with more than two children
TRIE: Node key is constructed from position in tree combining parents
SPACIAL PARTITIONING SCHEME: subdivide a space into partitions
OBJECT PARTITIONING SCHEME: subdivide an object into partitions

=======================================================================================
BINARY TREES
=======================================================================================

BINARY SEARCH TREE:
• The left subtree of a node contains only nodes with values less
• The right subtree of a node contains only nodes with values greater
• The left and right subtree each must also be a binary search tree.
• There must be no duplicate nodes
• Used for sets, maps and dictionarys

SPLAY TREE
• Self-balancing Binary Search Tree
• Recently accessed elements are quick to access
• Height of tree has impact on performance
• Used for caches/garbage collection

RED-BLACK TREE
• Self-balancing Binary Search Tree
• Root is black, each node alternates from red/black down the tree
• All leaf nodes must have a 'nil' node
• All red nodes must have 2 black or nil nodes
• Height balanced: Path from the root to the furthest leaf is no more 
  than twice as long as the path from the root to the nearest leaf

HEAPS
• Weakly ordered Binary Tree that keeps node with largest or smallest key as root node
• Used for fast removing from top of heap, can only remove from top
• Min Heap: All nodes have a smaller value than their parent but not guarenteed to be in any other order
• Max Heap: All nodes have a greater value than their parent but not guarenteed to be in any other order
• Inserts at bottom of heap and traverses up until finds a larger node to be its parent

=======================================================================================
B-TREES
=======================================================================================

GENERIC B-TREE
• Tree with multiple children
• Optimized for systems that read/write large blocks of memory
• Used in databases and filesystems for quick random access to arbitrary blocks

2-3/2-3-4 TREES
• Self balancing tree
• 2-node has one data element, and if internal has two child nodes;
• 3-node has two data elements, and if internal has three child nodes;
• 4-node has three data elements, and if internal has four child nodes.

=======================================================================================
PARTITIONING TREES
=======================================================================================

BINARY SPACE PARTITIONING TREES
• Spacial Partitioning Scheme
• Binary search tree for polygons
• Partitions a scene using a splitter plane
• When 3 children per node are recieved, splits again to move back to 2 children
• Best pre-computed offline and later read into the program
• Best suited for indoor environments

K-D TREE
• Spacial Partitioning Scheme
• Binary space partitioning tree used for points in k-dimensions
• Splitter plane lies on axis of points

R-TREE
• Spacial Partitioning Scheme
• Partitions geometric objects, points and polygons
• Groups nearby objects and uses their combined bounding rectangle as the parent

QUAD(2D) / OCT(3D) TREES
• Spacial Partitioning Scheme
• Partitions polygons or geometric objects
• Quadtrees have four children, Octrees have eight children
• Create a large bounding box around entire geometry and recursively divide the box into smaller boxes
• Best suited for outdoor environments

BOUNDING VOLUME HIERARCHY TREE
• Object Partitioning Scheme done on a single object
• Used in collision detection and ray tracing

=======================================================================================
MINIMAX TREES
=======================================================================================

       6        (root)
      / \
     /   \
    6     3     (player: chooses highest)
   / \   / \ 
  6   8 3   6   (opponent: chooses lowest)

• Tree built from bottom up where each level it alternates between the lowest/highest choice
• Can have any number of children per node at a specifically chosen depth
• Parent nodes are given the likely value chosen of their children as traversed up
• Used for games with perfect information (No element of random chance), 2 players
• Goal: Player chooses moves to maximise the minimum payoff; tries to get the best score
        Opponent chooses moves to minimise the maximum payoff; tries to reduce player's score

MAX NODE: Node that gives the highest payoff; player chooses this
MIN NODE: Node that gives the lowest payoff; opponent chooses this
DEPTH: Level searched to give a list of leaf nodes
L or -inf: Game is lost
W of +inf: Game is won

αβ PRUNING FOR OPTIMISATION:
       6
      / \
     /   \
    6     3
   / \   / \ 
  6   8 3   Pruned

Anything less than highest choice (α) for player doesn't need to be looked at
Anything more than lowest choice (β) for opponent doesn't need to be looked 
Values searched are in range [min->max] [α->β] ([-INF,INF] initially)

////////////////////////////////////////////////////////////////////////////////////////////////////
//GRAPHS
////////////////////////////////////////////////////////////////////////////////////////////////////

DIRECTED GRAPH: Graph with edges with directions
WEIGHTED GRAPH: Graph with edges and/or nodes have a cost
CYCLIC GRAPH: Edge number greater than vertex number
ACYCLIC GRAPH: Tree structure

COST: Amount required to reach node (use positive values only)
HEURISTIC: The best guess on how much a node is worth (never overestimate actual cost of node)
POLICY: Solution that tells the optimal/shortest path to any goal node from any start node

DIJKSTRA [UNINFORMED SEARCH METHOD]
• Searches graphs for shortest path
• Chooses nodes with lowest cost so far value
• Searches entire graph, less effecient than A*

A* [INFORMED SEARCH METHOD]
• Searches weighted graph with heuristics for shortest path
• Chooses node with lowest estimated total cost
• Less nodes considered and more effeciant than Dijkstra
• Most ideal to use priority queue with iteration for Open/Closed lists
• std::priority_queue has no iteration; best to use sorted vector
• 2D Heuristic formula: |Goalʸ-Nodeʸ|+|Goalˣ-Nodeˣ|

- Create two lists: open/closed
- Add start pole to the open list
- While there are nodes in the open list, get the node with the smallest total estimate cost
- Check if this node is the goal
- For all other direct nodes connected to this node, update its costs and move to the open list
- Once all connected nodes are finished, add the parent node to the closed list
- Continue until goal node or no solution is found 

*////////////////////////////////////////////////////////////////////////////////////////////////////