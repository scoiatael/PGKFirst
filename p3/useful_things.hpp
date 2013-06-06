#include <cmath>



inline float torad(float arg)
{
	return arg*M_PI/180;
}

inline float todeg(float arg)
{
	return arg*180/M_PI;
}

inline int tomp1(int arg)
{
	return (((arg%2)*2))-1;
}

float costosin(const float& val)
{
	return sin(acos(val));
}

float ci(const int& n, const float& val)
{
	if(n==0)
		return val;
	else
		return sqrt((1+ci(n-1, val))/2);
	return val;
}

float si(const int& n, const float& val)
{
	if(n==0)
		return val;
	else
		return si(n-1,val) / sqrt(2+2*ci(n-1,val));
	return val;
}

