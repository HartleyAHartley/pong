#include "renderer.h"

Renderer::Renderer(Uint32 flags, unsigned int h, unsigned int w, bool f) {
    if ( SDL_Init( flags ) != 0 )
        throw GameError();

    if(f){
        if ( SDL_CreateWindowAndRenderer( w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP,
                                      &m_window, &m_renderer ) != 0 )
            throw GameError();
    } else{
        if ( SDL_CreateWindowAndRenderer( w, h, SDL_WINDOW_SHOWN,
                                          &m_window, &m_renderer ) != 0 )
            throw GameError();
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    SDL_Quit();
}

void Renderer::Draw() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear( m_renderer );
    // Show the window
    for(const auto& i : renderRectangles) {

        for(auto const& h : *i){
            if((h.second.render)) {
                RenderRect(&h.second);
            }
        }
    }
    SDL_RenderPresent( m_renderer );
}

bool Renderer::RenderRect(const renderRect * rr) {
    if(SDL_SetRenderDrawColor(m_renderer, rr->r, rr->g, rr->b, rr->a)) {
        return false;
    } else {
        if(SDL_RenderFillRect(m_renderer, &rr->rect)) {
            return false;
        }
    }
    return true;
}


void Renderer::AddRectangle(std::map<std::string, renderRect>* rr) {
    renderRectangles.insert(renderRectangles.end(), rr);
}
