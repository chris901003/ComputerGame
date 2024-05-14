#include "../PlayerAlphaBeta/playerAlphaBeta.h"

class PlayerPVS: public PlayerAlphaBeta {
    private:
    int pvsMove(Player player, bool isMax, int alpha, int beta, int depth);

    public:
    MoveData getMoveDecision(vector<MoveData>) override;
};