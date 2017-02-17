#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>
#include <SDL.h>

class GameError : public std::exception {
public:
    /** Default constructor */
    GameError();
    /** constructor with error str
     * \param m Error Msg
     */
    GameError( const std::string & );
    /** Default destructor */
    virtual ~GameError() throw();
    /** Return Error String
     * \return Error Str
     */
    virtual const char * what() const throw();

protected:

private:
    std::string msg;
};

#endif // ERROR_H
