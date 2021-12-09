#include "Player.h"
#include "SDL.h"
#include <iostream>
#include "Game.h"
#include "Bullet.h"


Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    shot = false;
    isJump = true; // chpark
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_acceleration.setY(0.5);//가속도
    checkCollision(); //충돌체크
    handleInput(); //키입력

    m_currentFrame = ((SDL_GetTicks() / 100) % 6);
    SDLGameObject::update();
}
void Player::handleInput()
{

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
        SDLGameObject::m_textureID = "Player_Run";
        SDLGameObject::m_flip = SDL_FLIP_NONE;
        m_velocity.setX(2);
    }
    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false)
    {
        SDLGameObject::m_textureID = "Player_Idle";
        m_velocity.setX(0);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
        SDLGameObject::m_textureID = "Player_Run";
        SDLGameObject::m_flip = SDL_FLIP_HORIZONTAL;
        m_velocity.setX(-2);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) //스페이스바
    {
        if (isJump) { //땅에 있을 시 점프
            m_velocity.setY(-10);
            gravity(0.1);
            isJump = false;
        }
    }


    Shoot();

}

void Player::Shoot()
{
    ShootDelay = ((SDL_GetTicks() / 100));
    if (TheInputHandler::Instance()->getMouseButtonState(0))
    {
        if (ShootDelay >= nextShootDelay)
        {
            TheGame::Instance()->m_bulletObjects.push_back(new Bullet(new LoaderParams(m_position.getX()+10, m_position.getY()+10, 12, 12, "Bullet")));
            

            nextShootDelay = ShootDelay + ballShootDelay;
        }
    }
}

void Player::checkCollision()
{
    std::vector<GameObject*> collBox = TheGame::Instance()->getBoxObjects();
    int p_L = m_position.getX();
    int p_R = p_L + m_width;
    int p_T = m_position.getY();
    int p_B = p_T + m_height;

    for (int i = 0; i < collBox.size(); i++)
    {
        int o_L = dynamic_cast<SDLGameObject*>(collBox[i])->getPos().getX();
        int o_R = o_L + dynamic_cast<SDLGameObject*>(collBox[i])->getWidth();
        int o_T = dynamic_cast<SDLGameObject*>(collBox[i])->getPos().getY();
        int o_B = o_T + dynamic_cast<SDLGameObject*>(collBox[i])->getHeight();

        if (p_L <= o_R && p_R >= o_L && p_T <= o_B && p_B >= o_T)
        {
            //아래
            if (m_velocity.getY() > 0 && p_B >= o_T && p_B < o_B && p_L != o_R && p_R != o_L)
            {
                m_position.setY(o_T - m_height);
                p_T = m_position.getY();
                p_B = p_T + m_height;

                m_velocity.setY(0);
                gravity(0.0);
                isJump = true;
            }
            //위쪽
            else if (m_velocity.getY() < 0 && p_T <= o_B && p_T > o_T && p_L != o_R && p_R != o_L)
            {
                m_position.setY(o_B);
                p_T = m_position.getY();
                p_B = p_T + m_height;

                m_velocity.setY(0);
            }
            //왼쪽
            if (m_velocity.getX() < 0 && p_L <= o_R && p_L > o_L && p_T != o_B && p_B != o_T)
            {
                m_position.setX(o_R);
                m_velocity.setX(0);
            }
            //오른쪽
            else if (m_velocity.getX() > 0 && p_R >= o_L && p_R < o_R && p_T != o_B && p_B != o_T)
            {
                m_position.setX(o_L - m_width);
                m_velocity.setX(0);
            }
        }
    }
    std::vector<GameObject*>* Enemy = TheGame::Instance()->getEnemyObjects();
    for (int i = 0; i < Enemy->size(); i++)
    {
        int o_L = dynamic_cast<SDLGameObject*>((*Enemy)[i])->getPos().getX();
        int o_R = o_L + dynamic_cast<SDLGameObject*>((*Enemy)[i])->getWidth();
        int o_T = dynamic_cast<SDLGameObject*>((*Enemy)[i])->getPos().getY();
        int o_B = o_T + dynamic_cast<SDLGameObject*>((*Enemy)[i])->getHeight();

        if (p_L <= o_R && p_R >= o_L && p_T <= o_B && p_B >= o_T)
        {
            //아래
            if (m_velocity.getY() > 0 && p_B >= o_T && p_B < o_B && p_L != o_R && p_R != o_L)
            {
                m_position.setY(o_T - m_height);
                p_T = m_position.getY();
                p_B = p_T + m_height;
                m_velocity.setY(0);
            }
            //위쪽
            else if (m_velocity.getY() < 0 && p_T <= o_B && p_T > o_T && p_L != o_R && p_R != o_L)
            {
                m_position.setY(o_B);
                p_T = m_position.getY();
                p_B = p_T + m_height;
                m_velocity.setY(0);
            }
            //왼쪽
            if (m_velocity.getX() < 0 && p_L <= o_R && p_L > o_L && p_T != o_B && p_B != o_T)
            {
                m_position.setX(o_R);
                m_velocity.setX(0);
            }
            //오른쪽
            else if (m_velocity.getX() > 0 && p_R >= o_L && p_R < o_R && p_T != o_B && p_B != o_T)
            {
                m_position.setX(o_L - m_width);
                m_velocity.setX(0);

            }
        }
    };
}

void Player::gravity(float g_power)
{
    m_acceleration.setY(g_power);
}


void Player::clean() {}