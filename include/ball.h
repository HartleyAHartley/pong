#ifndef BALL_H
#define BALL_H

#include <string>
#include <random>

class Game;
#include "gameobject.h"
#include "types.h"

class Ball : public GameObject
{
    public:
        Ball(const char* name, Game* g, int speed = 250);
        ~Ball();
        void Update();
        void* GetInfo(){return &m_dir;}

    protected:
        void collisionCB(GameObject * obj);

    private:
        int m_speed;
        fXY m_dir;
        void WallCollsion();
        void RandomDir();
        std::string lastCollision = "";
        std::mt19937 mt;
        std::uniform_real_distribution<double> dir;
};

#endif // BALL_H
