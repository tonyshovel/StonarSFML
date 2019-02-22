/***
This file declares global variables and functions which help the program implement better (or maybe worst)


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


#ifndef _stonar_header
#define _stonar_header

/**----Library----**/
#include <iostream>
#include <functional>
#include <vector>
#include <time.h>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace sf;

extern sf::VideoMode screen; ///<The game window size

extern float playerScale; ///<The picture in "img" folder is really big, so we use scale to make it smaller
extern int spaceShip_width; ///<The spaceship's picture width
extern int spaceShip_height; ///<The spaceship's picture height

extern sf::Font gameFont;
extern sf::Font menuFont;

extern sf::Texture background, playerShip, laser, soldierBullet, mouseTexture, explosion, /*Enemy*/ bossShape, soldierShape;
extern sf::Sprite sBackground, sPlayerShip, sLaser, sSoldierBullet, mouseSprite, sExplosion, /*Enemy*/ sBossShape, sSoldierShape;
extern sf::SoundBuffer gunBuffer, gameOverBuffer, explosionBuffer, selectBuffer;
extern sf::Sound gunSound, gameOverSound, explosionSound, selectSound;

extern float FPS;
extern float TPF;
/*Global functions*/

void initSpritesAndTextures();
void initFonts();
void initSounds();

void createGame();
void delay(float secs);

#endif // _stonar_header
