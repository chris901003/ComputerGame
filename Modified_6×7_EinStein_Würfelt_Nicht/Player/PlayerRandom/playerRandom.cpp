#include <bits/stdc++.h>
#include "playerRandom.h"

using namespace std;

MoveData PlayerRandom::getMoveDecision(vector<MoveData> moveDatas) {
    cout << "Random have override it." << endl;
    return moveDatas[0];
}
