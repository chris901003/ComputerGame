#pragma once
#include <bits/stdc++.h>
#include "../Game/game.h"

using namespace std;

enum MoveDirection {
    right = 0,
    down = 1,
    rightDown = 2,
    left = 3,
    up = 4,
    leftUp = 5
};

struct MoveData {
    Player player;
    int num;
    MoveDirection direction;

    MoveData(Player, int, MoveDirection);
};

class Board {
    private:
    vector<vector<int>> board;
    map<int, pair<int, int>> chessPlace;
    pair<int, int> getDxDy(MoveDirection);
    vector<MoveData> moveRecord;

    public:
    Board();
    bool move(MoveData);
    vector<MoveData> validMove(Player);
    void printBoard();
};