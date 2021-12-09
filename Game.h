#pragma once
#ifndef __Game__
#define __Game__

#include "SDL.h"
#include "GameObject.h"
#include <vector>
#include "InputHandler.h"
#include "SDL_ttf.h"
#include <random>

class Game
{
public:
    static Game* Instance()
    {
        if (s_pInstance == 0) {
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }
    ~Game() {}

    bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
    void render();
    void update();
    bool running();
    void handleEvents();
    void clean();
    void quit() { m_bRunning = false; }
    static SDL_Renderer* getRenderer() { return m_pRenderer; }
    static SDL_Renderer* m_pRenderer;


    std::vector<GameObject*> getBoxObjects() const { return m_boxObjects; } //�ڽ�
    std::vector<GameObject*> getPlayerObjects() const { return m_player; } //�÷��̾�
    std::vector<GameObject*>* getEnemyObjects() { return &m_enemy; } //����
    std::vector<GameObject*> getObjects() const { return m_gameObjects; } //������Ʈ
    std::vector<GameObject*>* getBulletObjects() { return &m_bulletObjects; }
    std::vector<GameObject*> m_bulletObjects; //�Ѿ�
    void Cooltime();
    void createBullet();
    bool cool = true;
    unsigned int lastTime = 0, currentTime;
    bool bullet_cool = true;
    unsigned int bullet_currentTime;
    const char* text;

private:
    Game() {}
    static Game* s_pInstance;
    SDL_Window* m_pWindow;
    bool m_bRunning;
    int E_posX;
    std::vector<GameObject*> m_boxObjects; //�ڽ�
    std::vector<GameObject*> m_player; //�÷��̾�
    std::vector<GameObject*> m_enemy; //����
    std::vector<GameObject*> m_gameObjects; //������Ʈ
    // ���� �簢��
    SDL_Rect m_sourceRectangle;
    // ��� �簢��
    SDL_Rect m_destinationRectangle;

    SDL_Texture* m_pTexture;

    bool shoot; //�Ѿ� �߻� bool��

    SDL_Rect r;
    SDL_Texture* texture;
};
typedef Game TheGame;

#endif