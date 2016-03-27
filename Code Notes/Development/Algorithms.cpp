///////////////////////////////////////////////////////////////////////////////////////////////////////
//GENERAL ALGORITHMS
///////////////////////////////////////////////////////////////////////////////////////////////////////

//CHANGE RANGE OF A VALUE
template<typename T> 
T ChangeRange(T value, T currentInner, T currentOuter, T newInner, T newOuter)
{
    return ((value-currentInner)*((newOuter-newInner)/(currentOuter-currentInner)))+newInner;
}

//DEGREES/RADIANS CONVERSION
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

//STRING: MAKE UPPER/LOWER CASE
std::transform(str.begin(), str.end(), str.begin(), &std::toupper);
std::transform(str.begin(), str.end(), str.begin(), &std::tolower);

//STRING: CASE INSENSITIVE COMPARISON
str1.size() == str2.size() &&
std::equal(str1.begin(), str1.end(), str2.begin(), 
    [](char c1, char s2){ return toupper(c1) == toupper(c2); });

//GET 1D INDEX FROM 2D COORD (UNIFORM GRID)
int index = rows * x + z;
int x = index / rows;
int z = index % rows;

//WHETHER NUMBER IS EVEN
bool isOdd = x % 2;

//GET DIGIT AT RADIX SIGNIFICANT POSITION (1, 10, 100..)
int digit = number/position % 10;

//GETTING COLOR COMPONENTS VIA BIT SHIFTING
unsigned int color;
int r = color & 0xFF;
int g = (color >> 8) & 0xFF;
int b = (color >> 16) & 0xFF;
int a = (color >> 24) & 0xFF;

//GENERATE FIBONACCI NUMBERS
//copies into container: 1 1 2 3 5 8 13 21 34 55
std::vector<int> v = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
std::adjacent_difference(v.begin(), v.end() - 1, v.begin() + 1, std::plus<int>());

//SAFE RELEASE
SafeRelease(&myPointer);
template <typename T> void SafeRelease(T** pObject)
{
    if(*pObject)
    {
        (*pObject)->Release();
        *pObject = nullptr;
    }
}

//BITWISE WITH BOOL
bool ifBothAreTrue   = myBool1 & myBool2
bool ifEitherAreTrue = myBool1 | myBool2  // either are true
bool ifEitherAreTrue = myBool1 ^ myBool2  // either are true but not both
bool success = true; success &= HasSucceeded(); // will lock in false if something fails

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
//RGB-HSV COLOUR BLENDING
///////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Converting RGB-HSV: http://www.poynton.com/PDFs/coloureq.pdf p15
/// Where rgb is [0,1]
/// </summary>
private HSV ConvertColour(RGB rgb)
{
    HSV hsv = new HSV();

    double min = Math.Min(Math.Min(rgb.Red, rgb.Blue), rgb.Green);
    double max = Math.Max(Math.Max(rgb.Red, rgb.Blue), rgb.Green);
    hsv.Saturation = max == 0.0f ? 0.0f : (max - min) / max;
    hsv.Value = max;

    double red = (max - rgb.Red) / (max - min);
    double green = (max - rgb.Green) / (max - min);
    double blue = (max - rgb.Blue) / (max - min);

    if (hsv.Saturation != 0)
    {
        if (rgb.Red == max && rgb.Green == min)
        {
            hsv.Hue = 5.0f + blue;
        }
        else if (rgb.Red == max && rgb.Green != min)
        {
            hsv.Hue = 1.0f - green;
        }
        else if (rgb.Green == max && rgb.Blue == min)
        {
            hsv.Hue = 1.0f + red;
        }
        else if (rgb.Green == max && rgb.Blue != min)
        {
            hsv.Hue = 3.0f - blue;
        }
        else if (rgb.Red == max || rgb.Red == min)
        {
            hsv.Hue = 3.0f + green;
        }
        else
        {
            hsv.Hue = 5.0f - red;
        }
    }

    hsv.Hue *= 60.0f;
    return hsv;
}

/// <summary>
/// Converting HSV-RGB: http://www.poynton.com/PDFs/coloureq.pdf p15
/// Where h is [0,360] and sv is [0,1]
/// </summary>
private RGB ConvertColour(HSV hsv)
{
    RGB rgb = new RGB();

    double hex = hsv.Hue / 60.0f;
    int primary = (int)Math.Floor(hex);
    double secondary = hex - primary;
    double a = (1.0f - hsv.Saturation) * hsv.Value;
    double b = (1.0f - (hsv.Saturation * secondary)) * hsv.Value;
    double c = (1.0f - (hsv.Saturation * (1.0f - secondary))) * hsv.Value;

    switch (primary)
    {
    case 0:
        rgb.Red = hsv.Value;
        rgb.Green = c;
        rgb.Blue = a;
        break;
    case 1:
        rgb.Red = b;
        rgb.Green = hsv.Value;
        rgb.Blue = a;
        break;
    case 2:
        rgb.Red = a;
        rgb.Green = hsv.Value;
        rgb.Blue = c;
        break;
    case 3:
        rgb.Red = a;
        rgb.Green = b;
        rgb.Blue = hsv.Value;
        break;
    case 4:
        rgb.Red = c;
        rgb.Green = a;
        rgb.Blue = hsv.Value;
        break;
    case 5:
        rgb.Red = hsv.Value;
        rgb.Green = a;
        rgb.Blue = b;
        break;
    case 6:
        rgb.Red = hsv.Value;
        rgb.Green = c;
        rgb.Blue = a;
        break;
    }

    return rgb;
}

/// <summary>
/// Colour Blending: http://www.stuartdenman.com/improved-color-blending/
/// Where blend value is [0-1]
/// </summary>
private HSV BlendColour(HSV one, HSV two, double blendvalue)
{
    HSV blend = new HSV();

    double invBlendValue = 1.0f - blendvalue;
    blend.Saturation = (one.Saturation * invBlendValue) + (two.Saturation * blendvalue);
    blend.Value = (one.Value * invBlendValue) + (two.Value * blendvalue);

    double hue1 = one.Hue;
    double hue2 = two.Hue;
    double difference = hue2 - hue1;

    if (hue1 > hue2)
    {
        hue2 = one.Hue;
        hue1 = two.Hue;

        blendvalue = invBlendValue;
        difference = -difference;
    }

    if (difference > 180)
    {
        hue1 += 360.0f;
        blend.Hue = ((int)(hue1 + (blendvalue * (hue2 - hue1)))) % 360;
    }
    else
    {
        blend.Hue = hue1 + (blendvalue * difference);
    }

    return blend;
}
