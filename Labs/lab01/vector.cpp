#include <bits/stdc++.h>

using namespace std;

void print_vector(vector<int> vec) {
    // for-based loop to iterate through each element in vec (from vec[0] to vec[vec.size() - 1])
    // &a allows us to use the value directly in vec instead of creating a new copy
    // and also allows us to change the value in vec if necessary
    for(auto &a: vec) {
        cout << a << " ";
    }
    cout << '\n';
}

int main() {
    // WARNING: if using this for speedup, do not mix cin with scanf
    // or mix cout with printf
    ios_base::sync_with_stdio(false); cin.tie(0);

    // initialise a vector of of size 0 (to prevent null)
    vector<int> vec(0);
    cout << vec.empty() << '\n';

    cout << '\n';

    // push back 10 numbers into vector;
    for(int i = 0; i < 10; i++) vec.push_back(i);
    print_vector(vec);

    // pop out last 3 numbers
    for(int i = 0; i < 3; i++) {
        vec.pop_back();
        print_vector(vec);
    }

    cout << '\n';

    // get iterator pointer to the 1st element in vec
    auto it = vec.begin();

    // insert a number at the beginning
    vec.insert(it, 11);
    print_vector(vec);

    // shift iterator to point 3 elements to left (4th element)
    it += 3;

    // insert 2 numbers at pos 3(zero-indexed)
    vec.insert(it, 2, 13);
    print_vector(vec);

    // shift iterator back to point 1 element to right (3rd element)
    it -= 1;

    // insert numbers from another vector at pos 2(zero-indexed)
    vector<int> vec2({15,16,17});
    vec.insert(vec.begin() + 2, vec2.begin(), vec2.end());
    print_vector(vec);

    cout << '\n';

    // remove 3rd number(pos 2) from the vector
    vec.erase(vec.begin() + 2); // zero-based
    print_vector(vec);

    // remove 4th to 7th(exclusive) number from the vector
    vec.erase(vec.begin() + 3, vec.begin() + 6);
    print_vector(vec);

    // check each number and remove the even number
    for(auto a = vec.begin(); a != vec.end();) {
    	if (*a % 2 == 0) {
            vec.erase(a);
        } else {
            a++;
        } 
    }
    print_vector(vec);

    cout << '\n';

    // get and print the 1st and last number of the vector
    cout << vec.front() <<  " " << vec.back() << '\n';

    cout << '\n';
    
    cout << vec.empty() << '\n';

    // empty out the vector
    vec.clear();

    cout << vec.empty() << '\n';
}