#include <string>
#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

bool isOperator(char c){
    if (c == '+' || c == '-' || c == '*')
        return true;
    else
        return false;
}

int getVal(int a, int b, char op){
    if (op == '+')
        return a+b;
    else if (op == '-')
        return a-b;
    else if (op == '*')
        return a*b;
}

string get_next(string str, int tok_start){
    int tok_end = tok_start + 1;
    while (tok_end < str.length() && str[tok_end] != ' '){
        tok_end++;
    }
    return str.substr(tok_start, tok_end - tok_start);
}

int string_to_int(string snum)
{
    int num = 0;
    for(int i=0;i<snum.length();i++)
    {
        int cur = snum[i] - '0';
        num = num * 10 + cur;
    }
    return num;
}

int evaluate(string exp){
    // http://www.cplusplus.com/reference/stack/stack/
    stack<int> s;
    int idx = 0;
    while (idx < exp.length())
    {
        string tok = get_next(exp, idx);
        if (tok.length() == 1 && isOperator(tok[0]))
        {
            int second = s.top();
            s.pop();
            int first = s.top();
            s.pop();
            int val = getVal(first, second, tok[0]);
            s.push(val);
        }
        else
        {
            s.push(string_to_int(tok));
        }
        idx += tok.length() + 1;
    }
    return s.top();
}

int main()
{
    string expr = "20 30 + 400 *";
    cout << evaluate(expr) << endl;
    return 0;
}
