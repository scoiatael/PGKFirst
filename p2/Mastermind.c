#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct rowGuess
{
	int t[4];
};

struct rowGuess history[12][2];
//0 - strzaly gracza, 1 - odpowiedzi
int shots;
//ile razy gracz juz strzelal
struct rowGuess chosen;
//wylosowana kombinacja
struct rowGuess current_pick;
int current_num;
//aktualnie wybierana kombinacja i ile wybrano elementow
int won;
//0 - gra sie toczy, 1 - wygral, inne wartosci - przegral
const int MAX_SHOTS = 10;
const double RADIUS = 0.1;
const double SEPARATOR = 0.15;
//const char MAP_K[6] = ['w', 'e', 'r', 't', 'u', 'i', 'o', 'p'];
const float MAP_C[6][3] =
	{{1. ,0. ,0.},
	 {0. ,1. ,0.},
	 {0. ,0. ,1.},
	 {0.5,0.5,0.},
	 {0. ,0. ,0.},
	 {1. ,1. ,1.}};

#define DrawOneLine(x1,y1,x2,y2) glColor3f(1.,1.,1.); glLoadIdentity(); glBegin(GL_LINES); \
	glVertex2f((x1),(y1)); glVertex2f((x2),(y2)); glEnd();

void print_row(struct rowGuess );
int czarny(struct rowGuess shot)
{
	for(int i=0; i<4; i++)
		if(shot.t[i] != 4)
			return 0;
	return 1;
}

struct rowGuess answer(struct rowGuess shot)
{
	struct rowGuess an, cho = chosen;
	int li[2] = {0,0};
	for (int i=0; i<4; i++)
		if(shot.t[i] == cho.t[i])
		{
			li[0]+=1;
			shot.t[i]=100;
			cho.t[i]=99;
		}
	for(int i=0; i< 4; i++)
		for(int j=0; j<4; j++)
			if(shot.t[i] == cho.t[j])
			{
				li[1]+=1;
				shot.t[i] = 100;
				cho.t[j] = 99; 
			}

	int poz = 0;
	for(int j=0; j<2; j++)
		for(int i=0; i<li[j];i++)
		{
			an.t[poz] = j + 4;
			poz++;
		}
	for(;poz < 4; poz++)
		an.t[poz] = 0;
	return an;
}

void idle()
{
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
	if(!won)
{
   const double TOP = 1., LEFT = -1., BOTTOM = -1., RIGHT = 1.;

	DrawOneLine(LEFT, BOTTOM + 2 * SEPARATOR , RIGHT, BOTTOM + 2 * SEPARATOR);
	DrawOneLine(LEFT + 4.5 * SEPARATOR, TOP, LEFT + 4.5 * SEPARATOR, BOTTOM);
	
   for(int i = 0; i < shots;i++)
	for(int j = 0; j<8; j++)
	{
		if(j < 4 || (j > 3 && history[i][1].t[j%4] != 0))
		{
	 	glColor3f (MAP_C[history[i][j/4].t[j%4]][0], MAP_C[history[i][j/4].t[j%4]][1],MAP_C[history[i][j/4].t[j%4]][2]) ;
	   	glLoadIdentity ();
		glTranslatef( LEFT + j*SEPARATOR + RADIUS + floor(j/4) * RADIUS,TOP - i*SEPARATOR - RADIUS,0);           
   		glutWireCube (RADIUS);
		}
	}
		for (int i = 0; i< 4; i++)
	{
		glColor3f(MAP_C[current_pick.t[i]][0], MAP_C[current_pick.t[i]][1], MAP_C[current_pick.t[i]][2]);
		glLoadIdentity();
		glTranslatef(LEFT + (i+1) * SEPARATOR, BOTTOM + SEPARATOR, 0);
		glutWireCube(RADIUS);
	}
DrawOneLine(LEFT + (current_num) * SEPARATOR + RADIUS, BOTTOM + RADIUS/2, LEFT + (current_num) * SEPARATOR +2* RADIUS, BOTTOM + RADIUS/2);
	  
}
else
{
const double TOP = 0.2, BOTTOM = -0.2, LEFT = -0.1, RIGHT =  0.1;
if( won == 2)
{
	DrawOneLine(LEFT, TOP, RIGHT, TOP);	
	DrawOneLine(LEFT, BOTTOM, LEFT, TOP);	
	DrawOneLine(RIGHT, BOTTOM, RIGHT, TOP);
	DrawOneLine( LEFT, BOTTOM, RIGHT, BOTTOM);	
	
	DrawOneLine(RIGHT, (TOP - 0.1), RIGHT - 0.1, (TOP - 0.1));
	DrawOneLine(RIGHT, (TOP - 0.2), RIGHT - 0.1, (TOP - 0.2));
	DrawOneLine(RIGHT, (TOP - 0.3), RIGHT - 0.1, (TOP - 0.3));
	
	DrawOneLine(RIGHT, BOTTOM, RIGHT, BOTTOM - 0.2);
	DrawOneLine(RIGHT - 0.1, BOTTOM, RIGHT - 0.1, BOTTOM - 0.2);
	DrawOneLine(RIGHT, BOTTOM - 0.2, RIGHT - 0.1, BOTTOM - 0.2);
}
else
{
	DrawOneLine(LEFT, TOP, RIGHT, TOP);	
	DrawOneLine(LEFT, BOTTOM, LEFT, TOP);	
	DrawOneLine(RIGHT, BOTTOM, RIGHT, TOP);
	DrawOneLine( LEFT, BOTTOM, RIGHT, BOTTOM);	
	
	DrawOneLine(RIGHT, (TOP - 0.1), RIGHT - 0.1, (TOP - 0.1));
	DrawOneLine(RIGHT, (TOP - 0.2), RIGHT - 0.1, (TOP - 0.2));
	DrawOneLine(RIGHT, (TOP - 0.3), RIGHT - 0.1, (TOP - 0.3));
	
	DrawOneLine(RIGHT, TOP, RIGHT, TOP + 0.2);
	DrawOneLine(RIGHT - 0.1, TOP, RIGHT - 0.1, TOP + 0.2);
	DrawOneLine(RIGHT, TOP + 0.2, RIGHT - 0.1, TOP + 0.2);
}
	for (int i = 0; i< 4; i++)
	{
		glColor3f(MAP_C[chosen.t[i]][0], MAP_C[chosen.t[i]][1], MAP_C[chosen.t[i]][2]);
		glLoadIdentity();
		glTranslatef(LEFT + (i+1) * SEPARATOR - 0.3, BOTTOM + SEPARATOR - 0.6, 0);
		glutWireCube(RADIUS);
	}

}
  glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glMatrixMode (GL_MODELVIEW);
}

void print_row(struct rowGuess dat)
{
	for(int i = 0; i< 4; i++)
		printf("%d ", dat.t[i]);
}
void print_hist()
{
	for(int i=0; i< shots; i++)
	{
		print_row(history[i][0]);
		printf(" ");
		print_row(history[i][1]);
		printf("\n");
	}
}

struct rowGuess wylosuj_pick()
{
	struct rowGuess new;
	for(int i = 0; i<4; i++)
		new.t[i] = rand()%4;
	return new;
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case '6':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
	current_pick.t[current_num] = key - '0' - 1;
	current_num += 1;
	current_num %= 4;
	break;
      case 27:
      case 'q':
      case 'Q':
         exit(0);
         break;
      case 'a':
	current_num -= 1;
	current_num += 4;
	current_num %= 4;
	break;
      case 'd':
	current_num += 1;
	current_num %= 4;
	break;
      case 'z':
      case 13:
	if(!won)
	{
		current_num = 0;
		history[shots][0] = current_pick;
		history[shots][1] = answer(current_pick);
		if(czarny(history[shots][1]))
		
	won = 1;
		shots+=1;
		if(shots == MAX_SHOTS)
			won = 2;
//		print_row(chosen);
//		printf("\n");
	}
	else 
	{
		current_num = 0;
		shots = 0;
		chosen = wylosuj_pick();
		for(int i=0; i< 4; i++)
			current_pick.t[i] = 1;
	}
	break; 
   }
  glutPostRedisplay();
}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   glClearColor (0.1, 0.1, 0.4, 0.1);
chosen = wylosuj_pick();
   glShadeModel (GL_FLAT);
   glMatrixMode(GL_MODELVIEW);
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(NULL);
   glutMainLoop();
   return 0;
}
