#include <bits/stdc++.h>
using namespace std;

class stacks{
    private:
        stack <int> s1, s2, s3;
    
    public:
        void fill_s3(){
            
            int temp;
            char temp1;

            do {
                cin >> temp;
                s1.push(temp);
                temp1 = getchar();
            } while (temp1 != '\n');

        }

        bool possible(){

            int count = 1;

            while (!s1.empty()){
                if (s1.top() == count){
                    s3.push(s1.top());
                    s1.pop();
                    ++count;
                }
                else if (!s2.empty() && s2.top() == count){
                    s3.push(s2.top());
                    s2.pop();
                    ++count;
                }
                else {
                    if (s2.empty() || s2.top() >= s1.top()){
                        s2.push(s1.top());
                        s1.pop();
                    }
                    else {
                        return false;
                    }
                }
            }
            return true;

        }

};

int main(){

    stacks test;

    test.fill_s3();
    
    if (test.possible() == true){
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }

    return 0;
}