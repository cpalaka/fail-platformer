#include <SFML\Graphics.hpp>
#include <iostream>

#ifndef PLATFORM_H
#define PLATFORM_H
#include "Platform.h"
#endif PLATFORM_H

class Player{
public:
	Player(int, int);
	~Player();
	void draw(sf::RenderWindow& window);
	void update(sf::Time, sf::Event&, sf::View&, std::vector<Platform*>* colPositive);
	sf::Sprite sprite;
private:
	sf::Texture texture;

	sf::Vector2i prevpix;
	sf::Vector2f points[8]; //set of 8 points around player to check for collision
	enum PlayerState { ground, air };
	PlayerState state;
	bool movedir[2];//0 left, 1 right
	bool jump;
	float xvel, maxxvel;
	float xfriction, yfriction;
	float yvel,maxyvel;
	float gr_acc;
	bool direction;// 0 for left, 1 for right
};