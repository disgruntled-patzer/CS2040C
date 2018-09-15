#include <bits/stdc++.h>

using namespace std;

void printList(list<int> ll) {
	for(auto x: ll) {
		cout << x << " ";
	}
	cout << endl;
}

// forward_list for single-linkedlist, list for doubly-linkedlist
int main() {
  	list<int> ll({1,2,3}); // initialise using values from array 1,2,3
  	ll.push_back(4); // insert at back
  	ll.push_front(5); // insert at front
  	printList(ll); // should be 5,1,2,3,4

  	auto it = ll.begin(); // iterator at beginning points at element 5(pos 0)
  	ll.insert(it, 6); // insert at front, iterator still points to element 5(pos 1)
  	printList(ll); // should be 6,5,1,2,3,4

  	//it += 2; // bi-directional container, cannot use arithmetic operators (+,-)
  	it++; it++; // can still increment or decrement by 1, iterator now points to element 2(pos 3)
  	ll.insert(it, 2, 7); // insert 2 7s at pos 3, iterator still points to element 2(pos 5)
  	printList(ll); // should be 6,5,1,7,7,2,3,4

  	it = ll.erase(it); // erased 2, returns an iterator to the same pos 5(element 3)
  	printList(ll); // should be 6,5,1,7,7,3,4

  	it--; it--; // iterator moved to pos 3 (element 7)
  	auto it2 = it;
  	it2++; it2++;
  	ll.erase(it, it2); // erase the 2 7s again
  	printList(ll); // should be 6,5,1,3,4

  	//sort(list.begin(), list.end()); // does not work
  	ll.sort(); // for list, use list.sort()

  	cout << ll.front() << " " << ll.back() << endl; // get front and back, should be 1 and 6

  	ll.pop_back(); // remove last element
  	ll.pop_front(); // remove 1st element

  	cout << ll.front() << " " << ll.back() << endl; // should be 3 and 5
}