#pragma once
#include "../Board/board.h"

using namespace std;

class PlayerType {
    public:
    enum Value {
        human,
        random,
        alphaBeta,
        valueCnt
    };
    PlayerType(Value);
    string getTitle();

    private:
    Value value;
};

class Game {
    private:
    PlayerType player1 = PlayerType(PlayerType::human);
    PlayerType player2 = PlayerType(PlayerType::human);
    Board board = Board();

    PlayerType askPlayerType(int);

    public:
    void initGame();
};