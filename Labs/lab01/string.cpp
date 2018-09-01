#include <bits/stdc++.h>

using namespace std;

int main () {
    string str = "There are two needles in this haystack with needles.";
    string str2("needle");

    // str2 added to the back of str
    // str += str2 is also possible!
    str = str + str2;
    cout << str << '\n';

    cout << (str == str2) << '\n';
    cout << (str2 == "needle") << '\n';

    // 'T' is smaller than 'n' lexicographically (uppercase < lowercase)
    cout << (str < str2) << '\n';

    cout << '\n';

    cout << str.substr(2) << '\n';

    // get position where we found str2 in str
    auto found = str.find(str2);
    // when we can no longer find any more instances of str2
    // in str, we get -1 (an invalid value)
    while (found != -1) {
        cout << "needle found at: " << found << '\n';
        cout << str.substr(found, 6) << '\n';
        // find and get position of next instance of str2
        found = str.find(str2, found + 1);
    }

    cout << '\n';

    // convert c++ string to c string for printf and other C string functions
    printf("(%s) string has length of %d\n", str.c_str(), strlen(str.c_str()));

    cout << '\n';
    string line = "1a2 Mooshak is best";
    string line2 = "123-Mooshak-is-best";

    // initialise stringstream with a string input
    stringstream ss(line);

    string str3;
    int x;

    // read from stringstream (like cin from stdin)
    ss >> x;

    // ensure we read value as an actual int
    cout << x * 3 << '\n';

    // read until no more tokens inside stringstream
    while (ss >> str3) {
        cout << str3 << '\n';
    }

    stringstream ss2;
    // feed input into the stringstream (like cout to stdout)
    ss2 << line2;

    cout << '\n';
    
    // get each token that is splited by the delimiter '-';
    while (getline(ss2, str3,'-')) {
        cout << str3 << '\n';
    }
}