#include "../PlayerBase/playerBase.h"
#include "../../Board/board.h"

class PlayerAlphaBeta: public PlayerBase {
    private:
    static const int MAX_DEEP = 4;
    Board board;
    int boardScore(Player);
    vector<int> impossibleDismiss(Player);
    bool testToEnd(Player, int);
    vector<int> possibleToEnd(Player, vector<int>);
    int defWinOrLoss(Player);
    int getLargestNum(Player);
    int getLargest(vector<int>);
    int normalScore(Player);
    int alphaBetaMove(Player player, bool isMax, int alpha, int beta, int depth);

    public:
    void updateBoard(Board);
    MoveData getMoveDecision(vector<MoveData>) override;
};