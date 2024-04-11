#include <bits/stdc++.h>
#include "board.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"

using namespace std;

Board::Board() {
    board = vector<vector<int>>(6, vector<int>(7, -1));
    vector<int> red = {0, 1, 2, 3, 4, 5};
    vector<int> blue = {6, 7, 8, 9, 10, 11};
    shuffle(red.begin(), red.end(), default_random_engine(rand()));
    shuffle(blue.begin(), blue.end(), default_random_engine(rand()));
    int index = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j + i < 3; j++)
            board[i][j] = red[index++];
    index = 0;
    for (int i = 5; i > 2; i--)
        for (int j = 4 + (5 - i); j < 7; j++)
            board[i][j] = blue[index++];
}

void Board::printBoard() {
    for (auto &x:board) {
        for (auto &y:x) {
            if (y == -1) cout << WHITE << "X" << " ";
            else if (y < 6) cout << RED << y << RESET << " ";
            else cout << BLUE << to_string(y % 6) << RESET << " ";
        }
        cout << endl;
    }
}