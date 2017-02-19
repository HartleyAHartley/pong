#include "playerpaddle.h"
#include "game.h"
#include "ball.h"

PlayerPaddle::PlayerPaddle(const char* name, Game* g, bool ai, float yPos, int speed, SDL_Scancode up, SDL_Scancode down)
{
    m_game = g;
    m_speed = speed;
    m_name = name;
    if(ai){
        m_AI = true;
        m_ball = m_game->GetGameObject("Ball");
    } else {
        m_upKey = up;
        m_downKey = down;
        m_AI = false;
        int sc[2] = {up, down};
        for(int i = 0; i < 2; i++) {
            m_KeyCB[i].callback = std::bind(&KeyCallBack, this, std::placeholders::_1);
            m_KeyCB[i].sc = sc[i];
            m_game->GeteventHandler()->RegisterKeyCallback(&m_KeyCB[i]);
        }
    }
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
    m_rects[m_name] = paddle;
    m_game->Getrenderer()->AddRectangle(&m_rects);
}

PlayerPaddle::~PlayerPaddle()
{
    //dtor
}

void PlayerPaddle::Update(){
    if(m_AI){
        m_AITimer += m_game->getDTime();
        if(m_AITimer > 0.025){
            AIUpdate();
            m_AITimer = 0;
        }
        if(m_dir.y != 0){
            Move(m_dir*m_speed);
            CheckBounds();
        }
    }
}

void PlayerPaddle::AIUpdate(){
    SDL_Rect* ball = &m_ball->getRect("Ball")->rect;
    fXY* ballDir = (fXY*)m_ball->GetInfo();

    if((m_rects[m_name].x < m_game->GetW()/2 && ballDir->x < 0) || (m_rects[m_name].x > m_game->GetW()/2 && ballDir->x > 0)){
        if(ballDir->y > 0){
            m_dir.y = 1;
        } else if (ballDir->y < 0){
            m_dir.y = -1;
        }
        int ballPos = ball->y-(m_rects[m_name].rect.h/2)-(ball->h/2)-m_rects[m_name].rect.y;
        if(m_dir.y == 1 && ballPos < 10){
            m_dir.y = 0;
        } else if(m_dir.y == -1 && ballPos > 10){
            m_dir.y = 0;
        }
    }
}

void PlayerPaddle::CheckBounds(){
    if(m_rects[m_name].y > (m_game->GetH()-(m_rects[m_name].rect.h))){
        m_rects[m_name].y = m_rects[m_name].rect.y = m_game->GetH()-(m_rects[m_name].rect.h);
    } else if(m_rects[m_name].y < 0){
        m_rects[m_name].y = m_rects[m_name].rect.y = 0;
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
