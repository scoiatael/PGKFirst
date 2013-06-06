// Uciekajacy kwadrat/szescian 
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

GLfloat a=0;
GLfloat move = 0.0001;
GLfloat dir = 1; 

void idle()
{
	a += move * dir;
	if(a > 0.2 || a < 0)
	{
		dir *= -1;	
	}
	glutPostRedisplay();
}

void display(void)
{
//   printf("yep\n");
	glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1., 1.0);
   glLoadIdentity ();           
   glTranslatef(-0.8, -0.8, 0);
   glutWireCube (0.1);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
      case 'w':
	dir *=-1;
	break;
      case 'Q':
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
