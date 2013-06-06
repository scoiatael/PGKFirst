#include "stickman.hpp"

struct stickman_animation
{
  static const unsigned int STEPS = 300;
  unsigned int phase_nr;
  unsigned int time_since_start;
  stickman doll;
  vector<stickman*> phases;
  stickman_animation(const stickman& arg)
  : doll(arg)
  {
    time_since_start=0;
    phase_nr=0;
  }
  stickman_animation(const stickman& arg, const vector<stickman*> arg2)
  : doll(arg), phases(arg2)
  {
    phase_nr = phases.size();
    time_since_start=0;
  }
  void add_phase(stickman* phase)
  {
    phase_nr++;
    phases.push_back(phase);
  }
  void init()
  {
    if(phases.size()==0)
    {
      cerr << "Not enough phases to animate.\n";
      exit(1);
    }
    cout << "phase nr: " << phases.size() << endl;
  }
  void animate(const unsigned int& delta)
  {
    time_since_start+=delta;
        if(time_since_start%(STEPS*phase_nr)==0)
        {
          doll = stickman(*phases[0]);
        }
    for(unsigned int i=0; i<delta; i++)
     doll.rotate(stick_node_rotation(*doll.parts[0], *phases[(time_since_start/STEPS)%phase_nr]->parts[0], STEPS - (time_since_start%STEPS)));
  }
  void draw(const vec2& where, int offsetz)
  {
    doll.draw(where, offsetz);
  }
};
