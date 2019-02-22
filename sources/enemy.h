/***
This file declares the Enemy class


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

#ifndef _enemy_header
#define _enemy_header

#include "bullet.h"
#include "player.h"

enum EnemyType { darkSoldier, boss };

class Enemy
{
protected:
    int healthPoint;
    sf::Vector2f velocity;
public:
    int isBlowingUp;
    sf::Sprite shape;
    Shooter mainGun;
    EnemyType type;
public:
    Enemy() :isBlowingUp(0) {}
    void takeDamage(int damage);
    bool isDeath() { return (healthPoint > 0 ? false : true); }
    virtual void move() = 0;
    virtual void shoot(int shot) = 0;
    virtual void attack(Player target) = 0;
};

class DarkSoldier : public Enemy
{
public:
    void move();
    void shoot(int shot);
    void attack(Player target) {};

	DarkSoldier(sf::Vector2f pos);
};

class Boss : public Enemy
{
public:
    void move();
    void shoot(int shot);
    void attack(Player target);

    Boss(sf::Vector2f pos);
};

typedef std::vector<Enemy*> Enemies;

#endif // _enemy_header
