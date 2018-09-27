#include <bits/stdc++.h>

using namespace std;

void printList(deque<int> dq) {
	for(auto x: dq) {
		cout << x << " ";
	}
	cout << endl;
}

int main() {
	deque<int> dq({1,2,3}); // initialise using values from array 1,2,3
	cout << dq[0] << " " << dq[1] << " " << dq[2] << endl; // difference from list, can do random access
  	dq.push_back(4); // insert at back
  	dq.push_front(5); // insert at front
  	printList(dq); // should be 5,1,2,3,4

  	dq[3] = 6; // can also modify
  	printList(dq); // should be 5,1,2,6,4

  	auto it = dq.begin(); // iterator at beginning points at element 5(pos 0)
  	dq.insert(it, 6); // insert at front, iterator now points to element 5(pos 1)
  	printList(dq); // should be 6,5,1,2,6,4

  	it += 2; // random-access container, can do arithmetic operations on iterator (+, -)
  	dq.insert(it, 2, 7); // insert 2 7s at pos 3, iterator remains at pos 3
  	printList(dq); // should be 6,5,1,7,7,2,6,4

  	dq.erase(it); // erased 7, iterator now points to the pos 2 (element 1)
  	printList(dq); // should be 6,5,1,7,2,6,4

  	it -= 2; // iterator points back to beginning
  	dq.erase(it, it + 2); // erase the 6 and 5
  	printList(dq); // should be 1,7,2,6,4

  	sort(dq.begin(), dq.end());

  	cout << dq.front() << " " << dq.back() << endl; // get front and back, should be 1 and 7

  	dq.pop_back(); // remove last element
  	dq.pop_front(); // remove 1st element

  	cout << dq.front() << " " << dq.back() << endl; // should be 2 and 6
}