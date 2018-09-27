/*PS2 SubTaskA Lau Yan Han*/
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#define TCMAX 10

class typing {

    private:
        int TC; //Number of test cases
        string line; //String that will be printed for each test case
        string AllTC[TCMAX]; //Stores strings from all test cases to be printed later on

    public:
        
        //Get user to input number of test cases
        void inputTC(){
            cin >> TC;
            getchar(); //To prevent the \n character after inputting TC to mess with the strings later
        }

        //Main function to input lines, and take care of <, [ and ] special cases
        //For Task 1, [ special case is ignored
        void operateline(){
            
            int i = 0; //i is an iterator that will run through the line
            char data = getchar(); //Char variable to store input from user

            while (data != '\n') {

                if (data == ']'){ //For ], jump to end of line
                    i = line.length(); //Point the the index after the last character in the line
                }

                else if (data == '<'){ //For <, delete 
                    if (i > 0){ //If delete is not at the start of the line
                        line.erase(i - 1, 1); //Note i - 1 not i; i is incremented after inserting characters, thus it always points one step ahead of the char to be deleted
                        --i; //Shift i back since the length of the line is now decreased
                    }
                    //If delete is at the start of the line, do nothing!
                }

                else { //For default char, insert one copy of the character into its desired position
                    line.insert(i, 1, data);                 
                    ++i; //Then increment for next loop
                }

                data = getchar(); //Read the next user input character, if it is \n, then loop will terminate on next iteration
           }
        }

        
        //Print the final result for all test cases
        void printresult(){
            //cout<<"Hi"<<endl;
            for (int i = 0; i < TC; i++){ //Iterate through each test case
                for (int j = 0; j < AllTC[i].length(); j++){ //For each test case, iterate through the line
                    cout << AllTC[i][j];
                }
                cout << "\n" ;
            }
        }

        //Calls operateline function for all test cases before printing the results
        void solve_all_test_cases(){
            
            for (int i = 0; i < TC; i++){
                operateline();
                AllTC[i].assign(line); //Copy the line contents into the AllTC array to be printed
                line.clear(); //Then erase line contents for next test case
            }
            printresult();
        }

};

int main(int argc, char const *argv[])
{
    
    typing test;

    test.inputTC();
    test.solve_all_test_cases();

    return 0;
}
