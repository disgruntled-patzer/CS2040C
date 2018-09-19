#include <iostream>
#include <list>
#include <vector>
using namespace std;

#define dead -2

class formation {

    private:
        int N, G; //N = number of soldiers in battle line, G = number of casualty reports
        vector <int> line; //Battle line
        vector <int> commandleft, commandright; //Stores commands that will be output
        int start, end; //Casualty report input
       
    public:
        
        //Fills the battle line with N troops
        void fill_line(){

            cin >> N;

            for (int i = 0; i < N; ++i){
                line.push_back(i);
            }

        }

        //Kill off troop range indicated in the casualty report
        //A dead soldier is defined with the value "-2" (marked by the preprocessor "dead")
        void kill_troops(){
            
            for (int i = start; i <= end; ++i){
                line[i] = dead;
            }

        }
        
        //Output the commands to close up the battle line
        void issue_commands(){
            
            for (int i = 0; i < G; ++i){
                cout << commandleft[i] << " " << commandright[i] << endl;
            }

        }

        //Main driver function to manage the battle line
        void manage_line(){

            fill_line(); //Generate number of troops N and casualty reports G
            cin >> G; 

            int left, right; //Mark the left and right soldiers that are required to close up
            
            for (int i = 0; i < G; ++i){

                cin >> start >> end; //Generate a casualty report and kill off the troops in the report
                kill_troops();

                //The next two loops search for the closest left + right soldiers that are still alive
                for (left = start - 1; left >= 0; --left){
                    if (line[left] != dead){
                        break;
                    }
                }
                for (right = end + 1; right <= N; ++right){
                    if (line[right] != dead){
                        break;
                    }
                }

                //If no surviving soldier to the left or right, then mark the variables with '-1'
                if (left <= 0){
                    left = -1;
                }
                if (right >= N){
                    right = -1;
                }

                //Then store the commands for left and right soldiers to close up into a vector
                commandleft.push_back(left);
                commandright.push_back(right);

            }

            issue_commands();

        }

};

int main(int argc, char const *argv[])
{
    formation tut04;

    tut04.manage_line();

    return 0;
}
