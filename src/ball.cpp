#include "ball.h"
#include "game.h"

Ball::Ball(Game* g, int speed)
{
    name = "Ball";
    m_speed = speed;
    m_game = g;
    m_dir.x = -1;
    m_dir.y = -0.5;

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
    std::cout<<std::endl<<obj->getName()<<std::endl;
    if(lastCollision != obj->getName()){
        SDL_Rect * player = &m_game->GetGameObject(obj->getName())->getRect(obj->getName())->rect;
        int ballHeight = (m_rects[name].rect.y+(m_rects[name].rect.h/2))-player->y;
        if(ballHeight > player->h+3){
            std::cout<<"Above: "<<ballHeight<<std::endl;
            m_rects[name].rect.y = m_rects[name].y = player->y+player->h;
            if(m_dir.y > 0){
                m_dir.y *=1.5;
            } else if(m_dir.y < 0){
                m_dir.y *=-1;
            }
        } else if(ballHeight+3 < 0){
            std::cout<<"Below: "<<ballHeight<<std::endl;
            m_rects[name].rect.y = m_rects[name].y = player->y-m_rects[name].rect.h;
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
    if(m_rects[name].y > (m_game->GetH()-(m_rects[name].rect.h))){
        m_rects[name].y = m_rects[name].rect.y = m_game->GetH()-(m_rects[name].rect.h);
        m_dir.y *=-1;
    } else if(m_rects[name].y < 0){
        m_rects[name].y = m_rects[name].rect.y = 0;
        m_dir.y *=-1;
    } else if(m_rects[name].x > (m_game->GetW()-(m_rects[name].rect.w))){
        m_rects[name].x = m_rects[name].rect.x = m_game->GetW()-(m_rects[name].rect.w);
        m_dir.x *=-1;
    } else if(m_rects[name].x < 0){
        m_rects[name].x = m_rects[name].rect.x = 0;
        m_dir.x *=-1;
    }
}

