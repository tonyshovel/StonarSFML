/***
This file defines global variables such as screen's size or Textures,
which are declared in "stonar.h" and other files.



--------Author--------
Made by: Tony Shovel (Birth year: 2004), Huynh Cong Toai, Vietnamese.

If you can see these comments, that means you have the source code,
My level is just beginner, This game is not designed really well, I hope you guys
can help me to redesign the code to make it cleaner or help me to figure out bugs.


Tony Shovel (Huynh Cong Toai), 13:55 Third of February, 2019
***/


#include "stonar.h"
#include <string>
#include "SFML/Graphics.hpp"

sf::VideoMode screen(800, 600);
sf::Texture background, playerShip, laser, soldierBullet, mouseTexture, bossShape, explosion, soldierShape;
sf::Sprite sBackground, sPlayerShip, sLaser, sSoldierBullet, mouseSprite, sBossShape, sExplosion, sSoldierShape;

void initSpritesAndTextures()
{
    background.loadFromFile("img/background.jpg"); ///800x600
    sBackground.setTexture(background); sBackground.setColor(Color(Color::Cyan));

	explosion.loadFromFile("img/explosion.png"); ///79x73
	sExplosion.setTexture(explosion);

	soldierShape.loadFromFile("img/darkSoldier.png"); ///343x383
	sSoldierShape.setTexture(soldierShape);
	sSoldierShape.scale(0.2, 0.2);///68.6x76.6

	soldierBullet.loadFromFile("img/fireball.png");///184x182
	sSoldierBullet.setTexture(soldierBullet);
	sSoldierBullet.scale(0.1, 0.1);///18.4x18.2

	bossShape.loadFromFile("img/boss.png"); ///820x969
	sBossShape.setTexture(bossShape);
	sBossShape.scale(0.15, 0.15);///123x145.35

    playerShip.loadFromFile("img/player.png");///173x291
    sPlayerShip.setTexture(playerShip);
    sPlayerShip.scale(playerScale, playerScale);///51.9x87.3

    laser.loadFromFile("img/laser.png");///90x512
    sLaser.setTexture(laser);
    sLaser.scale(0.1, 0.07);///9x35x84

    mouseTexture.loadFromFile("img/mouse.png"); ///874x886
    mouseSprite.setTexture(mouseTexture);
    mouseSprite.scale(0.05, 0.05);
}

int spaceShip_width = 173;
int spaceShip_height = 291;
float playerScale = 0.3;


sf::Font gameFont;
sf::Font menuFont;

void initFonts()
{
    if (!gameFont.loadFromFile("font/MATURASC.ttf"))
    {
        std::cout << "Cannot read MATURASC font!" << std::endl;
        system("pause");
    }
    if (!menuFont.loadFromFile("font/consola.ttf"))
    {
        std::cout << "Cannot read Consolas font!" << std::endl;
        system("pause");
    }
}

sf::SoundBuffer gunBuffer, gameOverBuffer, explosionBuffer, selectBuffer;
sf::Sound gunSound, gameOverSound, explosionSound, selectSound;

void initSounds()
{
    gunBuffer.loadFromFile("sounds/laser.wav");
    gunSound.setBuffer(gunBuffer);

    gameOverBuffer.loadFromFile("sounds/lost.wav");
    gameOverSound.setBuffer(gameOverBuffer);

    explosionBuffer.loadFromFile("sounds/explosion.wav");
    explosionSound.setBuffer(explosionBuffer);

    selectBuffer.loadFromFile("sounds/select.wav");
    selectSound.setBuffer(selectBuffer);
}

void delay(float secs)
{
    sf::Clock delayClock;
    while (delayClock.getElapsedTime().asSeconds() <= secs);
}
