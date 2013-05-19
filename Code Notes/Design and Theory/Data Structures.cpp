//////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES
//////////////////////////////////////////////////////////////////////////////
/*
STRUCTURE LIST
 • Arrays            • Scene Graphs         • Sphere trees
 • Linked lists      • Binary trees         • Bounding volume heirarchies
 • Queues            • Octrees              • Hash tables
 • Stacks            • Quad trees           • Portals
 • Heaps             • Minimax trees        • Sectors
 • Graphs            • kd trees

STRUCTURE STATS
 Insertion to start/end of array  O(1)
 Insertion into ordered array     O(N)

 Ordered Arrays: Fast to search, slow to organise
 Un-ordered Arrays: Slow to search, fast to organise

//////////////////////////////////////////////////////////////////////////////
//HASH TABLES
//////////////////////////////////////////////////////////////////////////////

- Accessing elements: O(1)
- Searching elements: O(1)
- Inserting elements: O(1)
- expensive to expand- all object's IDs must be changed
- objects inside cannot be ordered easily
- copying table is slow
- can create cache misses as memory is all over the place
- Load Factor: ratio of number of items to the size of the array
- Suffer from collisions/clustering of elements

1) Object is hashed into an integer using the hash function
2) This interger is within hash table's bounds; used as the object's key
3) If a collision occurs with another object already having that key,
   use open addressing/seperate chaining

COALESCED HASHING: Hybrid of open addressing and seperate chaining
ROBIN-HOOD HASHING: Variation of double hashing
PROBABILISTIC HASHING: Drops or replaces value upon collision
PERFECT HASHING: prevents collision with known keys/array size

---------------------------------------------------------------------------
OPEN ADDRESSING
---------------------------------------------------------------------------
 • No additional allocation of memory to resolve collisions
 • Can suffer from clustering of data
 • Better for smaller tables

LINEAR PROBING
  - Stepping through hash table to find first empty slot
  - Suffers from clustering of objects in one section of table
  - Especially slow when table is very full

QUADRIC PROBING
  - Stepping through has table by constant step size n to find an empty slot
  - Suffers because only checks those positions each time

DOUBLE HASHING
  - Uses a secondary hash function to find a variable step size to check
  - doublehash = constant - (key % constant) to find step size
  - array size can't be a prime number otherwise constant looping of same 
    values through array

---------------------------------------------------------------------------
SEPERATE CHAINING
---------------------------------------------------------------------------

- each element in the hash table has a linked list
- upon collision, the item to be added is inserted into the linked list
- when searching, normal searching occurs on the list for that element
- uses less space than a large hash table with open addressing

---------------------------------------------------------------------------
HASHING FUNCTIONS
---------------------------------------------------------------------------

/*HASHING NUMBERS*/
    unsigned int key % size of hash table

/*HASHING STRINGS*/
    unsigned int hash = 0;
    for(int i = 0; i < (int)str.size(); i++)
    {
        int val = (int)str[i];
        hash = (hash * 256 + val) % m_size;
    }

/*
//////////////////////////////////////////////////////////////////////////////
//TREES
//////////////////////////////////////////////////////////////////////////////

BALANCED TREE: roughly equal nodes on right/left sides of tree (faster)
UNBALANCED TREE: right/left sides not equal in volume (slower)
HEIGHT VALUE/BALANCE FACTOR: childnode keys added for both sides and compared

BINARY TREE: balanced/unbalanced tree with only two children
B-TREE: balanced tree with multiple children nodes
AVL TREE: self-balancing binary tree that uses balance factor
RED-BLACK TREE: self-balancing binary tree that uses balance factor
2-3 TREES: self-balancing B-Tree with up to 3 child nodes
2-3-4 TREES: self-balancing B-Tree with up to 4 child nodes
HEAP: weakly ordered binary tree 

/*ALGORITHM*/
//Basic Node Structure
struct TreeNode
{
    TreeNode* child;
    TreeNode* PreviousSibling;
    TreeNode* NextSibling;
};

//Basic Tree Search Function (Depth first search)
bool Search(int value)
{
    if(TreeNode.value == value)
        return true;
    if(TreeNode.child != nullptr)
    {
        if(TreeNode.child->Search(value) == true)
        return true;
    }
    if(TreeNode.NextSibling != nullptr)
    {
        if(TreeNode.NextSibling->Search(value) == true)
        return true;
    }
    return false;
}
/*
//////////////////////////////////////////////////////////////////////////////
//HEAPS
//////////////////////////////////////////////////////////////////////////////

- weakly ordered Binary Tree that keeps node with largest key as root node
- not used for searching; used for fast removing from top of heap
- nodes are not guaranteed to be in order
- all nodes have a smaller value than their parent
- heaps are implemented as arrays

INSERTING INTO HEAP (O(logN))
- element is placed on bottom of heap
- traverses up heap until it finds a node larger than it and becomes 
  it's child

DELETING FROM HEAP (O(logN))
- removing only happens from the top
- take a node from bottom and put it on top and move it down until it 
  fits properly

//////////////////////////////////////////////////////////////////////////////
//BINARY TREES
//////////////////////////////////////////////////////////////////////////////

BINARY SEARCH TREE:
- only two children per node
- fast insertions, deletions, searching
- placements of nodes depend on their value

K-DIMENSIONAL TREES
- Binary Search Tree with keys being multi-dimensional
- which keys are used to traverse the tree is determined by depth down tree
- on root node, start with first key and with each depth, loop through keys

/*CREATING TREE*/
bool push(int key)
{
    Node* newNode = new Node;
    if(rootNode == nullptr)
        rootNode = newNode;
    else
    {
        Node* parentNode = nullptr;
        Node* currentNode = rootNode;
        while(true)
        {
            parentNode = currentNode;
            if(key == currentNode->m_key) { delete newNode; return false; }
            if(key < currentNode->m_key)
            {
                currentNode = currentNode->m_left;
                if(currentNode == nullptr) 
                    { parentNode->m_left = newNode; 
                    return true; }
            }
            else
            {
                currentNode = currentNode->m_right;
                if(currentNode == nullptr) 
                    { parentNode->m_right = newNode; 
                    return true; }
            }
        }
    }
    return true;
}
/*SEARCHING TREE*/
bool search(int key)
{
    if(m_root == nullptr)
        return false;
    Node *currentNode = m_root;
    while(currentNode->m_key != key)
    {
        if(key < currentNode->m_key)
            currentNode = currentNode->m_left;
        else
            currentNode = currentNode->m_right;
        if(currentNode == nullptr)
            return false;
    }
    return true;
}
/*
//////////////////////////////////////////////////////////////////////////////
//BINARY SPACE PARTITIONING TREES(BSP)
//////////////////////////////////////////////////////////////////////////////

- Binary search tree for polygons
- Partitions a scene using a plane in order from front to back
- Best pre-computed offline and later read into the program
- Best suited for indoor environments

1) Take a list of polygons and send it to the next node to calculate
2) Calculate a splitter plane between the polygons
3) Polys on one side of plane go into one child node, the other side goes 
   into the other child node
4) Repeat with another list until condition (ie. node is filled with polys)

CREATING A SPLITTING PLANE
1. Loop through all polygons and create a plane for each one.
2. For each plane add up the number of polygons that are on the front side 
   and on the back side.
3. Plane with lowest absolute difference (abs[front total – back total]) is 
   the best polygon to use as splitting plane

/*PSEUDO-CODE*/
listOfPolygons = new PolygonList(...);
bspTree = CreateBSPNode(listOfPolygons);

CreateBSPNode(listOfPolygons)
{
    node = new BSPNode();
    
    //If threshold is met then stop recursion.
    if(listOfPolygon.count <= MIN_NODE_POLY_COUNT)
    {
        node.polygonList = listOfPolygons;
        return node;
    }

    splitPlane = GetBestSplitter(listOfPolygons);
    for each(element i in listOfPolygons)
    {
        if(splitPlane.Classify(listOfPolygons[i]) == FRONT)
            subPolyList1.push(listOfPolygons[i]);
        else if(splitPlane.Classify(listOfPolygons[i]) == BACK)
            subPolyList2.push(listOfPolygons[i]);
        else
        {
            //Return two split polygons in p1, p2.
            splitPlane.ClipPolygon(listOfPolygons[i], &p1, &p2);
            subPolyList1.push(p1);
            subPolyList2.push(p2);
        }
    }
    node.frontNode = CreateBSPNode(subPolyList1);
    node.backNode = CreateBSPNode(subPolyList2);
    return node;
}
/*
//////////////////////////////////////////////////////////////////////////////
//QUAD(2D) / OCT(3D) TREES
//////////////////////////////////////////////////////////////////////////////

- Create a large bounding box around entire geometry. 
- Rrecursively divide the box into smaller boxes
- This divides the the polygons depending on what box they fall into
- Process continues until conditions are met: minimum number of polys 
  in a node or recursion depth met
- Better for outdoor scenes

QUAD: Partitions scene into four sections; 2D Data structure
OCT: Partitions scene into eight sections; 3D Data structure

//////////////////////////////////////////////////////////////////////////////
//MINIMAX TREES
//////////////////////////////////////////////////////////////////////////////

USED: Perfect information (No element of random chance), 2 player
GOAL: Player chooses moves to maximise the minimum payoff; tries to get 
      the best score
      Opponent chooses moves to minimise the maximum payoff; tries to reduce 
      player's score

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
4) Parent nodes are given the likely value chosen of their children 
   as traversed up

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

/*ALGORITHM*/

ALPHA = -INF
BETA = INF
SEARCHDEPTH

struct NODE
{
    IsTerminal
    Value
    NodeGameState
    BestChildGameState
};

STATIC EVALUATION FUNCTION(NodeGameState,Player)
Determines a value of how good a move could be

node MINIMAX(node, depth, player, alpha, beta)
{
    
    if(node is terminal)
        return node
    if(search depth is reached)
        Static Evaluation Function
        return node

    For every child of node
    {
        Create new child node for the move
        Determine the gamestate for the child given the move
        
        MOVE DOWN THE TREE
        ChildNode = MINIMAX(ChildNode,depth-1,nextplayer,alpha,beta)

        MINIMAX UP TREE
        if(player and ChildNode value > node value)
            node value = ChildNode value
            node BestChildGameState = ChildNode NodeGameState 
            alpha = ChildNode value
    
        if(opponent and ChildNode value < node value)
            node value = ChildNode value
            node BestChildGameState = ChildNode NodeGameState 
            beta = ChildNode value

        if(node value < alpha or > beta)
            return node and prune
    }
    Finished all children
    Return node
}
/*
//////////////////////////////////////////////////////////////////////////////
//GRAPHS
//////////////////////////////////////////////////////////////////////////////

VERTICES: Graph nodes
DIRECTED GRAPH: Edges have directions
WEIGHTED GRAPH: Nodes have /costs
CYCLIC GRAPH: Edge number >= vertices
ACYCLIC GRAPH: Tree
