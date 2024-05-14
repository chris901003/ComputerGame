#include "Board/board.h"
#include "Game/game.h"
#include "Player/PlayerHuman/playerHuman.h"
#include "Player/PlayerRandom/playerRandom.h"
#include "Player/PlayerAlphaBeta/playerAlphaBeta.h"
#include <chrono>
#include <iostream>

int main() {
    srand(time(NULL));

    Game game = Game();
    game.initGame();
    auto start = std::chrono::high_resolution_clock::now();
    game.startGame();
    game.endGame();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "執行所花費: " << duration.count() << " 秒" << std::endl;
    return 0;
}