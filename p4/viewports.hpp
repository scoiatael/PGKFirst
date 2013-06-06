#include "matrices2d.hpp"
enum View
{
  TOPDOWN,
  EYE_VIEW,
  BEHIND
};

struct viewport
{
  View type;
  viewport(View t)
    : type(t)
  {}
  viewport()
    : type(TOPDOWN)
  {}
  static void set_topdown()
  {
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.,500.,0.,0.,0.,0.,0.,0.,1.);
  }
  void set(pair<vec2, float> where)
  {
    float angle = torad(where.second);
    vec2 cam_displ(cos(angle), -sin(angle));
    vec2 LookFrom, LookAt;
    int heightFrom, heightAt;
    switch(type)
    {
      case TOPDOWN:
       LookAt = where.first;
       LookFrom = where.first - 0.1 * cam_displ;
       heightAt = 0;
       heightFrom = 100;
       break;
      case BEHIND:
        LookFrom = where.first - 30*cam_displ;
        LookAt = where.first;
        heightAt = 1;
        heightFrom = 20;
        break;
      case EYE_VIEW:
      LookFrom = where.first + cam_displ;
      LookAt = where.first + 300*cam_displ;
      heightAt = 6;
      heightFrom = 6.2;
    }
    gluLookAt(LookFrom.x,heightFrom,LookFrom.y, LookAt.x,heightAt,LookAt.y,0.,1.,0.);
  }
  void init()
  {}
};
