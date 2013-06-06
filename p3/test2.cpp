#include <iostream>
#include <vector>
#include "stickman.hpp"
using namespace std;

int main()
{
	vec2 j(0,-1);
	vec2 j2(1,0);
	cout << angle(j,j2) << endl;
}
