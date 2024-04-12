#include <bits/stdc++.h>
#include "playerAlphaBeta.h"

using namespace std;

MoveData PlayerAlphaBeta::getMoveDecision(vector<MoveData> moveDatas) {
    cout << "Alpha-Beta have override it." << endl;
    return moveDatas[0];
}
