#ifndef PLAYERPADDLE_H
#define PLAYERPADDLE_H

#include <memory>

class Game;
class Ball;
#include "gameobject.h"
#include "types.h"

class PlayerPaddle : public GameObject
{
    public:
        PlayerPaddle(const char* name, Game* g, bool ai, float yPos= 0.125f, int speed = 500, SDL_Scancode up=SDL_SCANCODE_W, SDL_Scancode down=SDL_SCANCODE_S);
        ~PlayerPaddle();
        void KeyCallBack(int sc);
        void Update();

    protected:

    private:
        keyCallback m_KeyCB[4]; //!< Struct for holding keycallback info.
        int m_upKey;
        int m_downKey;
        int m_speed;
        bool m_AI = false;
        void CreatePaddle(float yPos);
        void AIUpdate();
        void CheckBounds();
        float m_AITimer = 0;
        XY m_dir = {};
        std::shared_ptr<GameObject> m_ball;
};

#endif // PLAYERPADDLE_H
