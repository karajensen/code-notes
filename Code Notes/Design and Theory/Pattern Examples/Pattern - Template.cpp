////////////////////////////////////////////////////////////////////////////////////////////////////////
//TEMPLATE PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Behavioural
USE: A skeleton algorithm that allows changing of methods called but doesn't change
     the overall algorithm. Good for updating algorithms and seperating code
-------------------------------------------------------------------------------------------*/

typedef void (*FunctionPointer)(vector<int>&v);
void MergeSort(vector<int>&v){ }
void LinearSort(vector<int>&v){ }

int main()
{
    FunctionPointer func = &MergeSort;
    MyAlgorithm(func);
}

void MyAlgorithm(FunctionPointer func)
{
    //MY ALGORITHM
    vector<int> myVec;
    myVec.push_back(0);
    myVec.push_back(1);
    myVec.push_back(myVec[0]-myVec[1]);
    func(myVec);

}