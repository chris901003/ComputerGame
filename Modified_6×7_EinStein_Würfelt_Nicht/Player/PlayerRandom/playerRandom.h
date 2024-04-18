#include "../PlayerBase/playerBase.h"

class PlayerRandom: public PlayerBase {
    public:
    MoveData getMoveDecision(vector<MoveData>) override;
};