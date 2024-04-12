#include "Board/board.h"
#include "Game/game.h"
#include "Player/PlayerHuman/playerHuman.h"
#include "Player/PlayerRandom/playerRandom.h"
#include "Player/PlayerAlphaBeta/playerAlphaBeta.h"

int main() {
    Game game = Game();
    game.initGame();
    game.startGame();
    return 0;
}