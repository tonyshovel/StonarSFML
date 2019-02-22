/***
This file declares the Bullet class


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

#ifndef _bullet_header
#define _bullet_header

#include "stonar.h"

class Bullet
{
public:
    sf::Sprite shape;
    sf::Vector2f velocity;
    int damage;
};

typedef std::vector<Bullet> Shooter;

#endif //_bullet_header
