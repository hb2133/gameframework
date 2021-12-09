#ifndef __SDLGAMEOBJECT__
#define __SDLGAMEOBJECT__
#include "SDL.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include <iostream>
#include "InputHandler.h"

class SDLGameObject :public GameObject {
public:
    SDLGameObject() {};
    SDLGameObject(const LoaderParams* pParams);
    virtual void draw();
    virtual void draw_angle();
    virtual void update();
    virtual void clean();
    virtual ~SDLGameObject() {}

    Vector2D getPos() { return m_position; }
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }

protected:
    Vector2D m_acceleration;
    Vector2D m_position;
    Vector2D m_velocity;
    int m_width;
    int m_height;
    int m_currentRow;
    int m_currentFrame;
    int m_angle;
    SDL_RendererFlip m_flip;
    std::string m_textureID;
};


#endif