#include "matrices2d.hpp"
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;


#define DrawOneLine(x1,y1,x2,y2) glColor3f(1.,1.,1.); glLoadIdentity(); glBegin(GL_LINES); \
	glVertex2f((x1),(y1)); glVertex2f((x2),(y2)); glEnd(); 

const float OFFSET_SIZE = 0.1;

struct stickman_part
{
	matr2 rotation;
	public:
	stickman_part(const matr2& rot)
	: rotation(rot)
	{}
	stickman_part()
	: rotation(IDENTITY_MATR2)
	{}
	void rotate(const matr2& arg)
	{
		rotation = rotation * arg;
	}
	matr2 get_rotation() const
	{
		return rotation;
	}
	virtual void draw(const vec2& where, char offsetz) const =0;
	virtual vec2 get_end() const =0;
};

struct stick : public stickman_part
{
	vec2 length;
  char offset;
	public:
	stick(const stick& arg)
	: stickman_part(arg.rotation), length(arg.length), offset(arg.offset)
	{}
	stick(const matr2& rot, const vec2& l)
	:	stickman_part(rot), length(l), offset(0)
	{}
	stick(const vec2& l)
	:	stickman_part(), length(l), offset(0)
	{}
	stick(const float& x, const float& y)
	:	stickman_part(), length(x,y), offset(0)
	{}
  void set_offset(char arg)
  {
    offset = arg;
  }
	vec2 get_end() const
	{
		return get_rotation() * length;
	}	
	void draw(const vec2& where, char offsetz) const
	{
		vec2 end = get_end();
		glColor3f(1.,1.,1.);
		glLoadIdentity();
		glBegin(GL_LINES);
		glVertex3f(where.get_x(),where.get_y(), (offsetz)*OFFSET_SIZE);
		glVertex3f(end.get_x()+where.get_x(), end.get_y()+where.get_y(), (offset+offsetz)*OFFSET_SIZE);
		glEnd();
	}
};

struct stick_node_rotation;

struct stick_node
{
	stick main;
	vector<stick_node*> table;
	stick_node()
	: main(0,0), table()
	{}
	stick_node(const stick& m, const vector<stick_node>& t)
	: main(m), table(t.size())
	{
    for(unsigned int i=0; i< t.size(); i++)
      table[i] = new(stick_node)(t[i]);
  }
	stick_node(const stick& m, const vector<stick_node*>& t)
	: main(m), table(t.size())
	{
    for(unsigned int i=0; i< t.size(); i++)
      table[i] = new(stick_node)(*t[i]);
  }
	stick_node(const stick& m)
	: main(m), table()
	{}
	stick_node(const float& arg1, const float& arg2)
	: main(stick(arg1, arg2)), table()
	{}
  stick_node(const stick_node& arg)
  : main(arg.main), table(arg.table.size())
  {
    for(unsigned int i=0; i < arg.table.size(); i++)
      table[i] = new(stick_node)(*arg.table[i]);
  }
  ~stick_node()
  {
    for(unsigned int i=0; i<table.size(); i++)
      delete(table[i]);
  }
	void draw(const vec2& where, char offsetz) const
	{
		main.draw(where, offsetz);
		for(auto i = table.begin(); i < table.end(); i++)
			(*i)->draw(main.get_end()+where, offsetz + main.offset);
	}
	void rotate(const matr2& arg)
	{
		main.rotate(arg);
		for(auto i = table.begin(); i < table.end(); i++)
			(*i)->rotate(arg);
	}
	void rotate(const stick_node_rotation& arg);
  vec2 get_end() const
  {
    return main.get_end();
  }
  friend ostream& operator<< (ostream& stream, const stick_node& arg);
};

ostream& operator<< (ostream& stream, const stick_node& arg)
{
  stream << "( ";
  stream <<arg.get_end() << "->";
  for(unsigned int i=0; i< arg.table.size(); i++)
    stream << endl << *arg.table[i] << "|";
  stream << ")";
  return stream;
}

struct stick_node_rotation
{
	matr2 main_rotation;
	vector<stick_node_rotation> table;
	stick_node_rotation(const stick_node_rotation& arg)
	: main_rotation(arg.main_rotation), table(arg.table)
	{}
	stick_node_rotation(const stick_node& start, const stick_node& end, const int& steps)
	: main_rotation(), table()
	{
		if(start.main.get_end() != end.main.get_end())
		{
			float skal = angle(start.main.get_end(), end.main.get_end());
			skal /= steps;
			main_rotation = matr2(skal);
		}
		for(unsigned int i = 0; i< start.table.size(); i++)
			table.push_back(stick_node_rotation(*start.table[i], *end.table[i], steps));
	}	
};

void stick_node::rotate(const stick_node_rotation& arg)
{
	main.rotate(arg.main_rotation);
	for(unsigned int i = 0; i < table.size(); i++)
		table[i]->rotate(arg.table[i]);
}

ostream& operator<< (std::ostream& stream, const stick_node_rotation& arg)
{
	stream << "--" << endl;
	stream << arg.main_rotation << endl;
	for(auto i = arg.table.begin(); i< arg.table.end(); i++)
		stream << (*i);
	return stream;
}

struct stickman
{
  static const unsigned int size = 12;
  stick_node *parts[size];
  stickman()
  {
   for(unsigned int i=0; i<size; i++)
    parts[i] = NULL; 
  }
  stickman(const float arg[size][2]);
  stickman(const stickman& arg);
  ~stickman()
  {
    delete(parts[0]);
  }
  void operator= (const stickman& arg)
  {
    parts[0] = new(stick_node)(*arg.parts[0]);
    refresh_parts();
  }
  void refresh_parts()
  {
  	parts[1] = (parts[0]->table[0]);
  	parts[2] = (parts[0]->table[1]);
  	parts[3] = (parts[1]->table[0]);
  	parts[4] = (parts[2]->table[0]);
  	parts[5] = (parts[0]->table[2]);
  	parts[6] = (parts[5]->table[0]);
  	parts[7] = (parts[5]->table[1]);
  	parts[8] = (parts[6]->table[0]);
  	parts[9] = (parts[7]->table[0]);
    parts[10] = (parts[8]->table[0]);
    parts[11] = (parts[9]->table[0]);
    for(unsigned int i=0; i<stickman::size;i++)
      parts[i]->main.set_offset(0);
    int map[2] = {1,7};
    for(int i=0; i<2; i++)
      parts[map[i]]->main.set_offset(-1);
    int map2[2] = {2,6};
    for(int i=0; i<2; i++)
      parts[map2[i]]->main.set_offset(1);
  }
	void draw(const vec2& where, char offsetz) const
	{ 
    parts[0]->draw(where, offsetz);
	  glLoadIdentity();
  	glColor3f(1.,1.,1.);
  	glTranslatef(where.x,where.y,offsetz*OFFSET_SIZE);
  	glutSolidSphere(parts[0]->get_end().length(),100,100);
	}
	void rotate(const matr2& arg)
	{
		parts[0]->rotate(arg);
	}
	void rotate(const stick_node_rotation& arg)
  {
    parts[0]->rotate(arg);
  }
  friend istream& operator>> (istream& stream, stickman& arg);
  friend ostream& operator<< (ostream& stream, const stickman& arg);
};

stickman::stickman(const float arg[size][2])
{
  vector<vector<int>> map = { {1,3}, {2,4}, {7,9,11}, {6,8,10}};
  vector<stick_node*> t(4);
  vector<vector<stick_node>*> rubbish_bin;
  for(int j=0; j<4; j++)
  {
    vector<stick_node> *old=new(vector<stick_node>){};
    for(int i=map[j].size()-1; i>=0; i--)
    {
      rubbish_bin.push_back(old);
      old = new(vector<stick_node>){stick_node(stick(arg[map[j][i]][0], arg[map[j][i]][1]), *old)};
      if(i==0)
      {
        t[j] = &((*old)[0]);
      }
    }
  }
  stick m(arg[0][0], arg[0][1]);
  vector<stick_node> table = {*t[0], *t[1], stick_node(stick(arg[5][0], arg[5][1]), vector<stick_node>{*t[2], *t[3]})};
  parts[0] = new(stick_node)(m, table);
  for(unsigned int i=0; i<rubbish_bin.size(); i++)
    delete(rubbish_bin[i]);
  refresh_parts();
}


istream& operator>> (istream& stream, stickman& arg)
{
  float table[stickman::size][2];
  for(unsigned int i=0; i<stickman::size; i++)
  {
    float t1, t2;
    stream >> t1 >> t2;
    table[i][0] = t1;
    table[i][1] = t2;
  }
  arg = stickman(table);
  return stream;
}

ostream& operator<< (ostream& stream, const stickman& arg)
{
	for(unsigned int i=0; i<stickman::size;i++)
	{
		vec2 temp = arg.parts[i]->get_end();
		stream << temp.x << " " << temp.y << " ";
    stream << endl;
	}
  return stream;
}

stickman::stickman(const stickman& arg)
{
  parts[0] = new(stick_node)(*(arg.parts[0]));
  refresh_parts();
}
