#ifndef MATRICES2D_H

#define MATRICES2D_H

#include "useful_things.hpp"
#include <iostream>
#include<vector>
using namespace std;

class matr2;

struct vec2
{
	float x;
	float y;
	public:
	vec2()
	: x(0.), y(0.)
	{}
	vec2(const float& x, const float& y)
	: x(x), y(y)
	{}
	vec2(const vec2& a)
	: x(a.x), y(a.y)
	{}
	float get_x() const
	{
		return x;
	}
	float get_y() const
	{
		return y;
	}
	float length() const
	{
		return sqrt(pow(x,2)+pow(y,2));
	}
  void operator= (const vec2& arg)
  {
    x = arg.x;
    y = arg.y;
  }
	friend ostream& operator<<( ostream& stream, vec2 arg);
	friend matr2 operator* (const matr2& x, const matr2& y);
	friend vec2 operator* (const vec2& arg1, const float& arg2);
	friend vec2 operator* (const float& arg1, const vec2& arg2);
	friend vec2 operator* (const matr2& arg1, const vec2& arg2);
	friend vec2 operator+ (const vec2& arg1, const vec2& arg2);
	friend float il_skal (const vec2& arg1, const vec2& arg2);
	friend vec2 operator- (const vec2& arg1, const vec2& arg2);
	friend bool operator!= (const vec2& arg1, const vec2& arg2);
	friend vec2 operator- (const vec2& arg);
	friend int sgn(const vec2& arg1, const vec2& arg2);
	friend void operator+= (vec2& arg1, const vec2& arg2);
	float angle(const vec2& arg1, const vec2& arg2);
};

vec2 operator*(const vec2& arg1, const float& arg2)
{
	return vec2(arg1.x*arg2, arg1.y*arg2);
}

vec2 operator*(const float& arg1, const vec2& arg2)
{
	return arg2*arg1;
}

ostream& operator<<( ostream& stream, vec2 arg)
{
	stream << "(" << arg.x << ", " << arg.y << ")";
	return stream;
}

vec2 operator+(const vec2& arg1, const vec2& arg2)
{
	return vec2(arg1.x+arg2.x, arg1.y+arg2.y);
}

float il_skal(const vec2& arg1, const vec2& arg2)
{
	return  arg1.x*arg2.x+arg1.y*arg2.y;
}

vec2 operator-(const vec2& arg1, const vec2& arg2)
{
	return vec2(arg1.x-arg2.x, arg1.y-arg2.y);
}

bool operator!=(const vec2& arg1, const vec2& arg2)
{
	return (arg1.x != arg2.x) || (arg1.y != arg2.y);
}

vec2 operator-(const vec2& arg)
{
	return vec2(-arg.x,-arg.y);
}


void operator+= (vec2& arg1, const vec2& arg2)
{
	arg1 = arg1 + arg2;
}

float angle (const vec2& arg1, const vec2& arg2)
{
			
			float skal = il_skal(arg1, arg2)/(arg1.length()*arg2.length());
			skal = abs(acos(skal))*sgn(arg1, arg2);
			return skal;
}

struct matr2
{
	//columns:
	vec2 c1;
	vec2 c2;
	public:
	matr2()
	: c1(1.,0.), c2(0.,1.)
	{}
	matr2(const vec2& c1, const vec2& c2)
	:	c1(c1), c2(c2)
	{}
	//columns first
	matr2(const float& x1, const float& y1, const float& x2, const float& y2)
	:	c1(x1,y1), c2(x2,y2)
	{}
	// alpha - angle in radians
	matr2(const float& alpha)
	: c1(cos(alpha), sin(alpha)), c2(-sin(alpha), cos(alpha))
	{}
	matr2(const matr2& arg)
	:	c1(arg.c1), c2(arg.c2)
	{}
	vec2 get_c1() const
	{
		return c1;
	}
	vec2 get_c2() const
	{
		return c2;
	}
	friend matr2 operator* (const matr2& x, const matr2& y);
	friend ostream& operator<< (ostream& stream, matr2 arg);
	friend vec2 operator* (const matr2& arg1, const vec2& arg2);
};

matr2 operator* (const matr2& x, const matr2& y)
{

	return matr2(vec2(x.c1.x*y.c1.x + x.c2.x*y.c1.y, x.c1.y*y.c1.x + x.c2.y*y.c1.y), vec2(x.c1.x*y.c2.x + x.c2.x*y.c2.y, x.c1.y*y.c2.x + x.c2.y*y.c2.y));
}

ostream& operator<< (ostream& stream, matr2 arg)
{
	stream << "|" << arg.c1 << "|\n|" << arg.c2 << "|";
	return stream;
}

vec2 operator* (const matr2& arg1, const vec2& arg2)
{
	return vec2(arg1.c1.x * arg2.x + arg1.c2.x * arg2.y, arg1.c1.y * arg2.x + arg1.c2.y * arg2.y);
}


int sgn(const vec2& arg1, const vec2& arg2)
{
	matr2 rot(arg1.x, -arg1.y, arg1.y, arg1.x);
	vec2 arg2rot = rot*arg2;
	if(arg2rot.y == 0)
		return 0;
	int sign = abs(arg2rot.y)/arg2rot.y;
//	if(sign != 1. && sign != -1.)
//		cout << arg1 << " " << arg2 << " " << arg2rot << endl;
	return sign;
}

const matr2 IDENTITY_MATR2(1.,0.,0.,1.);

inline float lerp(const float& a, const float& b, const float& alpha)
{
  return (1-alpha)*a + alpha*b;
}

inline vec2 lerp(const vec2& a, const vec2& b, const float& alpha)
{
  return (1-alpha)*a + alpha*b;
}

inline vector<float> lerp(const vector<float>& a, const vector<float>&b, const float& alpha)
{
  vector<float> w = {};
  for(unsigned int i=0; i<a.size(); i++)
    w.push_back(lerp(a[i],b[i], alpha));
  return w;
}

inline vec2 slerp(const vec2& a, const vec2&b, const float& alpha)
{
  float om = angle(a,b);
  return ((sin((1-alpha)*om)/sin(om))*a + (sin(alpha*om)/sin(om))*b);
}


#endif
