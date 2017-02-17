#include "eventhandler.h"

#include <iostream>
EventHandler::EventHandler(Game* g) {
    m_game = g;
    for(int i=0; i < SDL_NUM_SCANCODES; i++) {
        m_keys[i] = -1;
    }
}

EventHandler::~EventHandler() {}

void EventHandler::Update() {
    SDL_PumpEvents();
    if(Close()) {
        m_game->close();
    }
    UpdateKeys();
    UpdateMouse();
}

bool EventHandler::Close() {
    SDL_Event e;
    if(SDL_PeepEvents(&e, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
        if (e.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

void EventHandler::UpdateMouse(){
    Uint32 mouseState = SDL_GetMouseState(&m_mousePos.x,&m_mousePos.y);
    for(int i = 0; i < 6; i++){
        m_mouseState[i] = mouseState & SDL_BUTTON(i);
    }
}

void EventHandler::UpdateKeys() {
    int numOfKeys = SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_KEYDOWN, SDL_KEYUP);
    SDL_Event kybdEvents[numOfKeys];
    SDL_PeepEvents(kybdEvents, numOfKeys, SDL_GETEVENT, SDL_KEYDOWN, SDL_KEYUP);
    for (int i = 0; i < numOfKeys; i++) {
        if(!kybdEvents[i].key.repeat) {
            if(kybdEvents[i].key.state == SDL_PRESSED) {
                m_keys[kybdEvents[i].key.keysym.scancode] = 0;
            } else if (kybdEvents[i].key.state == SDL_RELEASED) {
                m_keys[kybdEvents[i].key.keysym.scancode] = -1;
            }
        }
    }
    for(int i = 0; i < SDL_NUM_SCANCODES; i++) {
        if(m_keys[i] > -1) {
            for(auto const& j : keyboardCallbacks) {
                if((*j).sc == i && !(*j).keyDown) {
                    (*j).callback(i);
                } else if((*j).sc == i && (*j).keyDown && m_keys[i] == 0) {
                    (*j).callback(i);
                }
            }
            m_keys[i]++;
        }
    }
}

void EventHandler::RegisterKeyCallback(keyCallback * kCB) {
    keyboardCallbacks.insert(keyboardCallbacks.end(), kCB);
}
