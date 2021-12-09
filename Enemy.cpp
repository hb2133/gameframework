#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    m_flip = SDL_FLIP_NONE;
    hp = 5;
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	gravity(0.01);

    move();
    checkCollision();
    m_currentFrame = (SDL_GetTicks() / 100) % 6;

    if (hp <= 0)
    {
        this->clean();
    }

	SDLGameObject::update();
}

void Enemy::move()
{
    std::vector<GameObject*> playerPos = TheGame::Instance()->getPlayerObjects();
    for (int i = 0; i < playerPos.size(); i++)
    {
        p_PosX = dynamic_cast<SDLGameObject*>(playerPos[i])->getPos().getX();
    }
    if (m_position.getX() < p_PosX) 
    {
        m_flip = SDL_FLIP_HORIZONTAL;
        //std::cout << "몬스터가 왼쪽에 있음!" << std::endl;
        m_velocity.setX(0.5);

    }
    else if (m_position.getX() > p_PosX)
    {
        m_flip = SDL_FLIP_NONE;
       // std::cout << "몬스터가 오른쪽에 있음!" << std::endl;
        m_velocity.setX(-0.5);
    }
}
 




void Enemy::checkCollision()
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
    std::vector<GameObject*> *Bullet = TheGame::Instance()->getBulletObjects();
    for (int i = 0; i < Bullet->size(); i++)
    {
        int o_L = dynamic_cast<SDLGameObject*>((*Bullet)[i])->getPos().getX();
        int o_R = o_L + dynamic_cast<SDLGameObject*>((*Bullet)[i])->getWidth();
        int o_T = dynamic_cast<SDLGameObject*>((*Bullet)[i])->getPos().getY();
        int o_B = o_T + dynamic_cast<SDLGameObject*>((*Bullet)[i])->getHeight();

        if (p_L <= o_R && p_R >= o_L && p_T <= o_B && p_B >= o_T)
        {
            //아래
            if (m_velocity.getY() > 0 && p_B >= o_T && p_B < o_B && p_L != o_R && p_R != o_L)
            {
               // m_position.setY(o_T - m_height);
                p_T = m_position.getY();
                p_B = p_T + m_height;
                hp -= 1;
                if (hp == 0)
                {
                    this->clean();
                }
            }
            //위쪽
            else if (m_velocity.getY() < 0 && p_T <= o_B && p_T > o_T && p_L != o_R && p_R != o_L)
            {
               // m_position.setY(o_B);
                p_T = m_position.getY();
                p_B = p_T + m_height;
                hp -= 1;
                if (hp == 0)
                {
                    this->clean();
                }

            }
            //왼쪽
            if (m_velocity.getX() < 0 && p_L <= o_R && p_L > o_L && p_T != o_B && p_B != o_T)
            {
                //m_position.setX(o_R);
                hp -= 1;
                if (hp == 0)
                {
                    this->clean();
                }
            }
            //오른쪽
            else if (m_velocity.getX() > 0 && p_R >= o_L && p_R < o_R && p_T != o_B && p_B != o_T)
            {
               // m_position.setX(o_L - m_width);
                hp -= 1;
                if (hp == 0)
                {
                    this->clean();
                }
            }
        }
    }
}

void Enemy::gravity(float g_power)
{
	m_acceleration.setY(g_power);
}



void Enemy::clean() 
{
    std::vector<GameObject*>* enemy = TheGame::Instance()->getEnemyObjects(); //총알

    for (std::vector<GameObject*>::iterator i = enemy->begin(); i != enemy->end(); i++)
    {
        if (this == *i)
        {
            enemy->erase(i);
            break;
        }
    }
}