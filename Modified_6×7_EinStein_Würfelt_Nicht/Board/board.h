#pragma once
#include <bits/stdc++.h>
#include "../Game/game.h"

using namespace std;

enum MoveDirection {
    right,
    down,
    rightDown,
    left,
    up,
    leftUp
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

    public:
    Board();
    bool move(MoveData);
    void printBoard();
};