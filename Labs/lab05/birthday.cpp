#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii; // we will utilize the natural sort order of the
typedef tuple<int, int, int> iii;    // primitive data types that we paired

int main() { // we wish to sort by ascending month, ascending day, follow by descending year
  iii A = make_tuple(5, 24, -1982);                   // reorder DD/MM/YYYY
  iii B = make_tuple(5, 24, -1980);                           // to MM, DD,
  iii C = make_tuple(11, 13, -1983);          // and then use NEGATIVE YYYY
  vector<iii> birthdays;
  birthdays.push_back(A); birthdays.push_back(B); birthdays.push_back(C);
  sort(birthdays.begin(), birthdays.end());                // that's all :)
// tuple default comparison, compare 1st element, if equals compare 2nd, if also equals compare 3rd, and so on

  for (auto &p: birthdays)
  	// reorder the elements back to their original position and value
    printf("%d %d %d\n", get<1>(p), get<0>(p), -get<2>(p));  // get the value in each position
}

