#include "./playerPVS.h"
#include "iostream"
#define INF 1e9

using namespace std;

int PlayerPVS::pvsMove(Player player, bool isMax, int alpha, int beta, int depth) {
    if (board.isStopMove()) {
        int redCnt = board.getPlayerChessCnt(Player::red);
        int blueCnt = board.getPlayerChessCnt(Player::blue);
        if (redCnt == 0) {
            return player == Player::red ? -INF : INF;
        } else if (blueCnt == 0) {
            return player == Player::red ? INF : -INF;
        }
        int redScore = board.getBoardNum(5, 6) % 6;
        int blueScore = board.getBoardNum(0, 0) % 6;
        if (redScore > blueScore) {
            return player == Player::red ? INF : -INF;
        } else if (redScore < blueScore) {
            return player == Player::red ? -INF : INF;
        } else {
            return -INF;
        }
    }

    Player currentPlayer = isMax ? player : player == Player::red ? Player::blue : Player::red;
    vector<MoveData> moveDatas = board.validMove(currentPlayer);

    if (depth == PlayerAlphaBeta::MAX_DEEP) {
        return -boardScore(player);
    }

    int v = -INF;
    bool foundPV = false;
    for (auto &move: moveDatas) {
        board.move(move);
        int score = 0;
        if (foundPV) {
            score = -pvsMove(player, !isMax, -alpha - 1, -alpha, depth + 1);
            if (alpha < score && score < beta) {
                score = -pvsMove(player, !isMax, -beta, -alpha, depth + 1);
            }
        } else {
            score = -pvsMove(player, !isMax, -beta, -alpha, depth + 1);
        }
        board.undo();
        v = max(v, score);
        if (v > alpha) {
            alpha = v;
            foundPV = true;
        }
        if (alpha > beta) {
            return v;
        }
    }
    return v;
}

MoveData PlayerPVS::getMoveDecision(vector<MoveData> moveDatas) {
    int value = -(INF + 1);
    reverse(moveDatas.begin(), moveDatas.end());
    MoveData selection = moveDatas[0];
    for (auto &move: moveDatas) {
        board.move(move);
        int result = -pvsMove(move.player, false, -INF, INF, 0);
        board.undo();
        if (result > value) {
            value = result;
            selection = move;
        }
    }
    return selection;
}