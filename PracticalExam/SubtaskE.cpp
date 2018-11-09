#include <bits/stdc++.h>
using namespace std;

class SubTaskC{
    private:
        int N;
        map<int, deque<string>>students;
        //Still arrange according to height same as SubTaskC, but in each height create a deque of names

    public:
        
        SubTaskC(){
            students[0].push_back("RAR"); //RAR is of course at the height 0 deque
        }

        //Inputs the results and prints the "left-hand" student for each input at the same time
        void inputstudents(){
            cin >> N;
            string name;
            int height;
            for (int i = 0; i < N; ++i){
                cin >> name >> height;
                students[height].push_back(name); //New student joins back of queue
                auto pos = students.find(height);
                --pos; //Then student to left of new student is at the front of the previous queue
                cout << (pos->second).front() << endl;
            }
        }
        
        //Print the final lineup of students
        void printresult(){
            int count = 0; //To keep track of when to use space and when to use newline
            
            //Iterate through whole map
            for (auto it = students.begin(); it != students.end(); ++it){ 
                
                //For each height, iterate through deque, reading the rear elements and removing them
                while (!(it->second).empty()){
                    cout << (it->second).back(); //Read the name first
                    (it->second).pop_back(); //Before removing it
                    if (count < N){ //Keep track of whether last word has been reached
                        cout << " "; //If not yet reached, print space
                    } //If reached, exit and print newline
                    ++count;
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