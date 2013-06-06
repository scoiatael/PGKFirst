#include "stickman.hpp"
#include <fstream>
#include <string>
using namespace std;

stickman* obiekt;
unsigned int chosen=9;
const matr2 prawo(torad(90/20));
const matr2 lewo(torad(-90/20));
int ile_faz = 1;
fstream f;

void init()
{
	cout << "Podaj nazwe pliku:\n";
	string filename;
  filename = "base.data";
  f.open(filename, ios_base::in);
  obiekt = new(stickman);
  f >> *obiekt;
  f.close();
	cin >> filename;
	f.open(filename, ios_base::out);

  cout << *obiekt << endl;
  cout << *obiekt->parts[0] << endl;
}


void idle()
{
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	obiekt->draw(vec2(0.,0.), false);
	vec2 end(obiekt->parts[0]->main.get_end());
	if (chosen < stickman::size && chosen > 0)
	{
		end+=obiekt->parts[chosen]->main.get_end();
		if(chosen > 5)
		{
			end+=obiekt->parts[5]->main.get_end();
		  for(int t = chosen-2; t > 5; t-=2)
				end+=obiekt->parts[t]->main.get_end();
		}
		if(chosen < 5)
			for(int t = chosen-2; t > 0; t-=2)
				end+=obiekt->parts[t]->main.get_end();

	}
	glLoadIdentity();
	glTranslatef(end.x,end.y,0.);
	glColor3f(0.,0.,0.);
	glutSolidSphere(0.02,10,10);
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key) {
		case 'a':
			if(chosen < stickman::size)
				obiekt->parts[chosen]->rotate(lewo);
			break;
		case 'd':
			if(chosen < stickman::size)
				obiekt->parts[chosen]->rotate(prawo);
			break;
		case 'o':
			chosen += 1;
			chosen %= stickman::size;
      cout << chosen << endl;
			break;
		case 'p':
			chosen +=stickman::size-1;
			chosen %= stickman::size;
      cout << chosen << endl;
			break;
		case 'q':
   			f << 'e' << endl;
			f.close();
			exit(0);
			break;
		case 'e':
      f << "c" << endl;
			f << *obiekt << endl;
      break;
    case 'z':
      glMatrixMode(GL_PROJECTION);
      glRotatef(5, 0., 1., 0.);
      glMatrixMode(GL_MODELVIEW);
      break;
    case 'x':
      glMatrixMode(GL_PROJECTION);
      glRotatef(-5, 0., 1., 0.);
      glMatrixMode(GL_MODELVIEW);
      break;
	}
}

void reshape(int w, int h)
{}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   glClearColor (0.1, 0.1, 0.4, 0.1);
   glShadeModel (GL_FLAT);
   glMatrixMode(GL_MODELVIEW);
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(NULL);
   init();
   glutMainLoop();
}
