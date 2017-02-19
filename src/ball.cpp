#include "ball.h"
#include "game.h"

Ball::Ball(const char* name, Game* g, int speed)
{
    m_name = name;
    m_speed = speed;
    m_game = g;

    std::random_device rd;
    std::mt19937 temp(rd());
    mt = temp;
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    dir = dist;

    RandomDir();

    renderRect ball;
    ball.rect.w = 10;
    ball.rect.h = 10;
    ball.x = ball.rect.x = m_game->GetW()/2 - (ball.rect.w/2);
    ball.y = ball.rect.y = m_game->GetH()/2 - (ball.rect.h/2);
    ball.r = 255;
    ball.g = 255;
    ball.b = 255;
    m_rects[name] = ball;
    m_game->Getrenderer()->AddRectangle(&m_rects);
}

void Ball::RandomDir(){
    m_dir.x = dir(mt);
    m_dir.y = dir(mt);
}

Ball::~Ball()
{
    //dtor
}

void Ball::Update(){
    Move(m_dir * m_speed);
    if(!collision()){
        lastCollision = "";
        WallCollsion();
    }
}

void Ball::collisionCB(GameObject * obj){
    if(lastCollision != obj->getName()){
        SDL_Rect * player = &m_game->GetGameObject(obj->getName())->getRect(obj->getName())->rect;
        int ballHeight = (m_rects[m_name].rect.y+(m_rects[m_name].rect.h/2))-player->y;
        if(ballHeight > player->h+3){
            std::cout<<"Above: "<<ballHeight<<std::endl;
            m_rects[m_name].rect.y = m_rects[m_name].y = player->y+player->h;
            if(m_dir.y > 0){
                m_dir.y *=1.5;
            } else if(m_dir.y < 0){
                m_dir.y *=-1;
            }
        } else if(ballHeight+3 < 0){
            std::cout<<"Below: "<<ballHeight<<std::endl;
            m_rects[m_name].rect.y = m_rects[m_name].y = player->y-m_rects[m_name].rect.h;
            if(m_dir.y < 0){
                m_dir.y *=1.5;
            } else if(m_dir.y > 0){
                m_dir.y *=-1;
            }
        } else{
            std::cout<<"Middle: "<<ballHeight<<std::endl;
            int distToMiddle =abs(ballHeight-(player->h/2))*2;
            std::cout<<"Dist: "<<distToMiddle<<std::endl;
            m_dir.x *=-1;
            m_dir.y *= 0.5 + distToMiddle/100.f;
        }
    }
    lastCollision = obj->getName();
}

void Ball::WallCollsion(){
    if(m_rects[m_name].y > (m_game->GetH()-(m_rects[m_name].rect.h))){
        m_rects[m_name].y = m_rects[m_name].rect.y = m_game->GetH()-(m_rects[m_name].rect.h);
        m_dir.y *=-1;
    } else if(m_rects[m_name].y < 0){
        m_rects[m_name].y = m_rects[m_name].rect.y = 0;
        m_dir.y *=-1;
    } else if(m_rects[m_name].x > (m_game->GetW()-(m_rects[m_name].rect.w))){
        m_rects[m_name].x = m_rects[m_name].rect.x = m_game->GetW()-(m_rects[m_name].rect.w);
        m_dir.x *=-1;
    } else if(m_rects[m_name].x < 0){
        m_rects[m_name].x = m_rects[m_name].rect.x = 0;
        m_dir.x *=-1;
    }
}

