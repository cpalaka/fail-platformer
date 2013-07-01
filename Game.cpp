#include "Game.h"

Game::Game() :
	currentState(Running)
{
	p1 = new Player(50,10);
	plat1 = new Platform("resources/plat1.png", 300, 300);
	ground = new Platform("resources/ground.png", -10, 460);

	bgtext.loadFromFile("resources/bg.png");
	bgsprite.setTexture(bgtext);
	bgsprite.setPosition(0,0);

	qtree = new Quadtree(0, sf::Rect<int>(0,0,640, 480));

	window.create(sf::VideoMode(640, 480), "Platformer");
	view.reset(sf::FloatRect(0,240,320, 240));
	view.setViewport(sf::FloatRect(0,0,1,1));
}

void Game::Start()
{
	while(currentState != Exit)
	{
		gameloop();
	}
	window.close();
}

void Game::gameloop()
{
	sf::Event evt;
	window.pollEvent(evt);
	
		switch(evt.type)
		{
		case sf::Event::Closed:
			currentState = Exit;
			break;
		case sf::Event::KeyPressed:
			if(evt.key.code == sf::Keyboard::Escape) currentState = Exit;
			break;
		}
		//set up the timer
		dt = timer.restart();
		
		//set up quadtree
		qtree->clear();
		qtree->insert(plat1, (sf::Rect<int>)plat1->sprite.getGlobalBounds());
		//qtree->insert(ground, (sf::Rect<int>)ground->sprite.getGlobalBounds());

		std::vector<Platform*> collisionPositive;
		auto vec = qtree->retrieve(collisionPositive, (sf::Rect<int>)p1->sprite.getGlobalBounds());
		auto vecptr = &vec;

		//do all window actions(drawing etc)
		window.setView(view);
		window.clear(sf::Color(255,255,255));
		window.draw(bgsprite);
		
		ground->draw(window);
		plat1->draw(window);
		p1->draw(window);
		p1->update(dt, evt, view, vecptr);

		window.display();
}
