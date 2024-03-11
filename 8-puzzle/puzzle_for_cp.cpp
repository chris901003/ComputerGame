// CP Link: https://tioj.ck.tp.edu.tw/problems/1198
#include <bits/stdc++.h>

using namespace std;

struct Node;
Node find_twin_board(Node node);
void read_board(Node &node);
void print_board(Node node);
vector<pair<int,int>> fetch_path_node(Node last_node);

int board_width;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
map<string, pair<int,int>>record;
int goal_board[3][3];

struct Node {
    // board = 目前版面
    vector<vector<int>>board;
    // prev_space_x, prev_space_y = 上一步空白的位置
    int prev_space_x, prev_space_y;
    // space_x, space_y = 分別為空白處的x與y座標
    int space_x, space_y;
    // cost = deep + diff
    int deep, diff, cost;
    // string版本的版面，主要提供紀錄使用
    string board_str;

    // 創建Node的資訊
    void setNode(vector<vector<int>> board, int prev_space_x, int prev_space_y, int deep) {
        this->board = board;
        this->prev_space_x = prev_space_x;
        this->prev_space_y = prev_space_y;
        this->deep = deep;
        find_space();
        diff = distance_to_target();
        cost = diff + deep;
        board_str = board_to_string();
    }

    // 計算A*的cost
    int distance_to_target() {
        int res = 0;
        for (int i=0; i < board_width; i++)
            for (int j = 0; j < board_width; j++) {
                res += board[i][j] != goal_board[i][j];
            }
        // 空白的的方不算在錯誤內
        return res;
    }

    // 找出版面中空白的地方
    void find_space() {
        for (int i = 0; i < board_width; i++)
            for (int j = 0; j < board_width; j++)
                if (board[i][j] == 0) {
                    space_x = i;
                    space_y = j;
                }
    }

    // 將版面轉成string格式
    string board_to_string() {
        string str = "";
        for (auto &x:board)
            for (auto &y:x)
                str += to_string(y);
        return str;
    }

    // 獲取下一步動作
    vector<Node> fetch_next_step() {
        vector<Node> results;
        for (int idx = 0; idx < 4; idx++) {
            int nx = space_x + dr[idx];
            int ny = space_y + dc[idx];
            if (nx < 0 || ny < 0 || nx >= board_width || ny >= board_width) continue;
            swap(board[space_x][space_y], board[nx][ny]);
            Node node = Node();
            node.setNode(board, space_x, space_y, deep + 1);
            results.push_back(node);
            swap(board[space_x][space_y], board[nx][ny]);
        }
        return results;
    }
};

bool operator < (const Node& lhs, const Node& rhs) {
    return lhs.cost > rhs.cost;
}

// 找尋另一個啟示版面
Node find_twin_board(Node node) {
    bool isSwaped = false;
    for (int i = 0; i < board_width; i++) {
        for (int j = 0; j < board_width - 1; j++) {
            if (node.board[i][j] != 0 && node.board[i][j + 1] != 0) {
                swap(node.board[i][j], node.board[i][j + 1]);
                isSwaped = true;
                break;
            }
        }
        if (isSwaped) break;
    }
    Node twin_node = Node();
    twin_node.setNode(node.board, -1, -1, 0);
    return twin_node;
}

// 將版面讀入
void read_board(Node &node) {
    vector<vector<int>>board(board_width, vector<int>(board_width));
    for (auto &x:board) {
        for (auto &y:x)
            cin >> y;
    }
    node.setNode(board, -1, -1, 0);
}

// 從結果往回推，獲取路徑
vector<pair<int,int>> fetch_path_node(Node last_node) {
    vector<pair<int,int>> results;
    Node cur_node = last_node;
    while (cur_node.prev_space_x != -1) {
        results.push_back({cur_node.space_x, cur_node.space_y});
        swap(cur_node.board[cur_node.space_x][cur_node.space_y], cur_node.board[cur_node.prev_space_x][cur_node.prev_space_y]);
        pair<int,int> prev = record[cur_node.board_to_string()];
        cur_node.space_x = cur_node.prev_space_x;
        cur_node.space_y = cur_node.prev_space_y;
        cur_node.prev_space_x = prev.first;
        cur_node.prev_space_y = prev.second;
    }
    results.push_back({cur_node.space_x, cur_node.space_y});
    reverse(results.begin(), results.end());
    return results;
}

void solve() {
    // 將舊的紀錄刪除
    record.clear();

    // 所有節點
    priority_queue<Node> nodes;

    // 初始化讀版
    Node root_node = Node();
    read_board(root_node);
    nodes.push(root_node);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> goal_board[i][j];

    // 加入另一個起始版
    Node twin_board = find_twin_board(root_node);
    nodes.push(twin_board);

    Node goal_node;
    while (nodes.size()) {
        // 拿出當前cost最小的node
        Node cur_node = nodes.top();
        nodes.pop();

        // 已經達到終點，記錄下最後的node後離開
        if (cur_node.diff == 0) {
            goal_node = cur_node;
            break;
        }

        // 過去已經跑過此版面，並且如果尚未跑過就記錄下來
        if (record.count(cur_node.board_str)) continue;
        record[cur_node.board_str] = {cur_node.prev_space_x, cur_node.prev_space_y};

        // 獲取下次的動作
        vector<Node> next_steps = cur_node.fetch_next_step();
        for (auto &node:next_steps) nodes.push(node);
    }

    vector<pair<int,int>> path_node = fetch_path_node(goal_node);
    int steps = path_node.size() - 1;
    cout << steps << endl;
}

int main() {
    board_width = 3;
    solve();
    return 0;
}

// 印出提供的版面
void print_board(Node node) {
    cout << "======= Board =======" << endl;
    for (auto &x:node.board) {
        for (auto &y:x) {
            cout << y << " ";
        }
        cout << endl;
    }
}