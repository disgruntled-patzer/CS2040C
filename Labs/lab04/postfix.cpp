#include <string>
#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

bool isOperand(char c){ //Verify that c is NOT an operator
    return c != '+' && c != '-' && c != '*';
} //Return 1 if not an operator

int getVal(int a, int b, char op){
    if (op == '+')
        return a+b;
    else if (op == '-')
        return a-b;
    else
        return a*b;
}

int evaluate(string exp){
    stack<int> s;
    for (int i=0;i < exp.length(); i++){
        if (isOperand(exp[i])) //If i is not an operator, then push it into stack
            s.push(int(exp[i]-'0')); //Conversion of char to int: Need to do -'0'
        else{ //If i is operator
            int second = s.top(); //Push out top two numbers from stack
            s.pop();
            int first = s.top();
            s.pop();
            int val = getVal(first, second, exp[i]); //Then do the postfix operator on the numbers
            s.push(val); //And push in the new value into stack
        }
    }
    return s.top();
}

int main()
{
    string exp = "69+9*"; //Note: No spaces included, only can do single digit operations
    cout << evaluate(exp) << '\n';
    return 0;
}
