#include "InputHandler.h"
#include "Game.h"
#include <iostream>


InputHandler* InputHandler::s_pInstance = 0;


void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            TheGame::Instance()->quit();
            break;
        case SDL_KEYDOWN:
            onKeyDown();
            break;
        case SDL_KEYUP:
            onKeyUp();
            break;
        case SDL_MOUSEMOTION:
            onMouseMove(event);
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
        default:
            break;
        }
    }
}

void InputHandler::onKeyDown()
{
    m_keystates = SDL_GetKeyboardState(0);
}
void InputHandler::onKeyUp()
{
    m_keystates = SDL_GetKeyboardState(0);
}
bool InputHandler::getMouseButtonState(int buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition()
{
    return m_mousePosition;
}

void InputHandler::onMouseMove(SDL_Event event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        m_mousePosition->setX(event.motion.x);
        m_mousePosition->setY(event.motion.y);
    }
}
void InputHandler::onMouseButtonDown(SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            m_mouseButtonStates[LEFT] = true;
        }
        if (event.button.button == SDL_BUTTON_MIDDLE) {
            m_mouseButtonStates[MIDDLE] = true;
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            m_mouseButtonStates[RIGHT] = true;
        }
    }
}
void InputHandler::onMouseButtonUp(SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            m_mouseButtonStates[LEFT] = false;
        }
        if (event.button.button == SDL_BUTTON_MIDDLE) {
            m_mouseButtonStates[MIDDLE] = false;
        }
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            m_mouseButtonStates[RIGHT] = false;
        }
    }
}


bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (m_keystates != 0)
    {
        if (m_keystates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}