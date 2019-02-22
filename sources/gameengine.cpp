/***
This file define the createGame() function in "stonar.h"


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

#include "stonar.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"

#include "SFML/Graphics.hpp"

#include <cstdlib>
#include <sstream>
#include <typeinfo>

void modifyScore(sf::Text &txt, int score);
void modifyFPS(sf::Text &fpsCounter, int FPS);
void gameOver(sf::RenderWindow &GameWindow);

void generateEnemies(Enemies &enemies, sf::Clock &gameClock);
int bossCreated = 0;

float FPS = 1;
float TPF = 1;

void createGame()
{
    sf::Clock gameClock;
    //The score parameter
    sf::Text scoreCounter("SCORE: 0", gameFont, 24);
    scoreCounter.setStyle(sf::Text::Bold);
    scoreCounter.setPosition(screen.width*3/4, 0);

    //The FPS parameter
    sf::Text FPScounter("FPS: 0", menuFont, 22);
    FPScounter.setStyle(sf::Text::Bold);
    FPScounter.setPosition(0, 0);

    Player player;
    float score = 0;
    int level = 0;
    bool isLost = false;

    //These variables are created to make sure that we cannot shoot too many bullets consecutively
    bool canShoot = true;
    int shootCount = 0;
    int shootDelay = 35;

    sf::Clock fpsClock;
    float count = 0;

    Enemies enemies;

    sf::RenderWindow GameWindow(screen, "STONAR");
    while (GameWindow.isOpen())
    {
        GameWindow.clear();
        GameWindow.draw(sBackground);

        GameWindow.draw(FPScounter);
        GameWindow.draw(scoreCounter);

        generateEnemies(enemies, gameClock); //Generate enemies

        //Player
        GameWindow.draw(player.ship);
        GameWindow.draw(player.centerPoint);

        if (player.isBlowingUp > 0)
        {
            sExplosion.setPosition(player.ship.getPosition());
            GameWindow.draw(sExplosion);
            player.isBlowingUp--;
        }

        player.modifyColor();
        player.move();

        //Shoot action of player
        if ((shootCount % shootDelay == 0) && !canShoot)
            canShoot = true;
        for (auto it = player.laserGun.begin(); it != player.laserGun.end(); it++)
        {
            GameWindow.draw(it->shape);
            it->shape.move(it->velocity*TPF);

            if (it->shape.getPosition().y <= 0)
            {
                player.laserGun.erase(it--);
                continue;
            }

            for (auto &e : enemies)
                if (it->shape.getGlobalBounds().intersects(e->shape.getGlobalBounds()))
                {
                    e->takeDamage(it->damage);
                    player.laserGun.erase(it--);
                    break;
                }
        }
        if (canShoot && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            player.shoot();
            canShoot = false;
            shootCount = 1;
        }


        for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
        {
            auto e = *enemy;
            if (e->isDeath())
            {
                float s = 0;
                switch (e->type)
                {
                case darkSoldier:
                    s = 50.0f;
                    break;
                case boss:
                    s = 1000.0f;
                    bossCreated--;
                    break;
                }
                score += s;

                delete *enemy;
                enemies.erase(enemy--);
                continue;
            }

            GameWindow.draw(e->shape);
            if (e->isBlowingUp > 0)
            {
                sExplosion.setPosition(e->shape.getPosition());
                GameWindow.draw(sExplosion);
                e->isBlowingUp--;
            }
            e->move();

            if (int(count) % 600 == 0)
                e->shoot(e->type == boss ? 1 : 4);
            if (int(count) % 110 == 0 && e->type == boss)
            {
                e->attack(player);
                if (int(count) % 50 == 0)
                    e->shoot(1);
            }

            for (auto bu = e->mainGun.begin(); bu != e->mainGun.end(); bu++)
            {
                bu->shape.move(bu->velocity*TPF);

                auto pos = bu->shape.getPosition();
                if (pos.x <= 0 || pos.x >= screen.width || pos.y <= 0 || pos.y >= screen.height)
                {
                    e->mainGun.erase(bu--);
                    continue;
                }
                GameWindow.draw(bu->shape);

                if (bu->shape.getGlobalBounds().intersects(player.centerPoint.getGlobalBounds()))
                {
                    player.takeDamage(bu->damage);
                    e->mainGun.erase(bu--);

                    if (player.isDeath())
                        isLost = true;
                }
            }
            *enemy = e;
        }
        GameWindow.display();

        Event event;
        while (GameWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                GameWindow.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    GameWindow.close();
                break;
            case sf::Event::LostFocus:
                while (!GameWindow.pollEvent(event));
                break;
            }
        }

        //The whole game
        if (isLost)
        {
            gameOver(GameWindow);
            bossCreated = 0;
        }
        if (!canShoot)
            shootCount++;
        if (int(count) % 200 == 0)
            modifyFPS(FPScounter, FPS);
        if (count >= 2000000000.0f)
            count = 0.0f;
        modifyScore(scoreCounter, score);

        TPF = fpsClock.getElapsedTime().asSeconds();
        FPS = 1.0 / TPF;
        fpsClock.restart();
        count += 400*TPF;
    }
}







void modifyScore(sf::Text &txt, int score)
{
    char str[20]; sprintf(str, "SCORE: %d", score);
    txt.setString(str);
}

void modifyFPS(sf::Text &fpsCounter, int FPS)
{
    char str[20]; sprintf(str, "FPS: %d", FPS);
    fpsCounter.setString(str);
}

void gameOver(sf::RenderWindow &GameWindow)
{
    sf::Text gameOver("GAME OVER" , gameFont, 50);
    gameOver.setStyle(sf::Text::Bold);
    gameOver.setPosition(screen.width*1/4, screen.height/2);
    gameOver.setColor(sf::Color::Red);

    GameWindow.draw(gameOver);
    gameOverSound.play();
    GameWindow.display();

    while (GameWindow.isOpen())
    {
        sf::Event e;
        while (!(GameWindow.pollEvent(e) && (e.type == sf::Event::KeyReleased && (e.key.code == sf::Keyboard::Enter || e.key.code == sf::Keyboard::Escape))));
        GameWindow.close();
    }
}

void generateEnemies(Enemies &enemies, sf::Clock &gameClock)
{
    if (!enemies.size())
    {
        for (int i(0); i < 4; i++)
        {
            int randNum = rand() % 120;
            if (rand() % 2)
                randNum = -randNum;
            sf::Vector2f pos = { screen.width/2 + randNum, screen.height * 1/6 };
            enemies.push_back(new DarkSoldier(pos));
        }
    }

    int secs = gameClock.getElapsedTime().asSeconds();
    if (secs > 0 && secs % 5 == 0 && !bossCreated)
    {
        sf::Vector2f pos = { rand() % screen.width - 200, 0 };

        enemies.push_back(new Boss(sf::Vector2f(pos)));
        bossCreated++;
    }
}
