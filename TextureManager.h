#ifndef __Texture__
#define __Texture__

#include "SDL.h"
#include <map>
#include "Game.h"

class TextureManager {
public:
    ~TextureManager() {}
    static TextureManager* Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new TextureManager();
        }
        return s_pInstance;
    }
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void draw_angle(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, float angle, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void clean(SDL_Renderer* pRenderer);

    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
private:
    TextureManager() {}
    static TextureManager* s_pInstance;
    std::map<std::string, SDL_Texture*> m_textureMap;

};

typedef TextureManager TheTextureManager;

#endif