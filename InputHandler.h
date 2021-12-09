#ifndef __INPUT__
#define __INPUT__
#include "SDL.h"
#include "Vector2D.h"
#include <vector>

enum mouse_buttons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler {
public:
    ~InputHandler() {}
    static InputHandler* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }
    InputHandler() {
        m_mousePosition = new Vector2D(0, 0);
        for (int i = 0; i < 3; i++)
        {
            m_mouseButtonStates.push_back(false);
        }
    };
    bool isKeyDown(SDL_Scancode key);
    void update();
    void clean() {}

    //std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
    std::vector<bool> m_mouseButtonStates;
    bool getMouseButtonState(int buttonNumber);
    Vector2D* getMousePosition();

private:
    static InputHandler* s_pInstance;
    const Uint8* m_keystates;
    void onKeyDown();
    void onKeyUp();
    void onMouseMove(SDL_Event event);
    void onMouseButtonDown(SDL_Event event);
    void onMouseButtonUp(SDL_Event event);

};

typedef InputHandler TheInputHandler;

#endif