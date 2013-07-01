#include "Player.h"

Player::Player(int x=50, int y=10) :
	xvel(0),
	yvel(0),
	gr_acc(0.75),
	direction(0),
	maxxvel(400),
	xfriction(0.98),
	yfriction(0.2),
	jump(false),
	maxyvel(1000)
{
	movedir[0] = false;
	movedir[1] = false;
	texture.loadFromFile("resources/tempobj.png");
	sprite.setTexture(texture);
	state = air;
	sprite.setPosition(x, y);

	//player sprite is currently a 25x25 png image. 
	//these points are the x,y coordinates of 8 points around the player
	//forming an octagon to check for collision detection
	//...this idea failed.
	points[0].x = 6.2;
	points[1].x = 18.8;
	points[2].x = 25;
	points[3].x = 25;
	points[4].x = 18.8;
	points[5].x = 6.2;
	points[6].x = 0;
	points[7].x = 0;
	points[0].y = 0;
	points[1].y = 0;
	points[2].y = 6.2;
	points[3].y = 18.8;
	points[4].y = 25;
	points[5].y = 25;
	points[6].y = 18.8;
	points[7].y = 6.2;
}

Player::~Player()
{}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}


void Player::update(sf::Time delta, sf::Event& evt, sf::View& v, std::vector<Platform*>* colPositive)
{
	sf::Vector2f pos = sprite.getPosition();//current position of sprite
	sf::Vector2f vpos = v.getCenter();//center of view position
	float ydist=0, xdist=0;
	
	//check for key presses
	//move sprite accordingly
	if(evt.type == sf::Event::KeyPressed)
	{
		if(evt.key.code == sf::Keyboard::Right)
		{
			movedir[1] = true;
			direction = 1;
		}
		if(evt.key.code == sf::Keyboard::Left)
		{
			movedir[0] = true;
			direction = 0;
		}
		if(evt.key.code == sf::Keyboard::Up)
		{
			if(state == ground) jump = true;
		}
	} else if(evt.type == sf::Event::KeyReleased)
	{
		if(evt.key.code == sf::Keyboard::Right) movedir[1] = false;
		if(evt.key.code == sf::Keyboard::Left)  movedir[0] = false;
		if(evt.key.code == sf::Keyboard::Up) jump = false;
	}

	if(movedir[0]||movedir[1])
	{
		//when button is pressed( left or right), add velocity
		xvel+=3;
	} else if((movedir[1] == false && direction == 1)||
			   (movedir[0] == false && direction == 0))
	{
		//when button is released, add friction (decrease velocity)
		if(state == ground) xvel *= xfriction;
	} 

	//set the maximum velocities (x, y)
	if(xvel >= maxxvel) xvel = maxxvel;
	if(yvel >= maxyvel) yvel = maxyvel;

	if(pos.y <= 455)
	{
		if(jump == true)
		{
			yvel = -500;
			jump = false;
		}
		ydist = yvel*delta.asSeconds() + (1/2)*gr_acc*delta.asSeconds()*delta.asSeconds();
		yvel += gr_acc;
	} else {
		pos.y = 455;
		state = ground;
		yvel=-yvel*yfriction;
	}
	
	if(pos.y == 455) state = ground;
	if(pos.y < 455) state = air;

	if(pos.x <= 640-25 && pos.y >= 0)
	{
		if(direction == 0)
			xdist = -xvel*delta.asSeconds();
		if(direction == 1)
			xdist = xvel*delta.asSeconds();
	} else {
		if(pos.x >= 640 - 25)
		{
			pos.x = 615;
			xvel=-xvel;
		}
	}

	//camera view adjustments
	if(pos.x == 0 || pos.x < 0) 
	{ 
		v.setCenter(160, vpos.y);
	} else if(pos.x >= 480) 
	{
		v.setCenter(480, vpos.y);
	} else {
		v.setCenter(pos.x*2/3+160, vpos.y);
	}
	
	
	//collision check with all colliding platforms
	if(colPositive->size() > 0)
	{
		auto iter = colPositive->begin();
		for(iter; iter != colPositive->end(); ++iter)
		{
			for(int i=0; i < 8 ; i++)
			{
				if((*iter)->colCheck(pos.x + points[i].x, pos.y + points[i].y))
				{
					//interpolate position of player sprie
					float t = 1;
					while(t>= 0)
					{
						int x = (pos.x - prevpix.x)*t + prevpix.x;
						int y = (prevpix.y - pos.y)*t + pos.y;

						if((*iter)->colCheck(x + points[i].x, y + points[i].y))
							t-=0.2;
						else
							pos.x = x;
							pos.y = y;
							break;
					}
					break;//questionable break
				}
			}
		}
	}
	prevpix.x = pos.x;
	prevpix.y = pos.y;

	//finally change the x and y positions of the player sprite
	sprite.setPosition(pos.x + xdist, pos.y + ydist);
}
