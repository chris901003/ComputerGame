#include "playerRandom.h"
#include <random>

using namespace std;

MoveData PlayerRandom::getMoveDecision(vector<MoveData> moveDatas) {
    int moveCnt = moveDatas.size();
    int chooseNum = rand() % moveCnt;
    return moveDatas[chooseNum];
}
