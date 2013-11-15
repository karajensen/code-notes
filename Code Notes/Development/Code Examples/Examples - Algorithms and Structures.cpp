////////////////////////////////////////////////////////////////////////////////////////////////////
//BINARY SEARCH
////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////
//BREADTH FIRST SEARCH
////////////////////////////////////////////////////////////////////////////////////////////////////

BreadthFirstSearch(rootNode)
    Create FIFO (First in first out) Queue
    Push rootNode onto Queue
    while(Queue !Empty)
        Pop v from start of Queue
        set v as visited
        for(each possible move at v->gameBoard)
            create childNode
            push childNode onto Queue

////////////////////////////////////////////////////////////////////////////////////////////////////
//DEPTH FIRST SEARCH
////////////////////////////////////////////////////////////////////////////////////////////////////

DepthFirstSearch(v)
    set v as visited
    for(each possible move at v->gameBoard)
        create childNode
        call DepthFirstSearch(childNode)

////////////////////////////////////////////////////////////////////////////////////////////////////
//INSERTION SORT
////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////
//SHELL SORT
////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////
//MERGE SORT
////////////////////////////////////////////////////////////////////////////////////////////////////

string merge(string left, string right)
{
    string result = "";
    //while either list has elements
    while(left.size() > 0 || right.size() > 0)
    {
        //if both have elements
        if(left.size() > 0 && right.size() > 0)
        {
            //add smallest to result
            if(left[0] <= right[0])
            {
                result += left[0];
                left.erase(left.begin());
            }
            else
            {
                result += right[0];
                right.erase(right.begin());
            }
        }
        else if(left.size() > 0)
        {
            result += left[0];
            left.erase(left.begin());
        }
        else if(right.size() > 0)
        {
            result += right[0];
            right.erase(right.begin());
        }
    }
    return result;
}
string merge_sort(string s)
{
    //check container size
    if(s.size() <= 1)
        return s;

    //split list into two sublists
    string left = "", right = "";
    int middle = s.size()/2;
    for(unsigned int i = 0; i < middle; ++i)
        left += s[i];
    for(unsigned int i = middle; i < s.size(); ++i)
        right += s[i];

    //pass strings until size is 1
    left = merge_sort(left);
    right = merge_sort(right);

    //sort and merge the resulting string
    return merge(left, right);
}

int main()
{
    string mystring = "hellothisisatest";
    cout << mystring << endl;
    mystring = merge_sort(mystring);
    cout << mystring << endl;

    char current = mystring[0];
    for(unsigned int i = 1; i < mystring.size(); ++i)
    {
        if(current == mystring[i])
        {
            //remove from string
            for(unsigned int j = i+1; j < mystring.size(); ++j)
                mystring[j-1] = mystring[j];
            mystring.pop_back();
            i--;
        }
        else
            current = mystring[i];
    }
    cout << mystring << endl;

    cin.get();

};

////////////////////////////////////////////////////////////////////////////////////////////////////
//MINIMAX TREES
////////////////////////////////////////////////////////////////////////////////////////////////////

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

//Determines a value of how good a move could be
STATIC EVALUATION FUNCTION(NodeGameState,Player)

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
        
        //MOVE DOWN THE TREE
        ChildNode = MINIMAX(ChildNode,depth-1,nextplayer,alpha,beta)

        //MINIMAX UP TREE
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