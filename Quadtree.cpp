#include "Quadtree.h"

Quadtree::Quadtree(int c_level, sf::Rect<int> c_bounds) :
	MAX_OBJ(5),
	MAX_LVL(5)
{
	level = c_level;
	bounds = c_bounds;

	for(int i=0; i<4; ++i) nodes[i] = NULL;
}

void Quadtree::clear()
{
	objects.clear();

	for(int i=0; i<4; ++i)
	{
		if(nodes[i] != NULL)
		{
			nodes[i]->clear();
			nodes[i] = NULL;
		}
	}
}

void Quadtree::split()
{
	int subWidth = bounds.width/2;
	int subHeight = bounds.height/2;

	int x = bounds.left;
	int y = bounds.top;

	nodes[0] = new Quadtree(level + 1, sf::Rect<int>(x + subWidth, y            , subWidth, subHeight));
	nodes[1] = new Quadtree(level + 1, sf::Rect<int>(x           , y            , subWidth, subHeight));
	nodes[2] = new Quadtree(level + 1, sf::Rect<int>(x	         , y + subHeight, subWidth, subHeight));
	nodes[3] = new Quadtree(level + 1, sf::Rect<int>(x + subWidth, y + subHeight, subWidth, subHeight));
}

int Quadtree::getQuadrant(sf::Rect<int> _rect)
{
	int index = -1;
	bool topQuad, bottomQuad;
	int xMid = bounds.left + bounds.width/2;
	int yMid = bounds.top + bounds.height/2;

	if(_rect.top < yMid && _rect.top + _rect.height < yMid) topQuad = true;
	else topQuad = false;

	if(_rect.top > yMid) bottomQuad = true;
	else bottomQuad = false;

	if(_rect.left < xMid && _rect.left + _rect.width < xMid)
	{
		if(topQuad) index = 1;
		else if(bottomQuad) index = 2;
	}

	if(_rect.left > xMid)
	{
		if(topQuad) index = 0;
		else if(bottomQuad) index = 3;
	}
	return index;
}

void Quadtree::insert(Platform* p, sf::Rect<int> _rect)
{
	if(nodes[0] != NULL)
	{
		int index = getQuadrant(_rect);
		if(index != -1)
		{
			nodes[index]->insert(p, _rect);
			return;
		}
	}

	objects.insert(std::pair<Platform*, sf::Rect<int>>(p, _rect));
	if(objects.size() > MAX_OBJ && level < MAX_LVL)
	{
		if(nodes[0] == NULL) split();

		auto itr = objects.begin();
		while(itr != objects.end())
		{
			int index = getQuadrant((*itr).second);
			if(index != -1)
			{
				sf::Rect<int> temp = (*itr).second;

				/*auto iter = objects.begin();
				for(iter; iter < objects.end(); iter++) 
					if((*iter) == objects.at(i)) break;
				*/

				
				nodes[index]->insert((*itr).first, temp);
				objects.erase(itr);
			} else {
				itr++;
			}
		}
	}
}

std::vector<Platform*> Quadtree::retrieve(std::vector<Platform*> returnObjects, sf::Rect<int> rect)
{
	int index = getQuadrant(rect);
	if(index != -1 && nodes[0] != NULL)
	{
		nodes[index]->retrieve(returnObjects, rect);
	}
	auto iter = objects.begin();
	for(iter; iter != objects.end(); iter++)                                  
		returnObjects.push_back((*iter).first);
		
	return returnObjects;
}