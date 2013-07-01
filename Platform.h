#include <SFML/Graphics.hpp>
#include <iostream>

class Platform {
public:
	Platform(std::string, int, int);
	void draw(sf::RenderWindow& window);
	bool colCheck(int, int); //checks if given x,y coords are inside platform
	sf::Sprite sprite;
private:
	sf::Texture texture;
	sf::Image image;
};