
#----------------------------------------------------------------------
# SposÃ³b uÅ¼ycia:  make program.glfw (jeÅ›li mamy program.c uÅ¼ywajÄ…cy GLFW
#                 make program.glut (jeÅ›li mamy program.c uÅ¼ywajÄ…cy GLUT
#                 ...............................................
#----------------------------------------------------------------------
CXX=g++

CFLAGS= -std=c99 -O3 -Wall -march=native -I/usr/local/include -I/usr/X11R6/include -I/usr/include -I/opt/include 

LFLAGS= -L/usr/X11R6/lib -L/opt/lib -lGL -lGLU -lX11 -lXext -lXmu -lpthread -lm

.cpp.o:
	${CXX} -c ${CFLAGS} $<
%.o:    %.cxx
	${CXX} -c ${CFLAGS} $<

%.fltk: %.o
	${CXX} $< -lglut -lfltk -lfltk_gl -lfltk_forms -lfltk_images ${LFLAGS} -o $@

%.sdl:  %.o
	${CXX} $< -lSDL ${LFLAGS} -o $@

%.glfw: %.o 
	${CXX} $< -lglfw ${LFLAGS} -o $@  

%.glut: %.o
	${CXX} $< -lglut ${LFLAGS} -o $@  

clean:
	rm a.out *.o *~ core

