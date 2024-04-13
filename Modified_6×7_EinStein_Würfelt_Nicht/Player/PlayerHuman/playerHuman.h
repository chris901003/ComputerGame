#include <bits/stdc++.h>
#include "../PlayerBase/playerBase.h"

class PlayerHuman: public PlayerBase {
    private:
    string getMoveDirectionTitle(MoveDirection);
    
    public:
    MoveData getMoveDecision(vector<MoveData>) override;
};