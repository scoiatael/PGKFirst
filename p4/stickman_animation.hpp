#include "stickman.hpp"

struct stickman_animation
{
  static const unsigned int STEPS = 300;
  unsigned int phase_nr;
  unsigned int time_since_start;
  stickman doll;
  vector<stickman*> phases;
  stickman_animation()
  : doll(), phases()
  {
    time_since_start=0;
    phase_nr=0;
  }
  stickman_animation(const stickman& arg)
  : doll(arg), phases()
  {
    time_since_start=0;
    phase_nr=0;
  }
  void operator= (const stickman_animation& arg)
  {
    doll = arg.doll;
    phases = arg.phases;
    time_since_start = arg.time_since_start;
    phase_nr = arg.phase_nr;
  }
  stickman_animation(const stickman& arg, const vector<stickman*> arg2)
  : doll(arg), phases(arg2)
  {
    phase_nr = phases.size();
    time_since_start=0;
  }
  stickman_animation(const stickman_animation& arg)
  : phase_nr(arg.phase_nr), time_since_start(arg.time_since_start), doll(arg.doll), phases(arg.phases)
  {}
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
    doll = stickman(*phases[(time_since_start/STEPS)%phase_nr]);
    doll.rotate(stick_node_rotation(*doll.parts[0], *phases[(1 + time_since_start/STEPS)%phase_nr]->parts[0], ((float)(time_since_start%STEPS))/STEPS));
  }
  void draw(const vec2& where, int offsetz)
  {
    doll.draw(where, offsetz);
  }
  friend istream& operator>> (istream& stream, stickman_animation& arg);
};

istream& operator>> (istream& file, stickman_animation& arg)
{
  char c = 'i';
  file >> c;
  stickman obj_first, obj;
  file >> obj_first;
  file >> c;
  for(int i =0; c== 'c' ; i++, file >> c)
  {
    stickman* temp = new(stickman);
    file >> *temp;
    arg.phases.push_back( temp);
  }
  arg = stickman_animation(obj_first, arg.phases);
  return file;
}
