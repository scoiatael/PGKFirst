#include "stickman_animation.hpp"
#include <fstream>
#include <string>
using namespace std;

vector<stickman*> poz;
unsigned int v = 1;
string filename;
bool cont = true;
stickman_animation* obj1;

int height;
int width;

void init()
{
  fstream file;
  file.open(filename, ios_base::in);
  obj1 = new(stickman_animation);
  file >> *obj1;
  file.close(); 
  obj1->init();
  cout << "closed and working\n";
}

void idle()
{

  if(cont)
  {
    obj1->animate(v);  
    glutPostRedisplay();
  }
}

void display()
{
  glLoadIdentity();
  glViewport (0, 0, (GLsizei) width, (GLsizei) height); 
  glClear(GL_COLOR_BUFFER_BIT);
  gluLookAt(0.,0.,1.,0.,0.,0.,0.,1.,0.);
  glScalef(0.3,0.3,0.3);
  glLineWidth(10);
  obj1->draw(vec2(0.,0.), 0);
  glLineWidth(1);
  glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 'o':
      if(cont)
      {
        v--;
        v%=100;
      }
      break;
    case 'p':
      if(cont)
      {
        v++;
        v%=100;
      }
      else
      {
        cont = true;
        idle();
        cont = false;
      }
      break;
    case 'q':
      exit(0);
    case ' ':
      cont = !cont;
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
    case 'v':
      glMatrixMode(GL_PROJECTION);
      glTranslatef(0.,0.,-0.2);
      glMatrixMode(GL_MODELVIEW);
      break;
    case 'c':
      glMatrixMode(GL_PROJECTION);
      glTranslatef(0.,0.,0.2);
      glMatrixMode(GL_MODELVIEW);
      break;
    
  }
}

void reshape(int w, int h)
{
  height = h;
  width = w;  
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60,1,0.01, 100);
  glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv)
{
  cout << "Podaj nazwe pliku:\n";
  cin >> filename;
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  glClearColor (0.1, 0.1, 0.4, 0.1);
  glShadeModel (GL_FLAT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(NULL);
  init();
  glutMainLoop();
  return 0;
}
