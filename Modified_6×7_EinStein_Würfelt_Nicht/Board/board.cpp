#include <bits/stdc++.h>
#include "board.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"

using namespace std;

MoveData::MoveData(Player player, int num, MoveDirection direction) {
    this->player = player;
    this->num = num;
    this->direction = direction;
}

Board::Board() {
    board = vector<vector<int>>(6, vector<int>(7, -1));
    vector<int> red = {0, 1, 2, 3, 4, 5};
    vector<int> blue = {6, 7, 8, 9, 10, 11};
    shuffle(red.begin(), red.end(), default_random_engine(rand()));
    shuffle(blue.begin(), blue.end(), default_random_engine(rand()));
    int index = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j + i < 3; j++) {
            board[i][j] = red[index];
            chessPlace[red[index++]] = {i, j};
        }
    index = 0;
    for (int i = 5; i > 2; i--)
        for (int j = 4 + (5 - i); j < 7; j++) {
            board[i][j] = blue[index];
            chessPlace[blue[index++]] = {i, j};
        }
}

pair<int, int> Board::getDxDy(MoveDirection direction) {
    switch (direction) {
        case MoveDirection::right:
        return {0, 1};
        case MoveDirection::down:
        return {1, 0};
        case MoveDirection::rightDown:
        return {1, 1};
        case MoveDirection::left:
        return {0, -1};
        case MoveDirection::up:
        return {-1, 0};
        case MoveDirection::leftUp:
        return {-1, -1};
    }
}

bool Board::move(MoveData moveData) {
    int num = moveData.num;
    MoveDirection direction = moveData.direction;

    if (num < 0 || num >= 6) return false;
    if (moveData.player == Player::blue) num += 6;
    if (!chessPlace.count(num)) return false;

    pair<int, int> curPos = chessPlace[num];
    pair<int, int> dxdy = getDxDy(direction);
    pair<int, int> nxtPos = {curPos.first + dxdy.first, curPos.second + dxdy.second};
    if (nxtPos.first < 0 || nxtPos.first >= 6 || nxtPos.second < 0 || nxtPos.second >= 7) return false;
    int nxtNum = board[nxtPos.first][nxtPos.second];

    if (moveData.player == Player::red) {
        if (direction != MoveDirection::right && direction != MoveDirection::down && direction != MoveDirection::rightDown) return false;
        if (nxtNum != -1 && nxtNum < 6) return false;
    } else {
        if (direction != MoveDirection::left && direction != MoveDirection::up && direction != MoveDirection::leftUp) return false;
        if (nxtNum != -1 && nxtNum >= 6) return false;
    }
    if (nxtNum != -1) chessPlace.erase(nxtNum);
    chessPlace[num] = nxtPos;
    board[nxtPos.first][nxtPos.second] = num;
    board[curPos.first][curPos.second] = -1;
    moveRecord.push_back(moveData);
    return true;
}

vector<MoveData> Board::validMove(Player player) {
    vector<MoveData> response;
    int num = 0 + (player == Player::red ? 0 : 6);
    int baseDir = 0 + (player == Player::red ? 0 : 3);
    for (int offset = 0; offset < 6; offset++) {
        if (!chessPlace.count(num + offset)) continue;
        pair<int, int> curPos = chessPlace[num + offset];
        for (int dir = 0; dir < 3; dir++) {
            MoveDirection direction = MoveDirection(baseDir + dir);
            pair<int, int> dxdy = getDxDy(direction);
            pair<int, int>nxtPos = {curPos.first + dxdy.first, curPos.second + dxdy.second};
            if (nxtPos.first < 0 || nxtPos.first >= 6 || nxtPos.second < 0 || nxtPos.second >= 7) continue;
            int nxtNum = board[nxtPos.first][nxtPos.second];
            if (nxtNum != -1 && (nxtNum / 6) == ((num + offset) / 6)) continue;
            MoveData data = MoveData(player, (num + offset) % 6, direction);
            response.push_back(data);
        }
    }
    return response;
}

int Board::getPlayerChessCnt(Player player) {
    int offset = player == Player::red ? 0 : 6;
    int result = 0;
    for (int index = 0; index < 6; index++) {
        result += chessPlace.count(offset + index);
    }
    return result;
}

int Board::getBoardNum(int x, int y) {
    return board[x][y];
}

pair<int, int> Board::getNumPos(Player player, int num) {
    num += player == Player::red ? 0 : 6;
    if (!chessPlace.count(num)) return {-1, -1};
    return chessPlace[num];
}

bool Board::isGameEnd() {
    vector<MoveData> redMove = validMove(Player::red);
    vector<MoveData> blueMove = validMove(Player::blue);
    return (redMove.size() == 0) && (blueMove.size() == 0);
}

vector<vector<int>> Board::getBoard() {
    return board;
}

void Board::setBoard(vector<vector<int>> newBoard) {
    board = newBoard;
}

void Board::printBoard() {
    cout << "=======================" << endl;
    for (auto &x:board) {
        for (auto &y:x) {
            if (y == -1) cout << WHITE << "X" << " ";
            else if (y < 6) cout << RED << y << RESET << " ";
            else cout << BLUE << to_string(y % 6) << RESET << " ";
        }
        cout << endl;
    }
}