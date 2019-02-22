#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void loadFromFile(std::string fileName);

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void mouseChoose();

	int GetPressedItem() { return selectedItemIndex; }
	int GetClickedItem();

private:
	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text> menu;
	std::vector<std::string> strs;
};

