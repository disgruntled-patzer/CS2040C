#include <bits/stdc++.h>
using namespace std;

class SubTaskC{
    private:
        int N;
        map<int, string>students; //Arrange according to height first and name second since height is distinct

    public:
        
        SubTaskC(){
            students[0] = "RAR";
        }

        void inputstudents(){
            int N;
            cin >> N;
            string name;
            int height;
            for (int i = 0; i < N; ++i){
                cin >> name >> height;
                students[height] = name;
                auto pos = students.find(height);
                --pos; //Find the student to the left of the newcomer
                cout << pos->second << endl;
            }
        }
        
        void printresult(){
            for (auto it = students.begin(); it != students.end(); ++it){
                if (it != students.begin()){
                    cout << " " << it->second; //Print space if not last student
                }
                else{
                    cout << it->second; //Print newline if last student
                }
            }
            cout << "\n";
        }
};

int main(){
    SubTaskC BellCurveGodC;
    BellCurveGodC.inputstudents();
    BellCurveGodC.printresult();
    return 0;
}