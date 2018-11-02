/*Trivial Program to test mapping A - Z to 0 - 25, required for PS4 SubtaskB
E.g. A = 1, B = 2, C = 3...*/
#include <iostream>
using namespace std;

int char_to_int(char data){
	return int(data) - 65; //Distance from 0 to A on the ASCII table is 65
}

int main(){
    char x;
    cout << "Enter a character: ";
    cin >> x;
    cout << char_to_int(x) << endl;
}