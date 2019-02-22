#include "Menu.h"
#include "stonar.h"

#include <fstream>
Menu::Menu(float width, float height)
{
    selectedItemIndex = 0;
    font = menuFont;

    loadFromFile("items.txt");
    for (int i(0); i < strs.size(); i++)
    {
        sf::Text txt(strs.at(i), font, 24);
        txt.setColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
        txt.setStyle(i == selectedItemIndex ? sf::Text::Bold : sf::Text::Regular);
        txt.setPosition(sf::Vector2f(width/5, i*txt.getCharacterSize() + (2*height)/3));

        menu.push_back(txt);
    }
}

Menu::~Menu()
{
}

void Menu::loadFromFile(std::string fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Cannot open " << fileName << std::endl;
        exit(1);
    }

    std::string str;
    while (std::getline(file, str).good())
        strs.push_back(str);
    file.close();
}

void Menu::draw(sf::RenderWindow &window)
{
	for (auto m : menu)
	{
		window.draw(m);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
        menu.at(selectedItemIndex).setColor(sf::Color::White);
        menu.at(selectedItemIndex).setStyle(sf::Text::Regular);

		selectedItemIndex--;
        selectSound.play();

        menu.at(selectedItemIndex).setColor(sf::Color::Red);
        menu.at(selectedItemIndex).setStyle(sf::Text::Bold);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < menu.size())
	{
        menu.at(selectedItemIndex).setColor(sf::Color::White);
        menu.at(selectedItemIndex).setStyle(sf::Text::Regular);

		selectedItemIndex++;
        selectSound.play();

        menu.at(selectedItemIndex).setColor(sf::Color::Red);
        menu.at(selectedItemIndex).setStyle(sf::Text::Bold);
	}
}

void Menu::mouseChoose()
{
    for (int i = 0; i < menu.size(); i++)
    {
        if (menu.at(i).getGlobalBounds().intersects(mouseSprite.getGlobalBounds()))
        {
            menu.at(selectedItemIndex).setColor(sf::Color::White);
            menu.at(selectedItemIndex).setStyle(sf::Text::Regular);

            if (i != selectedItemIndex)
                selectSound.play();
            selectedItemIndex = i;

            menu.at(selectedItemIndex).setColor(sf::Color::Red);
            menu.at(selectedItemIndex).setStyle(sf::Text::Bold);
            return;
        }
    }
}

int Menu::GetClickedItem()
{
    if (menu.at(selectedItemIndex).getGlobalBounds().intersects(mouseSprite.getGlobalBounds()))
    {
        return selectedItemIndex;
    }
    return -1;
}

