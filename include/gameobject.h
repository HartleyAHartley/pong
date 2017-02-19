#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <functional>
#include <list>
#include <string>
#include "types.h"

class Game;

class GameObject
{
    public:
        /** Default constructor */
        GameObject();
        /** Default destructor */
        virtual ~GameObject();
        /** Get self identifier */
        unsigned long long getself(){return self;}
        /** Destroy this object */
        virtual void Update();
        const char* getName(){return m_name;}
        renderRect* getRect(std::string id){return &m_rects[id];}
        virtual void* GetInfo(){return nullptr;};

    protected:
        bool operator==(GameObject* obj){return self==obj->getself();}
        unsigned long long self;
        bool collision();
        virtual void collisionCB(GameObject * obj);
        Game* m_game; //!< Pointer to game object
        std::map<std::string, renderRect> m_rects; //!< Struct for holding rectangle rendering info
        //* Moves all of the Rects */
        void Move(fXY movement);
        void Set(XY pos);
        const char* m_name = "";


    private:
};

#endif // GAMEOBJECT_H
