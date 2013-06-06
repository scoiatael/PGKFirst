#include "stickman_animation.hpp"


const vector< pair< pair<vec2, vec2> , float > > bentsT = { 
      pair< pair<vec2, vec2> , float >(pair<vec2, vec2>(vec2(-50 ,  50), vec2(-64,64)), 0.  ), 
      pair< pair<vec2, vec2> , float >(pair<vec2, vec2>(vec2(50  ,  50 ), vec2(64,64)), 45. ), 
      pair< pair<vec2, vec2> , float >(pair<vec2, vec2>(vec2(100.,  0.),vec2(120,0)), 135.), 
      pair< pair<vec2, vec2> , float >(pair<vec2, vec2>(vec2(50  ,  -50),vec2(64,-64)), 180.),
      pair< pair<vec2, vec2> , float >(pair<vec2, vec2>(vec2(-50 ,  -50),vec2(-64,-64)), 225.), 
      pair< pair<vec2, vec2> , float >(pair<vec2, vec2>(vec2(-100.,  0.),vec2(-120,0)), 315.) 
  };

void drawTriangleStrip(const vec2& where, const float& offsetz,const vector<vec2>& poz)
{
    glBegin(GL_TRIANGLE_STRIP);
      for(unsigned int i=0; i<poz.size(); i++)
      {
        glVertex3f(where.x + poz[i].x, where.y, offsetz + poz[i].y);
      }
    glEnd();

}

void drawTriangleStrip(const vec2& where, const float& offsetz, const vector<vector<int>>& poz)
{
    glBegin(GL_TRIANGLE_STRIP);
      for(unsigned int i=0; i<poz.size(); i++)
        glVertex3f(where.x + poz[i][0], where.y + poz[i][1], offsetz + poz[i][2]);
    glEnd();
}

struct stadium
{
  static const int STEPS = 100;
  static const int SIZE = 3;
  vector< pair< pair<vec2,vec2>, float>> bents;
  vector<stickman_animation> objs;
  vector<pair< vec2, float>> poss;
  //time_since_bent -> tsb
  vector<int> tsbs;
  pair<vec2, float> to_pos(const unsigned int& nr, const unsigned int& which)
  {
      vec2 temp = bents[which].first.first + (((float)nr+1)/(poss.size()+1))*(bents[which].first.second - bents[which].first.first);
      return pair<vec2, float>(temp, bents[which].second);
    
  }
  stadium(const stickman_animation& o1)
  : objs(SIZE), poss(SIZE), tsbs(SIZE) 
  {
    for(unsigned int i=0; i<bentsT.size(); i++)
    {
      unsigned int MAX_ST = 100;
      pair<vec2,vec2> cur = bentsT[i].first;
      pair<vec2,vec2> next = bentsT[(i+1)%bentsT.size()].first;
      for(unsigned int st = 0; st < MAX_ST; st++)
      {
        float alpha = (float)(st+1)/MAX_ST;
        vec2 nslerp = slerp(cur.second,next.second, alpha);
        float bent_angle = -todeg(angle(vec2(1,0), nslerp))+90;
        if(bent_angle != bent_angle)
          bent_angle = 0;
        bents.push_back(pair< pair<vec2, vec2> , float >(pair<vec2, vec2>(slerp(cur.first, next.first, alpha), nslerp), bent_angle ));
        cout <<alpha <<" "<< cur.second<<" " << next.second << " "<<  nslerp << " " << bent_angle << endl;
      }
    }
    for(int i=0; i<SIZE; i++)
    {
      poss[i] = to_pos(i, 0);
      objs[i] = o1;
      tsbs[i] = 0;
    }

  }
  void init ()
  {
    cout << bents.size() << endl;
    return;
  }
  void draw(vec2 where, float offsetz)
  {
   // glScalef(0.5,0.5,0.5);
      vector<vec2> poz =
        {  vec2(-240,140),
           vec2(240, 140),
           vec2(-240,-140),
           vec2(240, -140)
        }; 
    glColor3f(0.1,0.4,0.1);
    drawTriangleStrip(where, offsetz, poz);
    poz = {};
    for(unsigned int i=0; i<bents.size();i++)
    {
      poz.push_back(bents[i].first.first);
      poz.push_back(bents[i].first.second);
    }
    poz.push_back(bents[0].first.first);
    poz.push_back(bents[0].first.second); 
    glColor3f(0.4,0.1,0.1);
    drawTriangleStrip(where + vec2(0,0.1), offsetz, poz);
     /* { { -50,  50  },
        { -64,  64  },
        { 50,   50  },
        { 64,   64  },
        { 100,   0  },
        { 120,   0  },
        { 50,   -50 },
        { 64,   -64 },
        { -50,  -50 },
        { -64,  -64 },
        { -100,  0  },
        { -120,  0  },
        { -50,  50  },
        { -64,  64  }
      };*/
    for(unsigned int j=0; j<=poss.size();j++)
    {
      glColor3f(0.,0.,0.);
      glBegin(GL_LINES);
        for(unsigned int i=0; i<poz.size()-2; i+=2)
        {
          vec2 med = lerp(poz[i], poz[i+1], (float)(j)/poss.size());
          glVertex3f(where.x + med.x, where.y+0.11, offsetz + med.y);
          med = lerp(poz[i+2], poz[i+3], (float)(j)/poss.size());
          glVertex3f(where.x + med.x, where.y+0.11, offsetz + med.y);
        }
      glEnd();
    }
    //glScalef(0.5,0.5,0.5);
     vector<vector<int>> poz2 = 
        { { -240, 0,  140  },
          { -250, 20, 150  },
          { 240,  0,  140  },
          { 250,  20, 150  },
          { 240,  0,  -140 },
          { 250,  20, -150 },
          { -240, 0,  -140 },
          { -250, 20, -150 },
          { -240, 0,  140  },
          { -250, 20, 150  }
        }; 
    glColor3f(0.2,0.2,0.2);
    drawTriangleStrip(where, offsetz, poz2);
   // glScalef(2,2,2);
    /*    glBegin(GL_TRIANGLES);
      for(unsigned int i=0; i<poz.size(); i++)
      {
        glVertex3f(where.x + pos1.first.x + poz[i][0], where.y + poz[i][1], offsetz + pos1.first.y + poz[i][2]);
    //    cout << poz[i][0] << " " << poz[i][1] << " " << poz[i][2] << endl;
      }
    glEnd();*/
    float sc = 6;
    glLineWidth(sc/2);
    for(unsigned int i=0; i < poss.size();i++)
    {
      glPushMatrix();
      glTranslatef(where.x + poss[i].first.x, where.y + sc, offsetz + poss[i].first.y);
      glScalef(sc,sc,sc);
      glColor3f(0.,0.,0.);
      glRotatef(poss[i].second,0.,1.,0.);
      objs[i].draw(vec2(0,0), 0);
      glPopMatrix();
    }
    glLineWidth(1);
  }
  void animate(int delta)
  {
    for(unsigned int i=0; i < poss.size(); i++)
    {
      delta*=2;
      tsbs[i]+=delta + (rand() % (2));
     // poss[i] = to_pos(i, (tsbs[i]/STEPS)%bents.size());
      pair<vec2,float> next = to_pos(i, (1 + tsbs[i]/STEPS)%bents.size());
      pair<vec2,float> cur = poss[i];
      float sc = (float)(tsbs[i]%STEPS -1)/STEPS;
      poss[i].first = lerp(cur.first, next.first,sc) ;
      poss[i].second = lerp(cur.second, next.second,sc); 
      objs[i].animate(delta);
    }
  }
  void addtf(const int& d)
  {
    tsbs[0]+=d;
  }
  pair<vec2, float> get_cam_pos()
  {
    return poss[0];
  }
};
