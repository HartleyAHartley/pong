#include "gameerror.h"

GameError::GameError() :
    exception(),
    msg( SDL_GetError() ) {
}

GameError::GameError( const std::string & m ) :
    exception(),
    msg( m ) {
}

GameError::~GameError() throw() {
}

const char * GameError::what() const throw() {
    return msg.c_str();
}
