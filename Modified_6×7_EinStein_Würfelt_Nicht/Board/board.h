#pragma once
#include <bits/stdc++.h>

using namespace std;

enum Player {
    red,
    blue
};

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
    vector<MoveData> moveRecord;

    public:
    Board();
    pair<int, int> getDxDy(MoveDirection);
    bool move(MoveData);
    vector<MoveData> validMove(Player);
    void printBoard();
    int getPlayerChessCnt(Player);
    int getBoardNum(int, int);
    pair<int, int> getNumPos(Player, int);
};