/****************************************************************
* Kara Jensen (mail@karajensen.com) 
*****************************************************************/
#pragma once

#include <boost/noncopyable.hpp>

class Game : boost::noncopyable
{
public:

    /**
    * Create/get the game object
    * @return the pointer to the game object
    */
    static Game* Get();

    /**
    * Destroy the game object
    */
    static void Release();

private:

    // If not using boost, don't define the copy/ass operators
    Game& operator=(const Game&);
    Game(const Game&); 

    static Game* sm_game;  ///< Singleton pointer
};