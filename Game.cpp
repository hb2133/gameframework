#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Box.h"
#include "Bullet.h"
#include "SDL_image.h"
#include <string>

Game* Game::s_pInstance = 0;
Map* map;
SDL_Renderer* Game::m_pRenderer = 0;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution <int> dis(30, 600);

SDL_Cursor* cursor = NULL;
SDL_Surface* surface = NULL;
Player player;

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

        if (m_pWindow != 0)
        {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0)
            {
                SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, 255);
            }
            else return false;
        }
        else return false;
    }
    else
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("Assets/background_0.png", "BG0", m_pRenderer))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("Assets/background_1.png", "BG1", m_pRenderer))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("Assets/background_2.png", "BG2", m_pRenderer))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("Assets/Idle.png", "Player_Idle", m_pRenderer))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("Assets/Run.png", "Player_Run", m_pRenderer))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("Assets/Block.png", "Box", m_pRenderer))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("Assets/Hyena_walk.png", "Enemy", m_pRenderer))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("Assets/Bullet.png", "Bullet", m_pRenderer))
    {
        return false;
    }
    for (int i = 0; i < 50; i++) {
        m_boxObjects.push_back(new Box(new LoaderParams(i * 16, 400, 22, 22, "Box")));
    }
    m_gameObjects.push_back(new Box(new LoaderParams(0, 0, 640, 480, "BG0")));
    m_gameObjects.push_back(new Box(new LoaderParams(0, 0, 640, 480, "BG1")));
    m_gameObjects.push_back(new Box(new LoaderParams(0, 0, 640, 480, "BG2")));
    m_player.push_back(new Player(new LoaderParams(50, 300, 32, 32, "Player_Idle")));

    map = new Map();

    surface = IMG_Load("Assets/cursor.png");
    cursor = SDL_CreateColorCursor(surface, 0, 0); //마우스 커서 변경
    SDL_SetCursor(cursor);

    //텍스트
    if (TTF_Init() < 0) { printf("오류: 폰트를 초기화할 수 없습니다. (%s)\n", TTF_GetError()); return false; }
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 16);
    if (font == NULL) 
    {
        printf("Could not open font! (%s)\n", TTF_GetError()); 
        return -1;
    }


    SDL_Color color = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    SDL_Surface* surface = TTF_RenderText_Blended(font, "1 Stage", color); //Text출력
    texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);

    r = { 0, 0, surface->w, surface->h };
    SDL_FreeSurface(surface);

    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);


    m_bRunning = true;
    return true;
}


void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    //map->DrawMap();
    for (int i = 0; i < m_gameObjects.size(); i++) //오브젝트 render
    {
        m_gameObjects[i]->draw();
    }
    for (int i = 0; i != m_boxObjects.size(); i++) //박스 render
    {
        m_boxObjects[i]->draw();
    }
    for (int i = 0; i < m_bulletObjects.size(); i++) //총알 render
    {
        m_bulletObjects[i]->draw();
    }
    for (int i = 0; i < m_enemy.size(); i++) //몬스터 render
    {
        m_enemy[i]->draw();
    }
    for (int i = 0; i < m_player.size(); i++) //플레이어 render
    {
        m_player[i]->draw();
    }
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderCopy(m_pRenderer, texture, NULL, &r);

    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    Cooltime();
    //createBullet();
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
    for (int i = 0; i < m_boxObjects.size(); i++)
    {
        m_boxObjects[i]->update();
    }
    for (int i = 0; i < m_bulletObjects.size(); i++)
    {
        m_bulletObjects[i]->update();
    }
    for (int i = 0; i < m_enemy.size(); i++)
    {
        m_enemy[i]->update();
    }
    for (int i = 0; i < m_player.size(); i++)
    {
        m_player[i]->update();
    }
}

void Game::Cooltime()
{
    currentTime = ((SDL_GetTicks() / 100 % 35));
    if (cool == true) {
        if (currentTime == 34)
        {
            m_enemy.push_back(new Enemy(new LoaderParams(dis(gen), 365, 48, 27, "Enemy"))); //몬스터 생성 x좌표 랜덤값, 쿨타임 생성
            cool = false;
        }
    }
    if (10 > currentTime && currentTime > 5)
    {
        cool = true;
    }
}

void Game::createBullet()
{

}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LCTRL))
    {
        shoot = true;
    }
    else
        shoot = false;
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}