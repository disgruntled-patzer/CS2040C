#include <bits/stdc++.h>

using namespace std;

void print_array(int* arr) {
	for(int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}
	cout << '\n';
}

int main () {
	// WARNING: if using this for speedup, do not mix cin with scanf
    // or mix cout with printf
	ios_base::sync_with_stdio(false); cin.tie(0);

	// initialise fixed sized array of size 10
	int arr[] = {0,1,2,3,4,5,6,7,8,9};
	print_array(arr);

	// reverse the entire array
	reverse(arr, arr + 10);
	print_array(arr);

	// reverse from pos 2 to pos 7(exclusive)
	reverse(arr + 2, arr + 7);
	print_array(arr);

	// reverse a string is possible too!
	string str = "Hello World!";
	reverse(str.begin(), str.end());
	cout << str << '\n';

	cout << '\n';

	// jumble up the entire array
	random_shuffle(arr, arr + 10);
	print_array(arr);

	// ensure nth pos of array is the correct element if array is sorted
	// also guarantees all elements before nth pos is smaller(or equal) than the nth element
	// and all elements after nth pos is larger(or equal) than nth element
	nth_element(arr, arr + 4, arr + 10);
	cout << arr[4] << '\n'; // in correct pos
	cout << arr[7] << '\n'; // some other random value
	print_array(arr);

	// ensure nth pos of array is the correct element if array is sorted(backwards)
	// also guarantees all elements before nth pos is larger(or equal) than the nth element
	// and all elements after nth pos is smaller(or equal) than nth element
	nth_element(arr, arr + 5, arr + 10, greater<int>());
	cout << arr[5] << '\n'; // in correct pos
	cout << arr[8] << '\n'; // some other random value
	print_array(arr);

	cout << '\n';

	// 1 iteration of bubblesort
	print_array(arr);
	for(int j = 0; j < 9; j++) {
		// if element in current pos j is larger than j + 1, swap them
		if (arr[j] > arr[j + 1]) {
			swap(arr[j], arr[j + 1]);
			print_array(arr);
		}
	}
	
	cout << '\n';

	//binary search the element (ensure array is sorted for algo to work properly!)
	sort(arr, arr + 10);
	print_array(arr);
	// lower_bound -> find smallest element larger or equal than specified
	auto it = lower_bound(arr, arr + 10, 0);

	// get the position it is at, just minus by arr!
	auto pos = it - arr;
	cout << pos << " " << *it << '\n';

	// upper_bound -> find smallest element larger than specified
	auto it2 = upper_bound(arr, arr + 10, 5);

	// get the position it is at, just minus by arr!
	auto pos2 = it2 - arr;
	cout << pos2 << " " << *it2 << '\n';

	cout << '\n';
	
	// remove duplicates directly preceding each number
	int arr2[] = {
		10,
		20,20,20,
		30,30,
		20,20,
		10,10
	};

	// returns the iterator/pointer to the last element of the modified array
	auto it3 = unique(arr2, arr2 + 10);

	// should give {10,20,30,20,10}
	for(auto a = arr2; a != it3; a++) cout << *a << " ";
	cout << '\n';

}