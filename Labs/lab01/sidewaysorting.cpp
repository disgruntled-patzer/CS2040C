#include <bits/stdc++.h>

using namespace std;

void setIO() {
  #ifdef LOCAL_PROJECT
    freopen("in.txt", "r", stdin);
  #endif
}

int r,c;
string x, arr[20];

bool cmp(string a, string b) { // can declare comparision function outside
                               // instead of using lambda (your preference)
  for(int i = 0; i < c; i++) {
    a[i] = tolower(a[i]);
    b[i] = tolower(b[i]);
  }
  return a < b;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    setIO();
    while ((cin >> r >> c), r && c) { // read current r and c, exit if both 0
      for(int i = 0; i < c; i++) arr[i] = ""; // reinitialise each string     
      
      for(int i = 0; i < r; i++) {
        cin >> x; // get the 'row' string
        for(int j = 0; j < c; j++) { // append the characters to their respective 'column string'
          arr[j] += x[j];
        }
      }

      // must use stable_sort! Consider the case where the character being compared
      // is the same character, but 1 is upper and the other is lower case 
      stable_sort(arr, arr + c, [](string a, string b) { // c++ lambda
        for(int i = 0; i < c; i++) { // convert each character to the lower case
                                     // so we are effectively 'ignoring' lower or upper cases
          a[i] = tolower(a[i]); // the comparison function here will create a new copy of the string
          b[i] = tolower(b[i]); // so we can replace the values here to all lower characters without affecting
        }                       // affecting the original
        return a < b;
      });

      for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
          cout << arr[j][i]; // print out the 'sorted' column strings
                             // back in their 'row' format
        }
        cout << endl;
      }
      cout << endl;
    }
}
