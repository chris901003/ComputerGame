#include <bits/stdc++.h>
#include "playerHuman.h"

using namespace std;

MoveData PlayerHuman::getMoveDecision(vector<MoveData> moveDatas) {
    cout << "Human have override it." << endl;
    return moveDatas[0];
}
