#include "Graph.h"
#include "MyException.h"
#include <algorithm>
#include <iterator>

//-------------------------------------------------------------------------------------------------

/* C-tor of Graph */

Graph::Graph() 
{
	// load pictures
	if (!m_texture[0].loadFromFile("s1.png") | !m_texture[1].loadFromFile("s2.png") | !m_texture[2].loadFromFile("s3.png")
		| !m_texture[3].loadFromFile("s4.png") | !m_texture[4].loadFromFile("s5.png") | !m_texture[5].loadFromFile("s6.png"))
		throw FileException("Stick image is missing");
}

//-------------------------------------------------------------------------------------------------

/*This function craete new graph for the current stage*/
void Graph::createGraph(int num_of_sticks)
{
	// create sticks
	for (int i = 0; i < num_of_sticks; i++) 
	{
		m_sticks.push_back(make_shared<Stick>(m_texture[rand() % NUM_OF_DIFF_STICKS], i));

		//insert stick to sorted data structures.
		m_sticksX.insert({ (m_sticks[i])->getPosition().x, m_sticks[i] });
		m_sticksY.insert({ (m_sticks[i])->getPosition().y, m_sticks[i] });
	}
}

//-------------------------------------------------------------------------------------------------

/* This function is controlling the event - user pressed on the board */

bool Graph::eventHandler(Vector2f & mouse_location)
{
	auto stick = m_sticks.rbegin();

	if (!findStick(mouse_location, stick)) return false;	// user didn't press on a stick
	
	if (!checkInter(stick)) return false;					//check intersection
	
	// legal to pick the stick
	
	delStick(stick);

	return true;
}

//-------------------------------------------------------------------------------------------------

/* This function find the stick that the user pressed on */

bool Graph::findStick(Vector2f & mouse_location , revIt & it)
{	
	for (; it != m_sticks.rend(); ++it)
		if ((*it)->isContain(mouse_location)) return true;

	return false;
}

//-------------------------------------------------------------------------------------------------

/* Clear all data in graph */

void Graph::clean()
{
	m_sticks.clear();
	m_sticks.resize(0);
	m_sticksX.clear();
	m_sticksY.clear();
}

//-------------------------------------------------------------------------------------------------

/* This function create and check the intersection set of sticks */

bool Graph::checkInter(revIt & stick)
{
	/* Create two set - save the range of possible intersetion stick in them */
	set<shared_ptr<Stick>> setX, setY;

	makeBoundSet(setX ,m_sticksX, (*stick)->getPosition().x);
	makeBoundSet(setY, m_sticksY, (*stick)->getPosition().y);

	/* Make an intersetion set of the two set above */
	set<shared_ptr<Stick>> interSet;
	set_intersection(setX.begin(), setX.end(), setY.begin(), setY.end(), inserter(interSet, interSet.begin()));

	/* Check if stick is legal to move */
	for (auto it : interSet)
	{
		if ((*stick)->getIndex() < (*it).getIndex() &&
			doIntersect((*stick)->getPTop(), (*stick)->getPBottom(), (*it).getPTop(), (*it).getPBottom()))
			return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------

/* This function delete the stick from the data structures */

void Graph::delStick(revIt  stick)
{
	//delete from sort containers
	delFromMap(m_sticksX, (*stick)->getPosition().x, (*stick)->getIndex());
	delFromMap(m_sticksY, (*stick)->getPosition().y, (*stick)->getIndex());

	//delete from main container
	stick = decltype(stick){m_sticks.erase(std::next(stick).base())};
}

//-------------------------------------------------------------------------------------------------

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'

bool Graph::onSegment(const Vector2f & p, const Vector2f & q, const Vector2f & r)
{
	return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y));
}


//-------------------------------------------------------------------------------------------------

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise

int Graph::orientation(const Vector2f & p, const Vector2f & q, const Vector2f & r)
{
	// for details of below formula.
	int val = (int)((q.y - p.y) * (r.x - q.x) -
			  (q.x - p.x) * (r.y - q.y));

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

//-------------------------------------------------------------------------------------------------

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.

bool Graph::doIntersect(const Vector2f & p1, const Vector2f & q1, const Vector2f & p2, const Vector2f & q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

//-------------------------------------------------------------------------------------------------

/* This function delete a value from multimap */

void delFromMap(mapc &map, float key , int index)
{
	//find the all the keys with the same x value
	auto range = map.equal_range(key);

	auto it = range.first;

	for (; it != range.second; ++it) 
		if (it->second->getIndex() == index)
		{
			map.erase(it);
			break;
		}
}

//-------------------------------------------------------------------------------------------------

/* Make lower bound \ upper boundset for the current range */

void makeBoundSet(set<shared_ptr<Stick>>& set , mapc &stick , float range)
{
	/*set the range of possible intersection */
	mapc::iterator itLow = stick.lower_bound(range - STICK_SIZE.y);
	mapc::iterator itHigh = stick.upper_bound(range + STICK_SIZE.y);

	//copy to new set
	for (; itLow != itHigh; ++itLow) set.insert((*itLow).second);
}