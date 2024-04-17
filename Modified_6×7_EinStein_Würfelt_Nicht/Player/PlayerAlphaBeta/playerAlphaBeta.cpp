#include <bits/stdc++.h>
#include "playerAlphaBeta.h"
#define INF 1e9;

using namespace std;

void PlayerAlphaBeta::updateBoard(Board newBoard) {
    board = newBoard;
}

int PlayerAlphaBeta::getLargestNum(Player player) {
    for (int num = 5; num >= 0; num--) {
        pair<int, int> pos = board.getNumPos(player, num);
        if (pos.first != -1) return num;
    }
    return -1;
}

vector<int> PlayerAlphaBeta::impossibleDismiss(Player player) {
    vector<int> result;
    for (int num = 0; num < 6; num++) {
        pair<int, int> myPos = board.getNumPos(player, num);
        if (myPos.first == -1) continue;
        bool isValid = true;
        for (int oppNum = 0; oppNum < 6; oppNum++) {
            pair<int, int> oppPos = board.getNumPos(player == Player::red ? Player::blue : Player::red, oppNum);
            if (oppPos.first == -1) continue;
            if (player == Player::red) {
                if (!(myPos.first > oppPos.first || myPos.second > oppPos.second)) {
                    isValid = false;
                    break;
                }
            } else if (player == Player::blue) {
                if (!(myPos.first < oppPos.first || myPos.second < oppPos.second)) {
                    isValid = false;
                    break;
                }
            }
        }
        if (isValid) {
            result.push_back(num);
        }
    }
    return result;
}

bool PlayerAlphaBeta::testToEnd(Player player, int num) {
    pair<int, int> pos = board.getNumPos(player, num);
    if (pos.first == -1) return false;
    num += player == Player::red ? 0 : 6;
    vector<MoveDirection> redDirections = {MoveDirection::left, MoveDirection::up, MoveDirection::leftUp};
    vector<MoveDirection> blueDirections = {MoveDirection::right, MoveDirection::down, MoveDirection::rightDown};
    set<pair<int, int>> vis;
    queue<pair<int, int>> q;
    q.push(pos);
    while (!q.empty()) {
        pair<int, int> curPos = q.front();
        q.pop();
        if (vis.count(curPos)) continue;
        else vis.insert(curPos);
        if (player == Player::red) {
            if (curPos.first == 5 && curPos.second == 6) {
                return true;
            }
        } else if (player == Player::blue) {
            if (curPos.first == 0 && curPos.second == 0) {
                return true;
            }
        }
        vector<MoveDirection> directions = player == Player::red ? redDirections : blueDirections;
        for (int idx = 0; idx < 3; idx++) {
            pair<int, int> dxdy = board.getDxDy(directions[idx]);
            int nx = curPos.first + dxdy.first;
            int ny = curPos.second + dxdy.second;
            if (nx < 0 || ny < 0 || nx >= 6 || ny >= 7) continue;
            int nxtNum = board.getBoardNum(nx, ny);
            if (nxtNum != -1 && ((nxtNum / 6) == (num / 6))) continue;
            q.push({nx, ny});
        }
    }
    return false;
}

vector<int> PlayerAlphaBeta::possibleToEnd(Player player, vector<int> candidate) {
    vector<int> result;
    for (int index = 0; index < candidate.size(); index++) {
        bool canArriveToEnd = testToEnd(player, candidate[index]);
        if (canArriveToEnd) result.push_back(candidate[index]);
    }
    return result;
}

int PlayerAlphaBeta::getLargest(vector<int> data) {
    int largest = -INF;
    for (auto &x:data) largest = max(largest, x);
    return largest;
}

int PlayerAlphaBeta::defWinOrLoss(Player player) {
    Player oppPlayer = player == Player::red ? Player::blue : Player::red;
    int opponentDefScore = getLargest(possibleToEnd(oppPlayer, impossibleDismiss(oppPlayer)));
    int opponentLargest = getLargestNum(oppPlayer);
    int myDefScore = getLargest(possibleToEnd(player, impossibleDismiss(player)));
    int myLargest = getLargestNum(player);
    if (myDefScore > opponentLargest) {
        return INF;
    }
    else if (myLargest < opponentDefScore) { 
        return -INF;
    }
    return 0;
}

int PlayerAlphaBeta::normalScore(Player player) {
    int total = 0;
    for (int num = 0; num < 6; num++) {
        pair<int, int> myPos = board.getNumPos(player, num);
        if (myPos.first == -1) continue;
        int blockCnt = 0;
        for (int oppNum = 0; oppNum < 6; oppNum++) {
            pair<int, int> oppPos = board.getNumPos(player == Player::red ? Player::blue : Player::red, oppNum);
            if (oppPos.first == -1) continue;
            if (player == Player::red) {
                if (!(myPos.first > oppPos.first || myPos.second > oppPos.second)) {
                    blockCnt += 1;
                }
            } else if (player == Player::blue) {
                if (!(myPos.first < oppPos.first || myPos.second < oppPos.second)) {
                    blockCnt += 1;
                }
            }
        }
        total += (num + 1) * (7 - blockCnt);
    }
    return total;
}

int PlayerAlphaBeta::boardScore(Player player) {
    int winOrLossScore = defWinOrLoss(player);
    if (winOrLossScore != 0) return winOrLossScore;

    int score = normalScore(player);
    return score;
}

MoveData PlayerAlphaBeta::alphaBetaMove(Player player, bool isMax, int alpha, int beta, int depth) {
    
}

MoveData PlayerAlphaBeta::getMoveDecision(vector<MoveData> moveDatas) {
    return alphaBetaMove(moveData[0].player, true, INF, -INF, 0);
}
