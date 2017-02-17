#ifndef BALL_H
#define BALL_H

#include <string>

class Game;
#include "gameobject.h"
#include "types.h"

class Ball : public GameObject
{
    public:
        Ball(Game* g, int speed = 250);
        ~Ball();
        void Update();

    protected:
        void collisionCB(GameObject * obj);

    private:
        int m_speed;
        fXY m_dir;
        void WallCollsion();
        std::string lastCollision = "";
};

#endif // BALL_H
