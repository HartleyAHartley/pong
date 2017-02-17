#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL.h>
#include <list>
#include <map>
#include <game.h>

#include "types.h"

class Game;

class EventHandler {
public:
    /** Default constructor */
    EventHandler(Game* gameObj);
    /** Default destructor */
    ~EventHandler();
    /** Event Updater */
    void Update();
    /** Add Keyboard CallBack
     * \param reference to keyCallback struct
     * \return Number of successful Callbacks registered
     */
    void RegisterKeyCallback(keyCallback * kCB);
    XY* GetMousePos(){return &m_mousePos;}
    bool GetMouseState(int id){return &m_mouseState[id];}

protected:

private:
    /** Handles Quit Events
     * \return Returns true if quit event is found
     */
    bool Close();
    /** Handles Keyboard Events */
    void UpdateKeys();
    /** Handles Mouse Events */
    void UpdateMouse();
    XY m_mousePos;
    bool m_mouseState[6];
    Game * m_game; //!< Reference to the game eventhandler is attached to.
    int m_keys[SDL_NUM_SCANCODES]; //!< Scancode keys that are held down.
    std::list<keyCallback*> keyboardCallbacks; //!< List of callbacks to the keyboard.

};

#endif // EVENTHANDLER_H
