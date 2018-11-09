#include <bits/stdc++.h>
using namespace std;

class SubTaskD{
    private:
        int N;
        stack<string>students; //Every student that enters is going to stand beside RAR!
    public:
        
        void inputstudents(){
            int N;
            cin >> N;
            string name;
            int height;
            for (int i = 0; i < N; ++i){
                cin >> name >> height;
                cout << "RAR" << endl;
                students.push(name);
            }
        }

        void printresult(){
            cout << "RAR ";
            while (!students.empty()){
                cout << students.top();
                students.pop();
                if (!students.empty()){
                    cout << " ";
                }
                else{
                    cout << "\n";
                }
            }
        }
};

int main(){
    SubTaskD BellCurveGodD;
    BellCurveGodD.inputstudents();
    BellCurveGodD.printresult();
    return 0;
}