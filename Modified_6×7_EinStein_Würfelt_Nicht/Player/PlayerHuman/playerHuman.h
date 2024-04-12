#include <bits/stdc++.h>
#include "../PlayerBase/playerBase.h"

class PlayerHuman: public PlayerBase {
    public:
    MoveData getMoveDecision(vector<MoveData>) override;
};