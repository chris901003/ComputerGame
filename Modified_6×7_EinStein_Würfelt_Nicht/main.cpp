#include "Board/board.h"
#include "Game/game.h"

int main() {
    Board board = Board();
    board.printBoard();
    MoveData moveData = MoveData(Player::red, 4, MoveDirection::rightDown);
    board.move(moveData);
    board.printBoard();

    return 0;
}