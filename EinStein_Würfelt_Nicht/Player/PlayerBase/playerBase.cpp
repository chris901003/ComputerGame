#include "playerBase.h"
#include <iostream>

using namespace std;

MoveData PlayerBase::getMoveDecision(vector<MoveData> moveDatas) {
    cout << "Please override it." << endl;
    return moveDatas[0];
}