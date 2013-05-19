///////////////////////////////////////////////////////////////////////////////////////////////////////
//PROXY PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Structural
USE: Creates an object/reference which, when changes are done to it, forwards them to the real object
	 Can keep track of number of proxies created and delete object once none left- smart pointer
-------------------------------------------------------------------------------------------*/

//EG1: STL Auto Pointers
auto_ptr<double> ap(new double);