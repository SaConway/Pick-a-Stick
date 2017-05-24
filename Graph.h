#pragma once

#include <list>
#include <map>
#include <set>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Stick.h"
using namespace std;
using namespace sf;

//-------------------------------------------------------------------------------------------------

const int NUM_OF_DIFF_STICKS = 6;

//-------------------------------------------------------------------------------------------------
								
typedef multimap<float, shared_ptr<Stick> > mapc;
typedef reverse_iterator<vector<shared_ptr<Stick>>::iterator> revIt;

//-------------------------------------------------------------------------------------------------

class Graph
{
public:
	Graph();
	void createGraph(int);
	bool eventHandler(Vector2f &);
	void draw(RenderWindow & window) const { for (auto i : m_sticks) i->draw(window);  }
	bool findStick(Vector2f & , revIt&);
	int stickCount() const { return (int) m_sticks.size(); }
	bool checkInter(revIt&);
	void delStick(revIt);
	bool doIntersect(const Vector2f & , const Vector2f & , const Vector2f & , const Vector2f & );
	int orientation(const Vector2f & , const Vector2f & , const Vector2f & );
	bool onSegment(const Vector2f & , const Vector2f & , const Vector2f & );
	void clean();

private:
	vector <shared_ptr<Stick>> m_sticks;
	mapc m_sticksX;
	mapc m_sticksY;
	Texture m_texture[NUM_OF_DIFF_STICKS];					// stick pictures
};

void makeBoundSet(set<shared_ptr<Stick>> & ,mapc & , float) ;
void delFromMap(mapc &, float , int);