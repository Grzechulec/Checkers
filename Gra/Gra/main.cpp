#include <iostream>

#include "Game.h"

using namespace sf;

int main()
{
    //Window
    Game game(1, -1);

    //Game loop
    while (game.isRunning())
    {
        //Update
        game.update();

        //Render
        game.render();

    }

    return 0;
}