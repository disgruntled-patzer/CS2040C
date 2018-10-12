#include <bits/stdc++.h>
using namespace std;

#define MAX_NM 1000010

int N, M, ans, Jack[MAX_NM], Jill[MAX_NM]; // N & M are up to 1M each

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); // important if using cin/cout since large I/O (1M)
  //freopen("in.txt", "r", stdin); // for easier testing, comment this out before submitting

  while ((cin >> N >> M), (N || M)) {
    // input here, can use this array or any other std you know of.
    for (int i = 0; i < N; i++) cin >> Jack[i];
    for (int j = 0; j < M; j++) cin >> Jill[j];
    // important, reinitialise ans for each test case.
    ans = 0;

    // main code here
    unordered_set<int> st;
    for (int i = 0; i < N; i++) st.insert(Jack[i]);
    for (int j = 0; j < M; j++) ans += st.find(Jill[j]) != st.end(); // gives 1 if found else 0
    
    /* 2 pointer solution to get the set intersection of the 2 sorted arrays
    int ptr1 = 0, ptr2 = 0;
    while (ptr1 < N && ptr2 < M) {
      if (Jack[ptr1] == Jill[ptr2]) {
        ans++;
        ptr1++;
        ptr2++;
      } else if (Jack[ptr1] > Jill[ptr2]) {
        ptr2++;
      } else {
        ptr1++;
      }
    } 
    */

    cout << ans << endl;
  }
  return 0;
}
