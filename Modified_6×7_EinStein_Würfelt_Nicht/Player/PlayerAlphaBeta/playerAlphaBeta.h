#include <bits/stdc++.h>
#include "../PlayerBase/playerBase.h"
#include "../../Board/board.h"

class PlayerAlphaBeta: public PlayerBase {
    private:
    Board board;

    public:
    void updateBoard(Board);
    MoveData getMoveDecision(vector<MoveData>) override;
};