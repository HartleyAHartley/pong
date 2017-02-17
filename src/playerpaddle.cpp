#include "playerpaddle.h"
#include "game.h"
#include "ball.h"

PlayerPaddle::PlayerPaddle(Game* g, float yPos, int speed, SDL_Scancode up, SDL_Scancode down)
{

    m_game = g;
    m_upKey = up;
    m_downKey = down;
    m_speed = speed;

    name = "PlayerPaddle";
    int sc[2] = {up, down};
    for(int i = 0; i < 2; i++) {
        m_KeyCB[i].callback = std::bind(&KeyCallBack, this, std::placeholders::_1);
        m_KeyCB[i].sc = sc[i];
        m_game->GeteventHandler()->RegisterKeyCallback(&m_KeyCB[i]);
    }
    CreatePaddle(yPos);
}

PlayerPaddle::PlayerPaddle(Game* g, std::shared_ptr<Ball> b, float yPos, int speed){
    m_game = g;
    m_speed = speed;
    m_AI = true;
    name = "AIPaddle";
    m_ball = b;
    CreatePaddle(yPos);
}

void PlayerPaddle::CreatePaddle(float yPos){
    renderRect paddle;
    paddle.rect.w = 10;
    paddle.rect.h = 100;
    paddle.x = paddle.rect.x = m_game->GetW()*yPos - (paddle.rect.w/2);
    paddle.y = paddle.rect.y = m_game->GetH()*yPos - (paddle.rect.h/2);
    paddle.r = 255;
    paddle.g = 255;
    paddle.b = 255;
    m_rects[name] = paddle;
    m_game->Getrenderer()->AddRectangle(&m_rects);
}

PlayerPaddle::~PlayerPaddle()
{
    //dtor
}

void PlayerPaddle::Update(){
    if(m_AI){
        AIUpdate();
    }
}

void PlayerPaddle::AIUpdate(){
    if(m_rects[name].rect.x-m_ball->getRect("Ball")->rect.x < m_game->GetW()/2 && m_ball->GetDir()->x > 0){
        if(m_ball->getRect("Ball")->rect.y-(m_rects[name].rect.h/2)-(m_ball->getRect("Ball")->rect.h/2) > m_rects[name].rect.y){
            Move(fXY(0,m_speed));
        } else {
            Move(fXY(0,-m_speed));
        }
        CheckBounds();
    }
}

void PlayerPaddle::CheckBounds(){
    if(m_rects[name].y > (m_game->GetH()-(m_rects[name].rect.h))){
        m_rects[name].y = m_rects[name].rect.y = m_game->GetH()-(m_rects[name].rect.h);
    } else if(m_rects[name].y < 0){
        m_rects[name].y = m_rects[name].rect.y = 0;
    }
}

void PlayerPaddle::KeyCallBack(int sc) {
    if(sc == m_upKey){
        Move(fXY(0,-m_speed));
    } else if(sc == m_downKey){
        Move(fXY(0,m_speed));
    }
    CheckBounds();
}
