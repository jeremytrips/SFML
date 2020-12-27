#include "src/game/Game.h"

// Improve Envent manager class


int main() {

    Game game;
    while (!game.getWindow()->isDone()) {
        game.update();
        game.render();
        game.lateUpdate();
    }

    return 0;
}