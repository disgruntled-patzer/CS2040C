#include <bits/stdc++.h>

using namespace std;

int n,k;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    string x;
    stack<int> st;
    int cur = 0;
    int y;
    for(int i = 0; i < k; i++) {
        cin >> x;
        if (x == "undo") {
            cin >> y;
            while (y--) {
                cur = st.top();
                st.pop();
            }
        } else {
            y = stoi(x);
            st.push(cur);
            cur = (((cur + y) % n) + n) % n; //This is the shortest way to implement a modulus operation
        }
    }
    cout << cur;
}