#include<bits/stdc++.h>

using namespace std;

string line, x;

int main() {
    //freopen("in.txt", "r", stdin);
    vector<string> vec;
    set<string> st;
    while (cin >> x) {
        // how to store/what to do with each input?
        for(string k: vec) {
            string c1 = k + x;
            string c2 = x + k;
            st.insert(c1);
            st.insert(c2);
        }
        vec.push_back(x);
    }
    
    // other necessary code.
    for(string k: st) cout << k << endl;
}