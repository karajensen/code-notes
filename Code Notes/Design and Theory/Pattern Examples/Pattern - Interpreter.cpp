///////////////////////////////////////////////////////////////////////////////////////////////////////
//INTERPRETER PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Behavioural
USE: Used to decode symbols from a string (ie. have a class for each symbol in a sentence)
	 Used in L-systems to decode the generated string and move the turtle
-------------------------------------------------------------------------------------------*/

for(unsigned int i = 0; i < myString.size(); i++)
{
	switch(myString[i])
	{
	case 'a':
		//do something
		break;
	case 'b':
		//do something else
		break;
	case 'c':
		//even something else
		break;
	}
}