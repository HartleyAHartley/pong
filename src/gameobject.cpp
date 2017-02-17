#include "gameobject.h"
#include "game.h"

GameObject::GameObject()
{
    self = (unsigned long long)this;
}

GameObject::~GameObject()
{
    //dtor
}

void GameObject::Update(){
    return;
}

void GameObject::collisionCB(GameObject * obj){
    return;
}

bool GameObject::collision(){
    bool collision = false;
    for(auto const& i : *m_game->GetGameObjects()){
        if(i.second != this){
            for(auto const& j : i.second->m_rects){
                for(auto const& h : m_rects){
                    if(SDL_HasIntersection(&j.second.rect,&h.second.rect)){
                        collisionCB(&(*i.second));
                        i.second->collisionCB(this);
                        collision = true;
                    }
                }
            }
        }
    }
    return collision;
}

void GameObject::Move(fXY movement){
    for(auto &i : m_rects){
        i.second.AddX((movement.x ) * m_game->getDTime());
        i.second.AddY((movement.y ) * m_game->getDTime());
    }
}

void GameObject::Set(XY pos){
    for(auto &i : m_rects){
        i.second.rect.x = pos.x+i.second.offset.x;
        i.second.rect.y = pos.y+i.second.offset.y;
    }
}
