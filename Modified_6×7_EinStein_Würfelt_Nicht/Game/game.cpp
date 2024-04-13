#include <bits/stdc++.h>
#include "game.h"
#include "../Player/PlayerHuman/playerHuman.h"
#include "../Player/PlayerRandom/playerRandom.h"
#include "../Player/PlayerAlphaBeta/playerAlphaBeta.h"

using namespace std;

PlayerType::PlayerType(PlayerType::Value value) {
    this->value = value;
}

string PlayerType::getTitle() {
    switch (value) {
        case human:
        return "自己玩";
        case random:
        return "隨機玩";
        case alphaBeta:
        return "用Alpha Beta算法玩";
        default:
        return "";
    }
}

PlayerBase* PlayerType::getPlayerManager() {
    switch (value) {
        case human:
        return new PlayerHuman();
        case random:
        return new PlayerRandom();
        case alphaBeta:
        return new PlayerAlphaBeta();
        default:
        return new PlayerBase();
    }
}

PlayerType Game::askPlayerType(int player) {
    bool isFirst = true;
    int num = 0;
    do {
        if (!isFirst) cout << "無該選項，請重新選擇: ";
        else cout << "第" << player << "個玩家: ";
        isFirst = false;
        cin >> num;
    } while (num < 1 || num > PlayerType::valueCnt);
    return PlayerType(PlayerType::Value(num - 1));
}

void Game::initPlayerManager() {
    playerManager1 = player1.getPlayerManager();
    playerManager2 = player2.getPlayerManager();
}

vector<MoveData> Game::getValidMove(int turn) {
    vector<MoveData> validMoves = board.validMove(Player(turn - 1));
    return validMoves;
}

void Game::initGame() {
    cout << "遊戲初始化中" << endl;
    cout << "雙邊玩家提供以下幾種方式" << endl;
    for (int index = 0; index < PlayerType::valueCnt; index++) {
        cout << index + 1 << ". " << PlayerType(PlayerType::Value(index)).getTitle() << endl;
    }

    player1 = askPlayerType(1);
    player2 = askPlayerType(2);
    initPlayerManager();
    cout << "玩家1: " << player1.getTitle() << endl;
    cout << "玩家2: " << player2.getTitle() << endl;

    cout << "初始版面" << endl;
    board.printBoard();
}

void Game::startGame() {
    int turn = 1;
    while (true) {
        cout << "現在是玩家" << turn << "進行" << endl;
        vector<MoveData> moveData = getValidMove(turn);

        PlayerBase* playerManager = turn == 1 ? playerManager1 : playerManager2;
        playerManager->getMoveDecision(moveData);

        break;
    }
}