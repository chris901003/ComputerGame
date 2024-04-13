#pragma once
#include "../Board/board.h"
#include "../Player/PlayerBase/playerBase.h"

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
    PlayerBase* getPlayerManager();
    Value value;
};

class Game {
    private:
    PlayerType player1 = PlayerType(PlayerType::human);
    PlayerType player2 = PlayerType(PlayerType::human);
    PlayerBase *playerManager1 = new PlayerBase();
    PlayerBase *playerManager2 = new PlayerBase();
    Board board = Board();

    PlayerType askPlayerType(int);
    void initPlayerManager();
    vector<MoveData> getValidMove(int turn);

    public:
    void initGame();
    void startGame();
    void endGame();
};