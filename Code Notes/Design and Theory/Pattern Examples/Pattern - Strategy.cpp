////////////////////////////////////////////////////////////////////////////////////////////////////////
//STRATEGY PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Behavioral
USE: Allows choosing an algorithm at runtime
-------------------------------------------------------------------------------------------*/

//STRATEGY CLASSES
class Strategy
{
public:
	enum{ MERGE, LINEAR };
	virtual void Implement()=0;
};
class MergeSort : public Strategy
{
public:
	virtual void Implement(){ /*do something*/ }
};
class LinearSort : public Strategy
{
public:
	virtual void Implement(){ /*do something else*/ }
};

//OBJECT CLASS
class GroupOfObjects
{
public:
	int Array[20];
	Strategy* strat;

	GroupOfObjects(){ strat = 0; }
	void SortArray(){ if(strat){ strat->Implement(); } }
	void SetStrategy(int choice)
	{
		switch(choice)
		{
			case Strategy::MERGE:  { strat = new MergeSort(); break; }
			case Strategy::LINEAR: { strat = new LinearSort(); break; }
		}
	}
	~GroupOfObjects(){ if(strat){ delete strat; } }
};

//USAGE
int main()
{
	GroupOfObjects grp;
	grp.SetStrategy(Strategy::MERGE);
	grp.SortArray();
};