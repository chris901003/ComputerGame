#pragma once
#include <bits/stdc++.h>
#include "../../Board/board.h"

using namespace std;

class PlayerBase {
    public:
    virtual MoveData getMoveDecision(vector<MoveData>);
};