#include <bits/stdc++.h>
using namespace std;

int main() {
  cout << "Problem 1: Searching for a specific value v in the array - binary search" << endl;
  vector<int> A({3,5,1,2,7}); // A is initially unsorted
  sort(A.begin(), A.end()); // after this line, A is sorted to {1,2,3,5,7}, O(n log n)
  cout << "7 is at index " << lower_bound(A.begin(), A.end(), 7)-A.begin() << endl; // 7 is at index 4, O(log n)
  cout << "8 is at index " << lower_bound(A.begin(), A.end(), 8)-A.begin() << endl; // 8 is at index 5 (beyond last, so actually it does not exist)
  cout << endl;

  cout << "Problem 2: Finding the min/max/k-th smallest/largest value in the (static) array" << endl;
  vector<int> B({3,5,1,2,7}); // B=A is initially unsorted
  cout << "min = " << *min_element(B.begin(), B.end()) << endl; // should be 1, O(n)
  for (auto &v : B) cout << v << " "; // B is not actually sorted, it is 2,1,3,5,7, with the 2nd
  cout << endl;
  cout << "max = " << *max_element(B.begin(), B.end()) << endl; // should be 7, O(n)
  for (auto &v : B) cout << v << " "; // B is not actually sorted, it is 2,1,3,5,7, with the 2nd
  cout << endl;
  nth_element(B.begin(), B.end()+B.size()/2, B.end()); // expected O(n), detailed analysis to be discussed later in CS3230
  cout << B.at(B.size()/2) << endl; // the median should be 3
  for (auto &v : B) cout << v << " "; // B is not actually sorted, it is 2,1,3,5,7
  cout << endl;
  cout << endl;

  cout << "Problem 3: Testing for uniqueness and deleting duplicates" << endl;
  vector<int> C({3,5,3,1,2,2,7,1,1,7}); // C contains many duplicates
  sort(C.begin(), C.end()); // important step, O(n log n)
  auto num_unique = unique(C.begin(), C.end())-C.begin(); // call unique, O(n)
  for (auto &v : C) cout << v << " "; // notice the first num_unique elements are unique
  cout << endl;
  for (int i = 0; i < num_unique; i++) cout << C[i] << " "; // we can just print num_unique elements of C
  cout << endl;
  cout << endl;

  cout << "Problem 4: Counting how many time a specific value v appear in the array" << endl;
  vector<int> D({3,5,3,1,2,2,7,1,1,7}); // D=C contains many duplicates
  sort(D.begin(), D.end());
  for (int i = 0; i < (int)D.size(); i++) { // O(n)
    int counter = 1; // assume that D[i] is unique... but
    printf("D[%d] = %d ", i, D[i]);
    while (i+1 < (int)D.size() && D[i+1] == D[i]) { // advance further
      i++;
      counter++;
    }
    printf("has %d copies\n", counter);
  }
  cout << endl;

  cout << "Problem 5: Set intersection/union between two sorted arrays A and B" << endl;
  vector<int> E({2,8,5});
  vector<int> F({1,8,2,9});
  sort(E.begin(), E.end());
  sort(F.begin(), F.end());
  vector<int> intersection_result;
  set_intersection(E.begin(), E.end(), // O(n log n) internally
                   F.begin(), F.end(),
                   back_inserter(intersection_result));
  cout << "Intersection result: ";
  for (auto &v : intersection_result) cout << v << ' ';
  cout << endl;
  vector<int> union_result;
  set_union(E.begin(), E.end(), // O(n log n) internally
            F.begin(), F.end(),
            back_inserter(union_result));
  cout << "Union result: ";
  for (auto &v : union_result) cout << v << ' ';
  cout << endl;
  cout << endl;
  // PS: Ranald has the O(n+m) solution that uses two pointers like problem 6 below

  cout << "Problem 6: Finding a target pair x and y such that x+y equals to a target z" << endl;
  vector<int> G({3,5,3,1,2,2,7,1,1,7});
  sort(G.begin(), G.end());
  int z = 14; // change this value to test
  bool found = false;
  for (int i = 0; i < (int)G.size(); i++) { // O(n*log n)
    int x = G[i];
    int y = z-G[i]; // we want to know if this exists
    if (binary_search(G.begin(), G.end(), y)) { // O(log n)
      printf("Found %d+%d = %d in vector G\n", x, y, z);
      found = true;
      break;
    }
  }
  if (!found)
    printf("Cannot find x+y = %d in vector G\n", z);

  for (int i = 0, j = (int)G.size()-1; i < j; ) { // O(n)
    int x = G[i]; // the front (low number)
    int y = G[j]; // the back (high number)
    if (x+y > z) // too high
      j--; // decrease y
    else if (x+y < z) // too low
      i++; // increase x
    else { // x+y == z
      printf("Found %d+%d = %d in vector G\n", x, y, z);
      found = true;
      break;
    }
  }
  if (!found)
    printf("Cannot find x+y = %d in vector G\n", z);

  return 0;
}



