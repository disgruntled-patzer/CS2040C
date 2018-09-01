#include <bits/stdc++.h>

using namespace std;

// set up to read from an input file when compiling locally
void setIO() {
  #ifdef LOCAL_PROJECT // check my C++.sublime-build
    freopen("test.txt", "r", stdin);
  #endif
}

void print_array(int* arr) {
	for(int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}
	cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    setIO();
    int arr1[10];
    int arr2[10];
    for(int i = 0; i < 10; i++) {
    	cin >> arr1[i];
    	scanf("%d", &arr2[i]);
    }
   	print_array(arr1);
	print_array(arr2);

}