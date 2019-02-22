/***
This file defines the Player class


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

#include "player.h"
#include "bullet.h"

#include "SFML/Graphics.hpp"
#include <windows.h>

using namespace sf;

Color colorList[8] = {Color::Yellow, Color::White, Color::Red, Color::Magenta, Color::Green, Color::Cyan, Color::Blue, Color::Black};

Player::Player()
{
    this->healthPoint = 120;
    this->isBlowingUp = 0;
    this->ship = sPlayerShip;
    this->ship.setPosition(int(float(screen.width - spaceShip_width*playerScale)/2), int(float(screen.height)* 4/5));
    this->color = 0;
    this->speed = 1.3;

    auto pos = this->ship.getPosition();
    this->centerPos = {76*playerScale + pos.x, 174*playerScale + pos.y};
    this->centerPoint.setRadius(10*playerScale);
    this->centerPoint.setPosition(centerPos);
    this->centerPoint.setFillColor(Color(Color::Yellow));
}

void Player::modifyColor()
{
    this->color = (this->color + 1) % 8;

    switch (this->color)
    {
    case 0:
        this->centerPoint.setFillColor(colorList[0]);
        break;
    case 1:
        this->centerPoint.setFillColor(colorList[1]);
        break;
    case 2:
        this->centerPoint.setFillColor(colorList[2]);
        break;
    case 3:
        this->centerPoint.setFillColor(colorList[3]);
        break;
    case 4:
        this->centerPoint.setFillColor(colorList[4]);
        break;
    case 5:
        this->centerPoint.setFillColor(colorList[5]);
        break;
    case 6:
        this->centerPoint.setFillColor(colorList[6]);
        break;
    case 7:
        this->centerPoint.setFillColor(colorList[7]);
        break;
    }
}

void Player::move() ///<If player pressed any arrow keys, the spaceship move
{
    bool modified = false;

    int up = Keyboard::isKeyPressed(sf::Keyboard::Up); //GetAsyncKeyState(VK_UP);
    int down = Keyboard::isKeyPressed(sf::Keyboard::Down); //GetAsyncKeyState(VK_DOWN);
    int left = Keyboard::isKeyPressed(sf::Keyboard::Left); //GetAsyncKeyState(VK_LEFT);
    int right = Keyboard::isKeyPressed(sf::Keyboard::Right); //GetAsyncKeyState(VK_RIGHT);

    auto pos = this->ship.getPosition();

    if (up && (pos.y - this->speed) >= 0)
    {
        this->ship.move(0, -this->speed);
        modified = true;
    }
    else if (down && (spaceShip_height*playerScale + this->speed + pos.y) <= screen.height)
    {
        this->ship.move(0, this->speed);
        modified = true;
    }
    else if (left && (pos.x - this->speed) >= 0)
    {
        this->ship.move(-this->speed, 0);
        modified = true;
    }
    else if (right && (spaceShip_width*playerScale + this->speed + pos.x) <= screen.width)
    {
        this->ship.move(this->speed, 0);
        modified = true;
    }

    pos = this->ship.getPosition();

    if (modified)
    {
        this->centerPos = {76*playerScale + pos.x, 174*playerScale + pos.y};
        this->centerPoint.setPosition(centerPos);
    }
}

void Player::shoot()
{
    Bullet b;
    b.shape = sLaser;
    b.velocity = {0.0f, -800.0f};
    b.shape.setPosition(centerPos.x, this->centerPos.y - 60);
    b.damage = 50;

    this->laserGun.push_back(b);
    gunSound.play();
}

void Player::takeDamage(int damage)
{
    healthPoint -= damage;
    isBlowingUp = 300;
    explosionSound.play();
}
