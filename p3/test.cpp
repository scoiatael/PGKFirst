#include "stickman.hpp"
#include <GL/glut.h>
#include <iostream>
#include <fstream>
using namespace std;
const int STEPS = 1;
int main()
{
	srand(time(NULL));
	for(int iii=0; iii< 2; iii++)
	{
    cout << "init..\n";
		stickman test1;
    stickman* test2;
    fstream f;
    f.open("base.data", ios_base::in);
    cout << "main part..\n";
    try
		{
      f >> test1;
      cout << "printing..\n";
      cout << test1 << endl;
      cout << *(test1.parts[0]) << endl;
      cout << "have fun..\n";
      test2 = new(stickman)(test1);
      cout << *test2 << endl;
		}
		catch(string S)
		{
			cout <<"woot " <<  S;
		}
	}
	return 0;
}
