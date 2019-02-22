/***
This file defines the Enemy class and its subclass


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

#include "enemy.h"
#include "stonar.h"

void Enemy::takeDamage(int damage)
{
	healthPoint -= damage;
	isBlowingUp = 300;
    explosionSound.play();
}

DarkSoldier::DarkSoldier(sf::Vector2f pos = {0.0f, 0.0f})
{
    type = darkSoldier;
    healthPoint = 500;
    velocity = sf::Vector2f(200.0f, 0.0f);
    shape = sSoldierShape;

	int lucky = rand() % 2;

	if (!lucky)
		velocity = -velocity; //move from right to left
    shape.setPosition(pos);
}

void DarkSoldier::move()
{
    this->shape.move(this->velocity*TPF);

    if (this->shape.getPosition().x <= 0 || this->shape.getPosition().x + 68.6 >= screen.width + 10)
        this->velocity = -this->velocity;
}

void DarkSoldier::shoot(int shot = 1)
{
    for (int i(shot); i > 0; i--)
    {
        Bullet bullet;
        bullet.damage = 20;
        bullet.velocity = { 0.0f, 200.0f };
        bullet.shape = sSoldierBullet;

        auto pos = this->shape.getPosition();
        pos.y = pos.y + i*30.0f;

        bullet.shape.setPosition(pos);
        this->mainGun.push_back(bullet);
    }
    //Gun Sound play
}



Boss::Boss(sf::Vector2f pos = { 0.0f, 0.0f })
{
    type = boss;
    healthPoint = 20000;
    velocity = { 150.0f, 0.0f };

    if (!(rand() % 2))
        velocity = -velocity;

    shape = sBossShape;
    shape.setPosition(pos);
}

void Boss::move()
{
    this->shape.move(this->velocity*TPF);

    if (this->shape.getPosition().x + 61.5 <= 0 || this->shape.getPosition().x + 61.5 >= screen.width)
        this->velocity = -this->velocity;
}

void Boss::shoot(int shot = 1)
{
    for (int i(shot); i > 0; i--)
    {
        Bullet bullet;
        bullet.damage = 60;
        bullet.velocity = { 0.0f, 160.0f };
        bullet.shape = sSoldierBullet;

        auto pos = this->shape.getPosition();
        pos.x = pos.x + 820*0.15 / 2;
        pos.y = pos.y + 969*0.15 + i*100.0f;

        bullet.shape.setPosition(pos);
        bullet.shape.setColor(sf::Color::Blue);

        this->mainGun.push_back(bullet);
    }
}

void Boss::attack(Player target)
{
    Bullet bullet;
    bullet.damage = 40;
    bullet.shape = sSoldierBullet;
    bullet.shape.setColor(sf::Color::Cyan);

    auto pos = this->shape.getPosition();
    bullet.shape.setPosition(pos.x + 820*0.15 / 2, pos.y + 969*0.15);

    //Flying direction of bullet
    sf::Vector2f aimDir = target.centerPoint.getPosition() - bullet.shape.getPosition();
    sf::Vector2f aimDirNorm = aimDir / float(sqrt((aimDir.x * aimDir.x, aimDir.y * aimDir.y)));
    bullet.velocity = aimDirNorm * 200.0f;

//  Change the bullet flying direction a bit
    float x = float(rand() % 11) / 100;
    float y = float(rand() % 11) / 100;

    int lucky = rand() % 2;

    auto vec = sf::Vector2f(x, y);
    if (lucky % 2)
        vec = -vec;
    bullet.velocity += vec;

    this->mainGun.push_back(bullet);
}
