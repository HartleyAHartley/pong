#ifndef PLAYERPADDLE_H
#define PLAYERPADDLE_H

class Game;
#include "gameobject.h"
#include "types.h"

class PlayerPaddle : public GameObject
{
    public:
        PlayerPaddle(Game* g, int speed = 500, SDL_Scancode up=SDL_SCANCODE_W, SDL_Scancode down=SDL_SCANCODE_S);
        ~PlayerPaddle();
        void KeyCallBack(int sc);

    protected:

    private:
        keyCallback m_KeyCB[4]; //!< Struct for holding keycallback info.
        int m_upKey;
        int m_downKey;
        int m_speed;
};

#endif // PLAYERPADDLE_H
