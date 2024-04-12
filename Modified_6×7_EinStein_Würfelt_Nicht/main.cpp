#include "Board/board.h"
#include "Game/game.h"

int main() {
    Board board = Board();
    board.printBoard();
    vector<MoveData> data = board.validMove(Player::red);
    cout << data.size() << endl;
    for (auto &x: data) {
        cout << x.num << " " << x.direction << endl;
    }

    return 0;
}