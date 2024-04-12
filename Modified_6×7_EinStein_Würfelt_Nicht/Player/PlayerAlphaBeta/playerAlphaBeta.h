#include <bits/stdc++.h>
#include "../PlayerBase/playerBase.h"

class PlayerAlphaBeta: public PlayerBase {
    public:
    MoveData getMoveDecision(vector<MoveData>) override;
};