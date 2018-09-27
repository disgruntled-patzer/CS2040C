/*PS2 SubTaskD Lau Yan Han: Custom implementation of Linked List
The convention followed here is that the iterator i is pointing to the data AFTER the cursor*/
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

#define TCMAX 10

struct node {
    char data;
    struct node *next;
    struct node *prev;

    node (char data){ //Constructor used to add a new node
        this->data = data; //Assign user input data to the node data (using "this" pointer)
        next = NULL; //Intialize the new node to point to NULL
        prev = NULL;
    }

};

//Implmentation of a Double Circular Linked List with a dummy head
class linkedlist {

    private:
        node *head; //Pointer to head of the list
        node *i; //Iterator to move through list
        node *dummy = new node ('\0'); //Dummy head

    public:

        linkedlist(){ //Constructor used to intialize empty linked list with dummy head
            head = dummy;
            dummy->next = dummy->prev = dummy;
            i = dummy;
        }

        //Shift i to mark start of list
        void begin(){
            i = dummy->next; //i points to position after dummy head
        }

        //Shift i to mark end of list
        void end(){
            i = dummy; //i points to position after tail, which is the dummy head
        }

        //Erase the data at the position before i
        void erase(){
            
            if (i == dummy->next){
                return; //If i points to start of list, do nothing
            }
            //Create a temp node to store the node to be erased
            node *temp;
            temp = i->prev; //Note that i is pointing to position after node that will be erased

            //Perform the actual deletion process here
            temp->prev->next = i;
            i->prev = temp->prev;
            delete temp;
            
        }

        //Insert data at the position before the iterator i
        void insert(char data){

            node *extra = new node (data);
            
            i->prev->next = extra;
            extra->prev = i->prev;
            i->prev = extra;
            extra->next = i;
        }

        //Clear the linked list of all data
        /*void clear(){
            
            while (dummy->next != dummy && dummy->prev != dummy){
                node *temp;
                temp = dummy->next;
                dummy->next = temp->next;
                temp->next->prev = dummy;
                delete temp;
            }
        }*/

        void printlist(){
            
            node *temp = dummy->next;
            
            while (temp != dummy){
                cout << temp->data;
                temp = temp->next;
            }
        }

};

class typing {

    private:
        int TC; //Number of test cases
        linkedlist line[TCMAX]; //Stores lines from all test cases to be printed later on

    public:
        
        //cOonstructor that gets user to input number of test cases
        typing(){
            cin >> TC;
            getchar(); //To prevent the \n character after inputting TC to mess with the strings later
        }

        //Main function to input lines, and take care of <, [ and ] special cases
        void operateline(int row){
            
            char data = getchar(); //Char variable to store input from user

            while (data != '\n') {

                if (data == ']'){ //For ], jump to end of line
                    line[row].end(); //Point the the index to the position after the last character in the line
                }

                else if (data == '<'){ //For <, delete 
                    line[row].erase(); //After deleting last item, i will point to position after the new last item
                    //If i is at start of line, do nothing!
                }

                else if (data == '['){ //For [, go to the start of the line (position zero)
                    line[row].begin();
                }

                else { //For default char, insert one copy of the character into its desired position
                    line[row].insert(data); //the insert function will insert, and then increment i forward by one position
                }

                data = getchar(); //Read the next user input character, if it is \n, then loop will terminate on next iteration
           }
        }

        
        //Print the final result for all test cases
        void printresult(){
            for (int row = 0; row < TC; ++row){ //Iterate through each test case
                line[row].printlist();
                cout << "\n" ;
            }
        }

        //Calls operateline function for all test cases before printing the results
        void solve_all_test_cases(){
            
            for (int row = 0; row < TC; row++){
                operateline(row);
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

    test.solve_all_test_cases();
    cout << "By submitting this source code, I declare that it is MY OWN implementation work. "
        "I fully understand the underlying algorithm behind the code that I wrote and can prove it "
        "to Lab TA if asked." << endl;

    return 0;
}
