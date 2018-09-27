/*PS2 SubTaskC Lau Yan Han*/
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

#define TCMAX 10

class typing {

    private:
        int TC; //Number of test cases
        list <char> line; //String that will be printed for each test case, implemented in Linked-List style
        list <char> AllTC[TCMAX]; //Stores lines from all test cases to be printed later on

    public:
        
        //Get user to input number of test cases
        void inputTC(){
            cin >> TC;
            getchar(); //To prevent the \n character after inputting TC to mess with the strings later
        }

        //Main function to input lines, and take care of <, [ and ] special cases
        void operateline(){
            
            list <char>::iterator i = line.begin(); //i is an iterator that will mark the position after the last inserted character

            char data = getchar(); //Char variable to store input from user

            while (data != '\n') {

                if (data == ']'){ //For ], jump to end of line
                    i = line.end(); //Point the the index to the position after the last character in the line
                }

                else if (data == '<'){ //For <, delete 
                    if (i != line.begin()){ //If i is not at the start of the line
                        --i; //Decrement i to the last item in the line to delete that item (because i points to position after last item)
                        i = line.erase(i); //After deleting last item, i will point to position after the new last item
                    }
                    //If i is at start of line, do nothing!
                }

                else if (data == '['){ //For [, go to the start of the line (position zero)
                    i = line.begin();
                }

                else { //For default char, insert one copy of the character into its desired position
                    line.insert(i, data); //the insert function will insert, and then increment i forward by one position
                }

                data = getchar(); //Read the next user input character, if it is \n, then loop will terminate on next iteration
           }
        }

        
        //Print the final result for all test cases
        void printresult(){
            for (int i = 0; i < TC; i++){ //Iterate through each test case
                list <char>::iterator j;
                for (j = AllTC[i].begin(); j != AllTC[i].end(); ++j){ //For each test case, iterate through the line
                    cout << *j;
                }
                cout << "\n" ;
            }
        }

        //Calls operateline function for all test cases before printing the results
        void solve_all_test_cases(){
            
            for (int i = 0; i < TC; i++){
                operateline();
                AllTC[i].assign(line.begin(), line.end()); //Copy the line contents into the AllTC array to be printed
                line.clear(); //Then erase line contents for next test case
            }
            printresult();
        }

};

int main(int argc, char const *argv[])
{
    //Tells cin/cout and scanf/printf not to update each other
    /*ios_base::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);*/

    typing test;

    test.inputTC();
    test.solve_all_test_cases();

    return 0;
}
