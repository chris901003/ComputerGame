#include "playerHuman.h"
#include <iostream>

using namespace std;

string PlayerHuman::getMoveDirectionTitle(MoveDirection direction) {
    switch (direction) {
        case MoveDirection::right:
        return "右";
        case MoveDirection::down:
        return "下";
        case MoveDirection::rightDown:
        return "右下";
        case MoveDirection::left:
        return "左";
        case MoveDirection::up:
        return "上";
        case MoveDirection::leftUp:
        return "左上";
    }
}

void PlayerHuman::printValidMove(vector<MoveData> moveDatas) {
    cout << "總共有" << moveDatas.size() << "種選擇" << endl;
    for (int index = 0; index < moveDatas.size(); index++) {
        cout << index + 1 << ". " << moveDatas[index].num << " 往 " << getMoveDirectionTitle(moveDatas[index].direction) << endl;
    }
}

MoveData PlayerHuman::getMoveDecision(vector<MoveData> moveDatas) {
    cout << "請從以下的幾個移動方法" << endl;
    printValidMove(moveDatas);
    int chooseNum = 0;
    bool firstTime = true;
    do {
        cout << (firstTime ? "你選擇: " : "請輸入合法選擇: ");
        firstTime = false;
        cin >> chooseNum;
    } while (chooseNum <= 0 || chooseNum > moveDatas.size());
    return moveDatas[chooseNum - 1];
}
