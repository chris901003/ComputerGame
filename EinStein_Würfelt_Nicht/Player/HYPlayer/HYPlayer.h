#include <vector>
#include "../../Board/board.h"
#include "../PlayerAlphaBeta/playerAlphaBeta.h"

using namespace std;

class HYPlayer: public PlayerAlphaBeta {
    private:
    Player currentPlayer;
    int hyMove(Player player, bool isMax, int alpha, int beta, int depth);
    int getPossible(Player, int);

    public:
    HYPlayer(int[5][5], Player);
    MoveData getMoveDecision(vector<MoveData>) override;
};