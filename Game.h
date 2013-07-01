#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Player.h"
#include "Quadtree.h"
#include <stdlib.h>
#ifndef PLATFORM_H
#define PLATFORM_H
#include "Platform.h"
#endif PLATFORM_H

class Game{
public:
	Game();
	void Start();
	void gameloop();

	Player* p1;
	Platform* plat1;
	Platform* ground;
	sf::RenderWindow window;
	sf::View view;
	Quadtree* qtree;

	enum gamestate{ Running, Exit };
	gamestate currentState;
private:
	
	sf::Texture bgtext;
	sf::Sprite bgsprite;
	sf::Clock timer;
	sf::Time dt;//delta time between each frame
};