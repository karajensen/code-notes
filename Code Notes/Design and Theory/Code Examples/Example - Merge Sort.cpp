
#include <string>
#include <iostream>
using namespace std;

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