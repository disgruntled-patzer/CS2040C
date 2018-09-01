#include <iostream> // you can change ’iostream’ with ’that one’...
using namespace std;
class ListArray {
private:		// Variables and functions under this section is 'private'
	int N;		// N stores the number of elements in this list array
	
	// A is an array to store the elements of the list array.
	int A[10]; // question 1a
public:		// Variables and functions under this section is 'public'
	// Constructor of ListArray
	ListArray() : N(0) {} // question 1b
	
	// Obtains the i-th element from the front of the list (0-indexed)
	int get(int i) {
		// ANS: Guard statements could have been added
		if (i < 0 || i >= N) return -1; // Placeholder value to denote error
		return A[i]; // question 1c
	}
	
	// Returns the first index which contains value 'v'
	int search(int v) {
		for (int i = 0; i < N; i++)
			if (A[i] == v)
				return i;
		return -1;
	}
	
	// Insert value 'v' at index 'i'.
	// Everything after index 'i' will be shifted back by one position.
	void insert(int i, int v) {
		if ((N == 10) || (i < 0) || (i > N)) return; // question 1d
		// ANS: direction of loop should be reversed, fixed code is as below
		for (int j = N-1; j >= i; j--) // question 1e
			A[j+1] = A[j];
		A[i] = v;
		N++;
	}
	// Remove item at index 'i'.
	// Everything after index 'i' will be shifted forward by one position.
	void remove(int i) {
		// ANS: Guard statements can also be added
		if (i < 0 || i >= N) return;
		
		for (int j = i; j < N-1; j++) // question 1f
			A[j] = A[j+1];
		N--;
	}
	
	// Print everything in the list, space separated.
	void printList() {
		for (int i = 0; i < N; i++) {
			if (i) cout << " ";	// This is a shortcut for if (i != 0)
			cout << A[i];
		}
		cout << endl;
	}
	
	// Sort the list in ascending order
	void sortList() { // sort array A, question 1g
		//ANS: O(N^2)
		for (int i = 0; i < N-1; i++) {				//O(N)
			for (int j = 1; j < N-i; j++) {			//O(N)
				if (A[j-1] > A[j]) {				//O(1)
				  int tmp = A[j];
				  A[j] = A[j-1];
				  A[j-1] = tmp;
				}
			}
		}
	}
};
int main() {
	// LA is a pointer to a ListArray
	ListArray* LA = new ListArray(); // question 1h
	
	// LA->insert(0, 5) is the same as (*LA).insert(0, 5)
	LA->insert(0, 5);
	LA->insert(0, 1);
	LA->insert(0, 4);
	LA->insert(0, 7);
	LA->insert(0, 2); // we should have A = {2, 7, 4, 1, 5} by now
	
	cout << LA->get(3) << endl; // 1, A[3] = 1
	cout << LA->search(4) << endl; // 2, A[2] = 4
	cout << LA->search(6) << endl; // not found, -1
	LA->remove(1); // we should have A = {2, 4, 1, 5} by now
	cout << LA->search(4) << endl; // 1, A[1] = 4 now
	cout << LA->search(7) << endl; // not found, -1
	
	
	LA->printList(); // unsorted
	LA->sortList(); // we should have A = {1, 2, 4, 5} by now
	LA->printList(); // sorted
	return 0;
} // please copy paste the code above, test compile, and run it yourself
