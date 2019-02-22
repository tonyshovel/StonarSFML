/***
This file declares the Player class


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

#ifndef _player_header
#define _player_header

#include "bullet.h"

class Player
{
private:
    int color; //centerPoint's color
    sf::Vector2f centerPos; //centerPoint position
    float speed;
    int healthPoint;
public:
    int isBlowingUp;
    sf::Sprite ship;
    sf::CircleShape centerPoint; //The colorful place we need to protect
    Shooter laserGun;

public:
    Player();
    void modifyColor(); //Make the center pointer becomes colorful by changing its color
    void move();
    void shoot();
    bool isDeath() { return (healthPoint > 0 ? false : true); }

    void takeDamage(int damage);
};

#endif // _player_header
