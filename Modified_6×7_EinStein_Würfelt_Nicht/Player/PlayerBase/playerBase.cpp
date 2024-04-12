#include <bits/stdc++.h>
#include "playerBase.h"

using namespace std;

MoveData PlayerBase::getMoveDecision(vector<MoveData> moveDatas) {
    cout << "Please override it." << endl;
    return moveDatas[0];
}