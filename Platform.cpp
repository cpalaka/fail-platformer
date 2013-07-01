#include "Platform.h"

Platform::Platform(std::string str, int x, int y)
{
	image.loadFromFile(str);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Platform::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Platform::colCheck(int x, int y)
{
	sf::Vector2f pos = sprite.getPosition();
	sf::FloatRect bounds = sprite.getGlobalBounds();
	if(x > pos.x && x < pos.x + bounds.width && y > pos.y && y < pos.y + bounds.height)
	{
		sf::Color col = image.getPixel(x - pos.x, y - pos.y);
		if(col.a == 255)
			return true;
		else
			return false;
	} else {
		return false;
	}
}