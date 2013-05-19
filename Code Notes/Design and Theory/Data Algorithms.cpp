//////////////////////////////////////////////////////////////////////////////
//DATA ALGORITHMS
//////////////////////////////////////////////////////////////////////////////
/*

BIG-O NOTATION:
- Used to describe the performance of algorithm based on item amount
- O(1) = doesn't depend on number of items
- O(N) = depends on nummber of items using a power-of curve
- O(logN) = depends on the number of items using a log curve

COMPILE TIME: action performed during compilation; uses no execution time.
CONSTANT TIME: time taken doesn't increase with number of elements
LINEAR TIME: time taken increases with number of elements

ALGORITHM LIST:
 •  Linear Search
 •  Binary Search
 •  Bubble Sort
 •  Selection Sort
 •  Insertion Sort
 •  Merge Sort
 •  Breadth First Search
 •  Depth First Search
 •  Partitioning

//////////////////////////////////////////////////////////////////////////////
//PARTITIONING ALGORITHM
//////////////////////////////////////////////////////////////////////////////
USED: Split data into two sections
PIVOT: Condition to partition data into sections
SPEED: O(N)

1) Start at left end and continue until finding a value that belongs 
   in right end
2) Once found, start from right end and continue until finding a value 
   that belongs in left end
3) Swap the two values around and continue until all data is split


//////////////////////////////////////////////////////////////////////////////
//ARRAY SEARCHING
//////////////////////////////////////////////////////////////////////////////

---------------------------------------------------------
BINARY SEARCH
---------------------------------------------------------
USED: Finding a value
REQUIREMENTS: Ordered array
SPEED: O(logN)
1) Look at middle value and compare
2) If target is higher, get middle value of upper section
3) If target is lower, get middle value of lower section
4) Repeat until number if found

/*ALGORITHM*/
int lowerBound = 0;
int upperBound = myArray.size()-1;
int current = 0;
while(true)
{
    current = (lowerBound+upperBound)/2;
    if(myArray[current] == target)
        return current;
    else if(lowerBound > upperBound)
        return -1;
    else
    {
        if(myArray[current] < target)
            lowerBound = current+1;
        else
            upperBound = current-1;
    }
}
/*
---------------------------------------------------------
LINEAR SEARCH
---------------------------------------------------------
USED: Finding a value
REQUIREMENTS: Unordered array
SPEED: O(N)
1) Iterate through array to find the value
2) Break if value found

//////////////////////////////////////////////////////////////////////////////
//ARRAY SORTING
//////////////////////////////////////////////////////////////////////////////

---------------------------------------------------------
BUBBLE SORT
---------------------------------------------------------
SPEED: O(N²)
1) Iterate through array once for every value
2) Each iteration, check two neighbouring values and swap largest to right

---------------------------------------------------------
SELECTION SORT
---------------------------------------------------------
SPEED: O(N)->O(N²)
1) Iterate through array once for every value
2) Each iteration, move the smallest value for whole array to front
3) Next iteration, iterate over remaining values

---------------------------------------------------------
INSERTION SORT
---------------------------------------------------------
SPEED: O(N²) 
faster though than selection/bubble
as fast as bubble if array in exact reverse order

1) Iterate through array once for every value
2) Inside a while loop for that value, check it against the previous value
3) If previous is larger, move the value before it and continue to check 
   against the new previous value
4) Continue until the previous value is smaller than the value

/*ALGORITHM*/
int i = 0;
int temp = 0;
for(unsigned int k = 1; k < myArray.size(); k++)
{
    temp = myArray[k];
    i = k;
    while(i > 0 && myArray[i-1] > temp)
    {
        myArray[i] = myArray[i-1];
        i--;
    }
    myArray[i] = temp;
}
/*
---------------------------------------------------------
MERGE SORT
----------------------------------------------------------
SPEED: O(N*logN)
1) For a list of elements, split in half and continue this until a tree 
   with single value nodes is created (recursion)
2) Move up the tree, sorting children of a parent into order and merging 
   to become the parent
3) Continue this until reaching root node

/*ALGORITHM*/
list merge(list left, list right)
{
    while either list has elements
        if both have elements
            add smallest of both first elements to result
            pop front of chosen list
        if left has elements
            add smallest of left to result
            pop front from left
        if right has elements
            add smallest of right to result
            pop front from right
    return result;
}       
list merge_sort(list l)
{
    if list has <= 1 elements
        return l;

    //split the list into two
    int middle = l.size()/2;
    for(unsigned int i = 0; i < middle; ++i)
        left += s[i];
    for(unsigned int i = middle; i < s.size(); ++i)
        right += s[i];

    //pass strings until size is 1
    left = merge_sort(left);
    right = merge_sort(right);

    //sort and merge the resulting string
    return merge(left, right);
}/*

----------------------------------------------------------
SHELLSORT 
----------------------------------------------------------
SPEED: O(N*logN²)
USED: Medium->Small arrays
- Multipass Insertion search with a decreasing step size between comparing 
  previous/current value
- Initial Step size determined by Knuth Method: h = h * 3 + 1
- H starts at 1 and increases until larger than array size. Once larger, 
  the previous value is the initial step
- Other step sizes created by: h = (h - 1) / 3
- Step size important: too small means too many calculations, too large 
  means too much work done on the final step

/*ALGORITHM*/
int temp;
int i = 0, k = 0;
int h = 1;
while(h <= myArray.size() / 3)
    h = h * 3 + 1

while (h > 0) //while step size is > 0
{
    for(k = h; k < myArray.size(); k++)
    {
        temp = myArray[k];
        i = k;
        while(i > h-1 && myArray[i-h] >= temp)
        {
            myArray[i] = myArray[i-h];
            i -= h;
        }
        myArray[i] = temp;
    }
    h = (h-1)/3;
}
/*
----------------------------------------------------------
QUICKSORT
----------------------------------------------------------
SPEED: O(N*logN)
USED: Large arrays
- Partitioning algorithm that continues on until elements are sectioned 
  into single slots
- Pivot value is taken via 'Median of three'
        - middle, start and end values of array are looked at
        - the largest value of those three and smallest value are used 
          to create a middle value
        - middle value becomes the pivot for partitioning
        - when doing sections too small for median of three, use another 
          sorting algorithm

----------------------------------------------------------
RADIX SORT
----------------------------------------------------------
SPEED: O(N*logN)
USED: Arrays containing numbers/bits
- Requires many containers to store temporary copies
- Linked lists can be used as alot of adding/deleting
- Number of passes is determined by the units of largest number 
  (100 = 3 passes, 1000 = 4 passes...)

1) First pass look at first digit on right of a number
2) Depending on the number, copy it over to a container between 0->9
3) Copy back to main container from containers 0->9, clear the temp cont.
4) Repeat for 10s and 100s etc. digits until sorted

----------------------------------------------------------
HEAP SORT
----------------------------------------------------------
SPEED: O(N*logN)
- Uses a heap structure to sort elements for an array

1) Add the unsorted array to the heap
2) The heap sorts the array weakly
3) Elements are removed from the heap in largest to smallest order
3) As elements are re-added, they are sorted properly into the array

----------------------------------------------------------
INTROSPECTIVE SORT
----------------------------------------------------------
SPEED: O(N*logN)
- Starts with Quicksort and switches to Heap sort upon a certain 
  recursion depth

----------------------------------------------------------
BUCKET SORT
----------------------------------------------------------
- Chooses amount of buckets and partitions array into those
- Buckets are sorted seperately 


//////////////////////////////////////////////////////////////////////////////
//GRAPH/TREE SEARCHING
//////////////////////////////////////////////////////////////////////////////

----------------------------------------------------------
BREADTH-FIRST SEARCH
----------------------------------------------------------
USED: To search using a while loop through a tree of specified depth
ADVANTAGE: Less likely to get stuck in infinite loop
DISADVANTAGE: Takes longer than depth first search
              As all possible paths are being considered nodes are never 
              deleted from memory until a terminal state is reached

1) A node is expanded and all children checked to whether they have children 
   or not (won/loss)
2) If they have children, all of the children are checked to whether they 
   have children before another depth level is moved to
3) All levels done until depth reached

/*ALGORITHM*/
BreadthFirstSearch(rootNode)
    Create FIFO (First in first out) Queue
    Push rootNode onto Queue
    while(Queue !Empty)
        Pop v from start of Queue
        set v as visited
        for(each possible move at v->gameBoard)
            create childNode
            push childNode onto Queue
/*
----------------------------------------------------------
DEPTH FIRST SEARCH
----------------------------------------------------------
USED: To search using a recursive function through a tree of specified depth
ADVANTAGE: Less memory used as only a few nodes need to be kept in memory
DISADVANTAGE: Possibility of getting into an infinite loop 

1. Check if current node is a goal state.
2. If not, expand the node, move to a child of the node, and repeat.
3. If a node is a terminal state or depth reached return to the parent and 
   try another child

/*ALGORITHM*/
DepthFirstSearch(v)
    set v as visited
    for(each possible move at v->gameBoard)
        create childNode
        call DepthFirstSearch(childNode)

/*
