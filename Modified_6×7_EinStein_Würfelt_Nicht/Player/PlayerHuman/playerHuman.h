#include "../PlayerBase/playerBase.h"

class PlayerHuman: public PlayerBase {
    private:
    string getMoveDirectionTitle(MoveDirection);
    void printValidMove(vector<MoveData>);

    public:
    MoveData getMoveDecision(vector<MoveData>) override;
};