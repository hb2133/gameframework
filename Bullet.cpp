#include "Bullet.h"
#include "Game.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIHGT 480

Bullet::Bullet(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    Vector2D center(m_position.getX() + m_width / 2, m_position.getY() + m_height / 2);

    Vector2D* direction = TheInputHandler::Instance()->getMousePosition();
    m_velocity = (*direction - center);
    m_velocity.normalize();
    m_velocity *= moveSpeed;
}

void Bullet::draw()
{
    SDLGameObject::draw();
}

void Bullet::update()
{
    look();

    m_currentFrame = 0;
    DeleteBullet();
    checkCollision();
    SDLGameObject::update();
}

void Bullet::look() //마우스 위치
{
    mouseX = 0;
    mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
}

void Bullet::DeleteBullet() //화면 밖에 나가는 총알 제거
{
    if (m_position.getX() + m_width <= 0 || m_position.getX() >= SCREEN_WIDTH)
    {
        this->clean();
    }
    if (m_position.getY() + m_height <= 0 || m_position.getY() >= SCREEN_HEIHGT)
    {
        this->clean();
    }
}

void Bullet::checkCollision()//몬스터 체크
{
    std::vector<GameObject*> *collBox = TheGame::Instance()->getEnemyObjects();
    int p_L = m_position.getX();
    int p_R = p_L + m_width;
    int p_T = m_position.getY();
    int p_B = p_T + m_height;

    for (int i = 0; i < collBox->size(); i++)
    {
        int o_L = dynamic_cast<SDLGameObject*>((*collBox)[i])->getPos().getX();
        int o_R = o_L + dynamic_cast<SDLGameObject*>((*collBox)[i])->getWidth();
        int o_T = dynamic_cast<SDLGameObject*>((*collBox)[i])->getPos().getY();
        int o_B = o_T + dynamic_cast<SDLGameObject*>((*collBox)[i])->getHeight();

        if (p_L <= o_R && p_R >= o_L && p_T <= o_B && p_B >= o_T)
        {
            //아래
            if (m_velocity.getY() > 0 && p_B >= o_T && p_B < o_B && p_L != o_R && p_R != o_L)
            {
                m_position.setY(o_T - m_height);
                p_T = m_position.getY();
                p_B = p_T + m_height;
                this->clean();
            }
            //위쪽
            else if (m_velocity.getY() < 0 && p_T <= o_B && p_T > o_T && p_L != o_R && p_R != o_L)
            {
                m_position.setY(o_B);
                p_T = m_position.getY();
                p_B = p_T + m_height;
                this->clean();
            }
            //왼쪽
            if (m_velocity.getX() < 0 && p_L <= o_R && p_L > o_L && p_T != o_B && p_B != o_T)
            {
                m_position.setX(o_R);
                this->clean();
            }
            //오른쪽
            else if (m_velocity.getX() > 0 && p_R >= o_L && p_R < o_R && p_T != o_B && p_B != o_T)
            {
                m_position.setX(o_L - m_width);
                this->clean();
            }
        }
    }
}

void Bullet::clean() //제거
{    
    std::vector<GameObject*> *bullet = TheGame::Instance()->getBulletObjects();

    for (std::vector<GameObject*>::iterator i = bullet->begin(); i != bullet->end(); i++)
    {
        if(this == *i)
        {
            bullet->erase(i);
            break;
        }
    }
}

//
//디자인패턴
//DX, OpenGL 