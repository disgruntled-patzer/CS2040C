#include<bits/stdc++.h>

using namespace std;

string line, x;
vector<string> vec;
set<string> st;

int main() {
    //freopen("in.txt", "r", stdin);
    while (cin >> x) {
        // how to store/what to do with each input?
        for(string y: vec) {
          if (x != y) {
            st.insert(x+y);
            st.insert(y+x);
          }
        }
        vec.push_back(x);
    }
    
    // other necessary code.
    for(string x: st)  cout << x << endl;
}