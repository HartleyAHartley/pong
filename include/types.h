#ifndef TYPES_H
#define TYPES_H

#include <SDL.h>
#include <functional>
#include <map>
#include <chrono>
#include <iostream>

/** Type Definition for the keyboard callback pointer */
typedef std::function<void(int)> keyCB;
/** Type Definition for chrono clock shorthand */
typedef std::chrono::high_resolution_clock Clock;
/** Type Definition for chrono time_point shorthand */
typedef Clock::time_point Time;

/** Keyboard CallBack
 * \param pointer to keyCallback callback
 * \param ScanCode for key
 * \param If True only returns callback on the first frame of keypress.
 */
struct keyCallback {
    keyCB callback;
    int sc = SDL_SCANCODE_UNKNOWN;
    bool keyDown = false;
};

struct XY {
    XY(){}
    XY(int a, int b){
        x = a;
        y = b;
    }
    int x = 0;
    int y = 0;
    XY operator*(float a) const{
        XY t;
        t.x=x*a;
        t.y=y*a;
        return t;
    }
};

struct fXY {
    fXY(){}
    fXY(float a, float b){
        x = a;
        y = b;
    }
    float x = 0;
    float y = 0;
    fXY operator*(float a) const{
        fXY t;
        t.x=x*a;
        t.y=y*a;
        return t;
    }
    fXY* operator*=(float a) {
        x=x*a;
        y=y*a;
        return this;
    }
};

struct renderRect {
    SDL_Rect rect;
    double x = 0;
    double y = 0;
    void AddX(double val){
        x += val;
        rect.x = (int)x;
    }
    void AddY(double val){
        y += val;
        rect.y = (int)y;
    }
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 255;
    bool render = true;
    XY offset;
    bool collision = false;
};

#endif
