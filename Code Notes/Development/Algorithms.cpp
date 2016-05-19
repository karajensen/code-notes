///////////////////////////////////////////////////////////////////////////////////////////////////////
//GENERAL ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Change range of a value
*/
template<typename T> 
T ChangeRange(T value, T currentInner, T currentOuter, T newInner, T newOuter)
{
    return ((value-currentInner)*((newOuter-newInner)/
        (currentOuter-currentInner)))+newInner;
}

/**
* Convert degrees and radians
*/
#define _USE_MATH_DEFINES
#include <math.h>
template<typename T> T DegToRad(T degrees)
{
    return static_cast<T>(M_PI/180.0)*degrees;
}
template<typename T> T RadToDeg(T radians)
{
    return static_cast<T>(180.0/M_PI)*radians;
}

/**
* Get 1D index from 2D coord 
* Requires uniform grid
*/
const int index = r * size + c;
int r = index / size;
int c = index % size;

/**
* Check whether a number is odd
*/
bool isOdd = x % 2;
bool isOdd = x & 1;

/**
* Swap two integers without using a temporary variable
*/
a ^= b;
b ^= a;
a ^= b;

/**
* Get digit at radix significant position (1, 10, 100..)
* Eg. 234 at position 100 = 2, position 10 = 3, position 1 = 4
*/
int digit = number/position % 10;
while (number != 0) 
{
    auto digit = number % 10;
    number /= 10;
}

/**
* Generate Fibonacci Numbers
* Copies into container: 1 1 2 3 5 8 13 21 34 55
*/
std::vector<int> v = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
std::adjacent_difference(v.begin(), v.end() - 1, v.begin() + 1, std::plus<int>());

/**
* Get Factorial n! of a number
* n cannot be negative and factorial of 0 is 1
*/
long FactorialRecursion(int n)
{
    return n == 0 ? 1 : n * FactorialRecursion(n - 1);
}
long Factorial(int n)
{
    long result = 1;
    for (int c = 1; c <= n; ++c)
    {
        result *= c;
    }
    return result;
}

/**
* Euclid's algorithm: 
* Finding the largest integer that divides 2 integers
*/
int GetLowestDivisor(int m, int n)
{
    while (n != 0)
    {
        int mod = m % n;
        m = n;
        n = mod;
    }
    return m;
}

/**
* Get four components of colour
*/
unsigned int color;
int r = color & 0xFF;
int g = (color >> 8) & 0xFF;
int b = (color >> 16) & 0xFF;
int a = (color >> 24) & 0xFF;

/**
* Representing colour
*/
union Color
{
    Color() :
        color(0)
    {
    }

    unsigned int color;
    struct
    {
        unsigned char r, g, b, a;
    };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//STRING ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Make string upper or lower case
*/
std::transform(str.begin(), str.end(), str.begin(), &std::toupper);
std::transform(str.begin(), str.end(), str.begin(), &std::tolower);

/**
* Case insensitive compare
*/
str1.size() == str2.size() &&
std::equal(str1.begin(), str1.end(), str2.begin(),
    [](char c1, char s2) { return toupper(c1) == toupper(c2); });

/**
* Remove duplicate characters (with additional buffer)
*/
std::set<char> characters(str.begin(), str.end());

/**
* Remove duplicate characters (no additional buffer)
* Erase-remove idiom, erase all instances after the current character at index i
*/
for (int i = 0; i < str.size() - 1; ++i)
{
    str.erase(std::remove(str.begin() + i + 1, str.end(), str[i]), str.end());
}

/**
* Reverse a C-String
*/
char test[] = "this is a test";
char saved = ' ';
int len = strlen(test);
for (int i = 0; i < len / 2; ++i)
{
    saved = test[i];
    test[i] = test[len - i - 1];
    test[len - i - 1] = saved;
}

/**
* Reverse a std::string
*/
std::reverse(str.begin(), str.end());

/**
* Determine if 2 strings are anagrams
*/
bool isAnagram = s1.size() == s2.size() && 
    std::is_permutation(s1.begin(), s1.end(), s2.begin());

/**
* Replace all spaces with %20
*/
for (int i = 0; i < str.size(); ++i)
{
    if (str[i] == ' ')
    {
        str[i] = '%';
        str.insert(i + 1, "20");
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//ARRAY ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Kadane's Algorithm:
* Finding the maximum continuous subsequence in an array
*/
int maximumSum = -INT_MAX;
int currentSum = 0;
int currentStart = 0;
int start = 0;
int end = 0;
for (int i = 0; i < arr.size(); ++i)
{
    currentSum += arr[i];
    if (currentSum > maximumSum)
    {
        maximumSum = currentSum;
        start = currentStart;
        end = i;
    }
    if (currentSum < 0)
    {
        currentSum = 0;
        currentStart = i + 1;
    }
}

/**
* Finding the missing number from an array of integers
*/
std::vector<int> baseline = { 1, 4, 2, 11, 56 };
std::vector<int> actual = { 1, 11, 56, 4 };
const auto baseSum = std::accumulate(baseline.begin(), baseline.end(), 0);
const auto actualSum = std::accumulate(actual.begin(), actual.end(), 0);
int missingValue = baseSum ^ actualSum;

/**
* Find number of unique integers in an array
* Use bitset as hash table, fast, high memory use
*/
const int maxValues = INT_MAX + 1; // need more if accepting negative
std::unique_ptr<std::bitset<maxValues>> values(new std::bitset<maxValues>());
for (int i = 0; i < size; ++i)
{
    values.set(arr[i]); // once bit is set will not go back to zero
}
int uniqueInts = values.count();

/**
* Find number of unique integers in an array
* Use set to cull duplicates, slow, low memory use
*/
std::stack<int> values;
for (int i = 0; i < size; ++i)
{
    values.insert(arr[i]);
}
int uniqueInts = values.size();

/**
* Difference between n x n array diagonals
*/
int primary = 0;
int secondary = 0;
for (int i = 0, j = n - 1; i < n; ++i, --j)
{
    primary += arr[i][i];
    secondary += arr[j][i];
}
int difference = abs(primary - secondary);

/**
* Find single integer value in an array of paired integers
*/
unsigned int values = 0;
for (unsigned int i = 0; i < arr.size(); ++i)
{
    values ^= a[i];
}
int singleInteger = values;

/**
* Copy a section of a nxn array at coordinates x,y to a larger nxn array
*/
void Blit(std::vector<int>& arrA, const std::vector<int>& arrB, int x, int y)
{
    const int aSize = std::sqrt(arrA.size());
    const int bSize = std::sqrt(arrB.size());
    const int endX = std::min(x + bSize, aSize);
    const int endY = std::min(y + bSize, aSize);
    const int maxWidth = endX - x;
    const int maxHeight = endY - y;

    // Safe and Slow loop
    for (int i = 0; i < maxWidth; ++i)
    {
        for (int j = 0; j < maxHeight; ++j)
        {
            const int aIndex = (x + i) * aSize + (j + y);
            const int bIndex = i * bSize + j;
            arrA[aIndex] = arrB[bIndex];
        }
    }

    // Unsafe and fast loop
    for (int i = 0; i < maxHeight; ++i)
    {
        const int aIndex = (y + i) * aSize + x;
        const int bIndex = i * bSize;
        memcpy(&arrA[aIndex], &arrB[bIndex], sizeof(int)*maxWidth);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//BUBBLE SORT
///////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////
//MERGE SORT
///////////////////////////////////////////////////////////////////////////////////////////////////////

MergeSort(&values[0], 1, &values[0]+1, values.size()-1);
void MergeSort(int* a, int lengthA, int* b, int lengthB)
{
    if (lengthA > 1)
    {
        int midA = lengthA / 2;
        MergeSort(a, midA, a + midA, lengthA - midA);
    }
    if (lengthB > 1)
    {
        int midB = lengthB / 2;
        MergeSort(b, midB, b + midB, lengthB - midB);
    }

    int i = 0;
    int currentA = 0;
    int currentB = 0;
    std::vector<int> sortedArray(lengthA + lengthB);

    while (currentA < lengthA && currentB < lengthB)
    {
        if (a[currentA] <= b[currentB])
        {
            sortedArray[i] = a[currentA];
            ++currentA;
        }
        else
        {
            sortedArray[i] = b[currentB];
            ++currentB;
        }
        ++i;
    }
    while (currentA < lengthA)
    {
        sortedArray[i] = a[currentA];
        ++currentA;
        ++i;
    }
    while (currentB < lengthB)
    {
        sortedArray[i] = b[currentB];
        ++currentB;
        ++i;
    }
    for (unsigned int j = 0; j < sortedArray.size(); ++j)
    {
        a[j] = sortedArray[j];
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//QUICK SORT
///////////////////////////////////////////////////////////////////////////////////////////////////////

QuickSort(values, 0, values.size()-1);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////
//BINARY SEARCH
///////////////////////////////////////////////////////////////////////////////////////////////////////

BinarySearch(values, values.size()/2);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////
//BREADTH FIRST SEARCH
///////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////
//DEPTH FIRST SEARCH
///////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////
//STACK ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T> class Stack
{
public:

    Stack() = default;

    void Push(T data)
    {
        auto entry = std::make_unique<Entry>();
        entry->data = data;
        entry->next = std::move(m_root);
        m_root = std::move(entry);
    }

    T Pop()
    {
        if (!m_root)
        {
            throw std::exception("Tried to pop empty stack");
        }

        T data = m_root->data;
        m_root = std::move(m_root->next);
        return data;
    }

private:

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    struct Entry
    {
        T data;
        std::unique_ptr<Entry> next;
    };

    std::unique_ptr<Entry> m_root;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//HASH ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Get a hash key from a string
* 37 or 31 good values for generating unique keys
*/
unsigned int GetKey(const std::string& str)
{
    unsigned int key = 0;
    for (char ch : str)
    {
        key = 37 * key + ch;
    }
    return key % tableSize;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//BINARY TREE ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
    int value;
    Node* left;
    Node* right;
};

/**
* Get maximum depth for tree
*/
int MaxDepth(Node* n)
{
    if (n == nullptr)
    {
        return 0;
    }
    return 1 + std::max(MaxDepth(n->left), MaxDepth(n->right));
}

/**
* Get minimum depth for tree
*/
int MinDepth(Node* n)
{
    if (n == nullptr)
    {
        return 0;
    }
    return 1 + std::min(MinDepth(n->left), MinDepth(n->right));
}

/**
* Check if tree is balanced
*/
bool IsBalanced(Node* root)
{
    return MaxDepth(root) - MinDepth(root) <= 1;
}

/**
* Binary Tree Traversal
*/
void Traverse(Node* node)
{
    if (node != nullptr)
    {
        PreOrderWork(node);
        Traverse(node->left);
        InOrderWork(node);
        Traverse(node->right);
        PostOrderWork(node);
    }
}

/**
* Binary Search Tree Insert value
*/
void Insert(int value, Node*& node)
{
    if (node == nullptr)
    {
        node = new Node(value);
    }
    else if (value < node->value)
    {
        Insert(value, node->left);
    }
    else if (value > node->value)
    {
        Insert(value, node->right);
    }
}

/**
* Binary Search Tree Find Minimum value
*/
Node* FindMin(Node* node)
{
    if (node->left == nullptr)
    {
        return node;
    }
    else
    {
        return FindMin(node->left);
    }
}

/**
* Binary Search Tree Find value
*/
bool Find(int value, Node* node)
{
    if (node == nullptr)
    {
        return false;
    }
    else if (value < node->value)
    {
        return Find(value, node->left);
    }
    else if (value > node->value)
    {
        return Find(value, node->right);
    }
    return true;
}

/**
* Binary Search Tree Remove value
*/
bool Remove(int value, Node*& node)
{
    if (node == nullptr)
    {
        return false;
    }
    else if (value < node->value)
    {
        return Remove(value, node->left);
    }
    else if (value > node->value)
    {
        return Remove(value, node->right);
    }
    else // Found value to remove
    {
        if (node->left != nullptr && node->right != nullptr)
        {
            // Have 2 children: Replace with right subtree lowest value
            node->value = FindMin(node->right)->value;
            Remove(node->value, node->right);
        }
        else
        {
            Node* toDelete = node;
            node = node->left != nullptr ? node->left : node->right;
            delete toDelete;
        }
        return true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//LINKED LIST ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Reverse a linked list
* Call ReverseList(root)
*/
Node* ReverseList(Node* node)
{
    Node* temp = nullptr;
    Node* previous = nullptr;
    while (node != nullptr)
    {
        temp = node->next;
        node->next = previous;
        previous = node;
        node = temp;
    }
    return previous;
}

/**
* Reverse a linked list recursively
* Call ReverseListRecursive(root, nullptr)
*/
Node* ReverseListRecursive(Node* node, Node* previous)
{
    if (node != nullptr)
    {
        Node* temp = node->next;
        node->next = previous;
        return ReverseListRecursive(temp, node);
    }
    return previous;
}

/**
* Remove duplicates using a temporary buffer
*/
Node* previous = n;
std::vector<int> results;
while (n->next != nullptr)
{
    if (std::count(results.begin(), results.end(), n->value) > 0)
    {
        previous->next = n->next;
        delete n;
        n = previous->next;
    }
    else
    {
        results.push_back(n->value);
        previous = n;
        n = n->next;
    }
}

/**
* Remove duplicates without using a temporary buffer
*/
while (n->next != nullptr)
{
    Node* previous = n;
    Node* tosearch = n->next;
    while (tosearch != nullptr)
    {
        if (tosearch->value == n->value)
        {
            previous->next = tosearch->next;
            delete tosearch;
            tosearch = previous->next;
        }
        else
        {
            previous = tosearch;
            tosearch = tosearch->next;
        }
    }
    n = n->next;
}

/**
* Delete a linked list node
*/
void DeleteNode(Node* n)
{
    if (n->next == nullptr)
    {
        throw std::exception("Cannot delete last node");
    }

    Node* toDelete = n->next;
    n->value = toDelete->value;
    n->next = toDelete->next;
    delete toDelete;
}

/**
* Find the start of a circular loop if one exists
*/
Node* FindStartOfLoop(Node* n)
{
    Node* previous = nullptr;
    std::vector<Node*> nodes;

    while (n != nullptr)
    {
        if (std::find(nodes.begin(), nodes.end(), n) != nodes.end())
        {
            return previous;
        }
        nodes.push_back(n);
        previous = n;
        n = n->next;
    }

    return nullptr;
}