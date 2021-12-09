#ifndef __PLAYER__
#define __PLAYER__
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "SDL_rect.h"
#include <vector>
class Player : public SDLGameObject
{
public:
    Player() { shot = false;  };
    Player(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    void handleInput();

    void gravity(float g_power);
    void checkCollision();

    bool getShot() { return shot; } //ÃÑset ÇÔ¼ö


private:
    void Shoot();
    bool isJump;
    bool shot;
    int nextShootDelay = 10;
    int ballShootDelay = 3; //°ø°Ý µô·¹ÀÌ
    int ShootDelay = 0;

};

#endif