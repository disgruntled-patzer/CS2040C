/* PS0 Subtask C*/

#include <iostream>
#include <cstdio>
#include <limits.h>
using namespace std;

#define INPUTMAX 10

/*Basic linked-list node
In each node, there is an array that can store up to 10 integers
Every array cell is intialized to zero for ease of calculation later on*/
struct node {
    unsigned long long data[INPUTMAX] = {0};
    struct node *next; //Pointer to next node

    node (unsigned long long data[INPUTMAX]){ //Constructor used to add new node
        int counter;

        //A loop will be run to store the data in the new node
        for (counter = 0; counter < INPUTMAX; counter++){
            this->data[counter] = data[counter];
        }

        next = NULL;
    }
};

//Linkedlist class containing the necessary functions
class LinkedList {

    public:
        node *head; //Pointer to head of list
        LinkedList(){
            head = NULL; //Constructor used to intialize empty linked list
        }

        //Add a node to the end of the list
        void append (unsigned long long data[INPUTMAX]){
            node *last  = head; //Intialize a counter to mark where the last node is
            node *extra = new node(data); // Initialize new node containing the user data

            //If the list is initially empty, then the new node becomes the head
            if (head == NULL){
                head = extra;
            }
            else { //Traverse down the list
                while (last->next != NULL){ //Stop only when "last" is pointing to NULL; that means it is last node
                    last = last->next; //Otherwise, go to the next node
                }
                last->next = extra; //Set the original last node to point to the new node
            }
        }

        
        //Traverse the list to add the integers together
        void output (){
            int counter = 1;
            node *temp = head;

            //Keep adding each line of integers until the end of the node
            while (temp != NULL){
                cout << sum(temp->data) << "\n";
                temp = temp->next;
                counter++;
            }
        }
        
        //Sums up all the data in each node
        unsigned long long sum (unsigned long long data[INPUTMAX]){
            int counter;
            unsigned long long sum = 0;

            //Since the array cells are zero by default, we can just add up everything
            //without having to worrying about any cells that were not filled in by user
            for (counter = 0; counter < INPUTMAX; counter++){
                sum = sum + data[counter];
            }

            return sum;

        }
};

int main(int argc, char const *argv[]) {
    
    //Array of up to 10 integers to be added
    unsigned long long data[INPUTMAX] = {0};

    int counter; //Used in the loop for reading user input data
    char checkline; //Used to detect newline character
    bool finalinput = false; //Flag used to check that the user has entered final input (0 0)

    LinkedList list; //Intialize a linkedlist object called "list"

    //Nested loop: Input integers from the user until a new line is reached, then repeat the process
    while (finalinput == false){ //Outer loop: Traverse the entire list, Terminate when final input is detected
        for (counter = 0; counter < INPUTMAX; counter++){ //Inner loop: Traverse through the data array in each node
            cin >> data[counter];
            checkline = getchar(); //This checks for whitespace after every integer
            if (checkline == '\n'){ //If the whitespace is a new line character, then exit inner loop
                //Final if statement: Check that user has entered final input (0 0)
                //This statement ensures that in the edge case where user inputs integers after 0 0 (e.g. 0 0 1 2)
                //Then the code will not mistake it as a final input
                if (data[0] == 0 && data[1] == 0 && counter == 1){ 
                    finalinput = true;
                }
                break;
            }
        }
        //Once the new line is reached, append the resulting sum (assuming it is not final input)to a new node.
        if (finalinput == false){
            list.append(data);

            //Then reset the original data array to zero and move on to a new node
            for (counter = 0; counter < INPUTMAX; counter++){
                data[counter] = 0;
            } 
        }
        
    }

    list.output();

    return 0;
}
