#include <iostream> // you can change <iostream> with <bits/stdc++.h>
// (this is basically a header file that includes every standard library)
using namespace std;

class ListArray {
	private:
		int N;
		int A[10]; // question 1a
	public:
		ListArray() : N(0) {} // question 1b
		int get(int i) {
			return A[i]; // question 1c
		}
		int search(int v) {
			for (int i = 0; i < N; i++)
				if (A[i] == v)
					return i;
			return -1;
		}
		void insert(int i, int v) {
			if ((N == 10) || (i < 0) || (i > N)) return; // question 1d
			for (int j = i; j <= N-1; j++) // question 1e
				A[j+1] = A[j];
			A[i] = v;
			N++;
		}
		void remove(int i) {
			for (int j = i; j < N-1; j++) // question 1f
				A[j] = A[j+1];
			N--;
		}
		void printList() {
			for (int i = 0; i < N; i++) {
				if (i) cout << " ";
				cout << A[i];
			}
			cout << endl;
		}
		void sortList() { // sort array A, question 1g
			for (int i = 0; i < N-1; i++) {
				for (int j = 1; j < N-i; j++) {
					if (A[j-1] > A[j]) {
						int tmp = A[j];
						A[j] = A[j-1];
						A[j-1] = tmp;
					}
				}
			}
		}
};

int main() {
	ListArray* LA = new ListArray(); // question 1h
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
