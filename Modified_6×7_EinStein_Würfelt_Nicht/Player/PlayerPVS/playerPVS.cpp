#include "./playerPVS.h"
#include "iostream"

using namespace std;

int PlayerPVS::pvsMove(Player player, int alpha, int beta, int depth) {
    return 0;
}

MoveData PlayerPVS::getMoveDecision(vector<MoveData> moveDatas) {
    cout << "PVS player" << endl;
    return moveDatas[0];
}