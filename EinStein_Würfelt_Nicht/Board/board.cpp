#include "board.h"
#include <iostream>
#include <random>

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

Board::Board() { }

Board::Board(int curBoard[5][5]) {
    board = vector<vector<int>>(5, vector<int>(5, -1));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int piece = curBoard[i][j] - 1;
            if (piece != -1) {
                if (piece < 6) piece += 6;
                else piece -= 6;
            }
            board[i][j] = piece;
            if (piece != -1) {
                chessPlace[piece] = {i, j};
            }
        }
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
    if (nxtPos.first < 0 || nxtPos.first >= 5 || nxtPos.second < 0 || nxtPos.second >= 5) return false;
    int nxtNum = board[nxtPos.first][nxtPos.second];

    if (moveData.player == Player::red) {
        if (direction != MoveDirection::right && direction != MoveDirection::down && direction != MoveDirection::rightDown) return false;
    } else {
        if (direction != MoveDirection::left && direction != MoveDirection::up && direction != MoveDirection::leftUp) return false;
    }
    lastBeforeChageBoardData.push_back({{curPos.first, curPos.second, num}, {nxtPos.first, nxtPos.second, nxtNum}});
    if (nxtNum != -1) chessPlace.erase(nxtNum);
    chessPlace[num] = nxtPos;
    board[nxtPos.first][nxtPos.second] = num;
    board[curPos.first][curPos.second] = -1;
    moveRecord.push_back(moveData);
    return true;
}

void Board::undo() {
    moveRecord.pop_back();
    vector<vector<int>> lastChange = lastBeforeChageBoardData.back();
    lastBeforeChageBoardData.pop_back();
    board[lastChange[0][0]][lastChange[0][1]] = lastChange[0][2];
    board[lastChange[1][0]][lastChange[1][1]] = lastChange[1][2];
    if (lastChange[0][2] != -1) {
        chessPlace[lastChange[0][2]] = {lastChange[0][0], lastChange[0][1]};
    }
    if (lastChange[1][2] != -1) {
        chessPlace[lastChange[1][2]] = {lastChange[1][0], lastChange[1][1]};
    }
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
            if (nxtPos.first < 0 || nxtPos.first >= 5 || nxtPos.second < 0 || nxtPos.second >= 5) continue;
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

bool Board::isStopMove() {
    int topLeft = board[0][0];
    int bottomRight = board[4][4];
    if (topLeft == -1 || bottomRight == -1) return false;
    return (((topLeft / 6) == 1) && ((bottomRight / 6) == 0));
}

vector<vector<int>> Board::getBoard() {
    return board;
}

void Board::setBoard(vector<vector<int>> newBoard) {
    board = newBoard;
}

void Board::printBoard() {
    cerr << "=======================" << endl;
    for (auto &x:board) {
        for (auto &y:x) {
            if (y == -1) cerr << "X" << " ";
            else if (y < 6) cerr << y << " ";
            else cerr << to_string(y) << " ";
        }
        cerr << endl;
    }
}