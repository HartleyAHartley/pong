#include "playerpaddle.h"
#include "game.h"

PlayerPaddle::PlayerPaddle(Game* g, int speed, SDL_Scancode up, SDL_Scancode down)
{
    name = "PlayerPaddle";
    m_game = g;
    m_upKey = up;
    m_downKey = down;
    m_speed = speed;

    int sc[2] = {up, down};
    for(int i = 0; i < 2; i++) {
        m_KeyCB[i].callback = std::bind(&KeyCallBack, this, std::placeholders::_1);
        m_KeyCB[i].sc = sc[i];
        m_game->GeteventHandler()->RegisterKeyCallback(&m_KeyCB[i]);
    }

    renderRect paddle;
    paddle.rect.w = 10;
    paddle.rect.h = 100;
    paddle.x = paddle.rect.x = m_game->GetW()/8 - (paddle.rect.w/2);
    paddle.y = paddle.rect.y = m_game->GetH()/2 - (paddle.rect.h/2);
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

void PlayerPaddle::KeyCallBack(int sc) {
    if(sc == m_upKey){
        Move(fXY(0,-m_speed));
    } else if(sc == m_downKey){
        Move(fXY(0,m_speed));
    }
    if(m_rects[name].y > (m_game->GetH()-(m_rects[name].rect.h))){
        m_rects[name].y = m_rects[name].rect.y = m_game->GetH()-(m_rects[name].rect.h);
    } else if(m_rects[name].y < 0){
        m_rects[name].y = m_rects[name].rect.y = 0;
    }
}
