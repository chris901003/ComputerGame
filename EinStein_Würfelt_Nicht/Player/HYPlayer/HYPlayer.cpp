#include "./HYPlayer.h"
#include "iostream"
#define INF 1e9

using namespace std;

HYPlayer::HYPlayer(int curBoard[5][5], Player player) {
    board = Board(curBoard);
    currentPlayer = player;
}

int HYPlayer::getPossible(Player player, int num) {
    int possible = 1;
    int cur = num - 1;
    while (cur >= 0) {
        pair<int, int>pos = board.getNumPos(player, cur);
        if (pos.first == -1) {
            possible += 1;
            cur -= 1;
        } else {
            break;
        }
    }
    cur = num + 1;
    while (cur < 6) {
        pair<int, int>pos = board.getNumPos(player, cur);
        if (pos.first == -1) {
            possible += 1;
            cur += 1;
        } else {
            break;
        }
    }
    return possible;
}

int HYPlayer::hyMove(Player player, bool isMax, int alpha, int beta, int depth) {
    // cerr << rand() << endl;
    if (board.isStopMove()) {
        int redCnt = board.getPlayerChessCnt(Player::red);
        int blueCnt = board.getPlayerChessCnt(Player::blue);
        if (redCnt == 0) {
            return player == Player::red ? -INF : INF;
        } else if (blueCnt == 0) {
            return player == Player::red ? INF : -INF;
        }
        int redScore = board.getBoardNum(4, 4) % 6;
        int blueScore = board.getBoardNum(0, 0) % 6;
        if (board.getBoardNum(0, 0) == -1 || (redScore > blueScore)) {
            return player == Player::red ? INF : -INF;
        } else if (board.getBoardNum(4, 4) == -1 || (redScore < blueScore)) {
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
        int possible = getPossible(move.player, move.num);
        board.move(move);
        int score = 0;
        if (foundPV) {
            score = -hyMove(player, !isMax, -alpha - 1, -alpha, depth + 1) * possible;
            if (alpha < score && score < beta) {
                score = -hyMove(player, !isMax, -beta, -alpha, depth + 1) * possible;
            }
        } else {
            score = -hyMove(player, !isMax, -beta, -alpha, depth + 1) * possible;
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

MoveData HYPlayer::getMoveDecision(vector<MoveData> moveDatas) {
    int value = -(INF + 1);
    reverse(moveDatas.begin(), moveDatas.end());
    MoveData selection = moveDatas[0];
    for (auto &move: moveDatas) {
        board.move(move);
        int result = -hyMove(move.player, false, -INF, INF, 0);
        board.undo();
        if (result > value) {
            value = result;
            selection = move;
        }
    }
    return selection;
}