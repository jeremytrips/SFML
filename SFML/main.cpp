#include "src/game/Game.h"

// Todo debug envent handler


int main() {

    Game game;
    while (!game.getWindow()->isDone()) {
        game.handlInput();
        game.update();
        game.render();
        game.restartClock();
    }

    return 0;
}