#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

int main() {
    cout << 1000 << " " << 3 << endl;
    int c = 1000;
    while (c--) {
        vector<int>v;
        for(int i = 0; i <= 9; i++)v.push_back(i);
        shuffle(v.begin(), v.end(), default_random_engine(0));
        for (auto &x:v) cout << x << " ";
        cout << endl;
    }
    return 0;
}