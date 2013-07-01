#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

#ifndef PLATFORM_H
#define PLATFORM_H
#include "Platform.h"
#endif PLATFORM_H

class Quadtree {
public:
	Quadtree(int, sf::Rect<int>);
	void clear();
	void insert(Platform*, sf::Rect<int>);
	std::vector<Platform*> retrieve(std::vector<Platform*>, sf::Rect<int>);
	
private:
	void split();
	int getQuadrant(sf::Rect<int>);

	int MAX_OBJ;
	int MAX_LVL;
	int level;
	sf::Rect<int> bounds;
	std::map<Platform*, sf::Rect<int>> objects;
	Quadtree* nodes[4];
};