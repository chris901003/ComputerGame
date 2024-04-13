#include <bits/stdc++.h>
#include "playerRandom.h"

using namespace std;

MoveData PlayerRandom::getMoveDecision(vector<MoveData> moveDatas) {
    int moveCnt = moveDatas.size();
    int chooseNum = rand() % moveCnt;
    return moveDatas[chooseNum];
}
