/***
This file contain the main function


--------Author--------
Made by: Tony Shovel (Birth year: 2004), Huynh Cong Toai, Vietnamese.

If you can see these comments, that means you have the source code,
My level is just beginner, This game is not designed really well, I hope you guys
can help me to redesign the code to make it cleaner or help me to figure out bugs
or you can make somethings base on these codes.


Tony Shovel (Huynh Cong Toai), 13:55 Third of February, 2019

Contact:
    Facebook: https://facebook.com/tony.shovel.90
    Email: hcthuyhcongtoai@gmail.com
           tonyshovel2004@gmail.com
    Phone number: 0918894508
***/


#include "sources/stonar.h"
#include "sources/menu.h"
#include "SFML/Graphics.hpp"

int main()
{
    srand(time(0));

    initSpritesAndTextures();
    initFonts();
    initSounds();

    sf::Texture menuBK; menuBK.loadFromFile("img/menu.jpg");
    sf::Sprite sMenuBK(menuBK); sMenuBK.setColor(sf::Color::Cyan);

    sf::RenderWindow menuWindow(sf::VideoMode(500, 600), "Stonar by TonyShovel");
    menuWindow.setMouseCursorVisible(false);
    Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);

    sf::Font font; font.loadFromFile("font/BPPU.TTF");

    sf::Text STONAR("STONAR", font, 70);
    STONAR.setColor(sf::Color::Magenta);
    STONAR.setPosition((menuWindow.getSize().x - STONAR.getGlobalBounds().width)/2 , menuWindow.getSize().y * 1/5);

    sf::Vector2f mousePos;
    int option = -1;

    while (menuWindow.isOpen())
    {
        mousePos = sf::Vector2f(sf::Mouse::getPosition(menuWindow));
        mouseSprite.setPosition(mousePos);

        menuWindow.clear();
        menuWindow.draw(sMenuBK);
        menuWindow.draw(STONAR);
        menu.draw(menuWindow);
        menuWindow.draw(mouseSprite);

        sf::Event event;
        while (menuWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                menuWindow.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    menuWindow.close();
                    break;
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;
                case sf::Keyboard::Return:
                    option = menu.GetPressedItem();
                    break;
                }
                delay(0.02);
                break;
            case sf::Event::MouseMoved:
                menu.mouseChoose();
                break;
            case sf::Event::MouseButtonPressed:
                switch (event.key.code)
                {
                case sf::Mouse::Left:
                    option = menu.GetClickedItem();
                    break;
                }
                break;
            }
        }

        //Menu
        switch (option)
        {
        case 0:
            createGame();
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            menuWindow.close();
            break;
        }
        option = -1;
        menuWindow.display();
    }
    return 0;
}
