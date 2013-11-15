///////////////////////////////////////////////////////////////////////////////////////////////////////
//SINGLETON PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Creational
USE: Ensure a class only has one instance and allow anyone seeing that class to have access to it
-------------------------------------------------------------------------------------------*/

#include <boost/noncopyable.hpp>
class Game : boost::noncopyable //inherits privately
{
public:

    static Game* GetPointer()
    {
        static Game gameSingleton;
        return &gameSingleton;
    }
};


class GAME
{
private:
    static GAME * p_game;

    //prevent normal creation/copying
    GAME(){};
    ~GAME(){};
    GAME(const GAME);
    GAME& operator=(const GAME);

public:
    static GAME* GetPoint(){ return p_game; }
    static GAME* Initialise(){ if(p_game == nullptr){ p_game = new GAME(); } return p_game; }
    static void Terminate(){ if(p_game != nullptr){ delete p_game; p_game = nullptr; } }
};

int main()
{
    GAME* game = GAME::Initialise();
}