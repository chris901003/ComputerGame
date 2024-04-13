#include <bits/stdc++.h>
#include "playerHuman.h"

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

MoveData PlayerHuman::getMoveDecision(vector<MoveData> moveDatas) {
    cout << "Human have override it." << endl;
    cout << "總共有" << moveDatas.size() << "種選擇" << endl;
    for (int index = 0; index < moveDatas.size(); index++) {
        cout << index + 1 << ". " << moveDatas[index].num << " 往 " << getMoveDirectionTitle(moveDatas[index].direction) << endl;
    }
    return moveDatas[0];
}
