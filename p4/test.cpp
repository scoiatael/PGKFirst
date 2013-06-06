#include "stadium.hpp"
#include "viewports.hpp"
#include <fstream>
#include <string>
using namespace std;

vector<stickman*> poz;
string filename("run.anim");
stickman_animation* obj1;
stadium* arena;
vector<viewport*> views;
viewport* topdown;
int chosen_viewport;

float rot1,rot2,rot3;
float v1, v2, v3;
int height;
int width;
bool last;

void init()
{
  fstream file;
  file.open(filename, ios_base::in);
  obj1 = new(stickman_animation);
  file >> *obj1; 
  file.close();
  obj1->init();
  arena = new(stadium)(*obj1);
  arena->init();
  topdown = new(viewport)(TOPDOWN);
  views.push_back(new(viewport)(BEHIND));
  views[0]->init();
  views.push_back(new(viewport)(EYE_VIEW));
  views[1]->init();
}

void idle()
{
   int v = 10;
   arena->animate(v);  
   glutPostRedisplay();
}

void display()
{
  vector< vector<int> > poz = 
    {
      {0, 0, (GLsizei) width, (GLsizei) height},
      {(GLsizei) (3*width/4), 0, (GLsizei) width/4, (GLsizei) height/4}
    };
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_LINE_SMOOTH);
  glClear(GL_COLOR_BUFFER_BIT);
  for(unsigned int i=0; i<poz.size(); i++)
  {
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    glScissor(poz[i][0],poz[i][1],poz[i][2],poz[i][3]);
    glViewport(poz[i][0],poz[i][1],poz[i][2],poz[i][3]);
    glutWireCube(0.5);
//    float a = 0.05, b=0.005;
//    float sc = a*(i-1)+b*(i);
    float sc = 0.005;
    glScalef(sc,sc,sc);
    if(i==1)
      topdown->set(arena->get_cam_pos());
    else
      views[chosen_viewport]->set(arena->get_cam_pos());
    glRotatef(rot1, 1, 0, 0);
    glRotatef(rot2, 0,1,0);
    glRotatef(rot3, 0,0,1);
    glTranslatef(v1,v2,v3);
    arena->draw(vec2(0.,0.),0);
    glMatrixMode(GL_MODELVIEW);
    glFlush(); 
  }
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_MULTISAMPLE);
  glDisable(GL_LINE_SMOOTH);
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 'q':
      exit(0);
    case 'a':
      chosen_viewport+=1;
      chosen_viewport%=views.size();
      break;
    case 's':
      chosen_viewport-=1;
      chosen_viewport%=views.size();
      break;
    case 'b':
      rot2+=1;
      break;
    case 'n':
      rot2-=1; 
      break;
    case 'v':
      rot1+=1;
      break;
    case 'c':
      rot1-=1; 
      break;
    case 'z':
      rot3-=1;
      break;
    case 'x':
      rot3+=1;
      break;
    case 'd':
      v1+=1;
      break;
    case 'f':
      v1-=1;
      break;
    case 'g':
      v2+=1;
      break;
    case 'h':
      v2-=1;
      break;
    case 'j':
      v3+=1;
      break;
    case 'k':
      v3-=1;
      break;
    case ',':
      if(last)
      {
        last = !last;
        arena->addtf(5);
      }
      break;
    case '.':
      if(!last)
      {
        last = !last;
        arena->addtf(5);
      }
      break;
  }
  glutPostRedisplay();    
}

void reshape(int w, int h)
{
  height = h;
  width = w;  
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
 // glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
  gluPerspective(60,1,0.01,100);
  glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
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
