#include "food.h"
#include <iostream>
using namespace std;

Food::Food(string s, int cal)
{
	_name = s;
	_cal = cal;
}

Food Food:: operator+(const Food& f)
{
	return Food();
}

/*
write comments here
*/
bool Food:: operator<(const Food& f)
{
	// modify this function
	return true;
}

bool Food:: operator==(const Food& f)
{
	return true;
}


ostream& operator<<(ostream& os, const Food& f)
{
	os << f._name << " with " << f._cal << " calories";
	return os;
}
