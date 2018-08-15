/* PS0 Subtask B
This program reads integer pairs that are input by the user.
For each input pair, the program will output the sum of the integers
It terminates when it reads an integer pair 0 0
In contrast to SubtaskA, which accepts integers from 0 < 2^30 - 1, 
SubtaskB accepts integers from 0 < 2^63 - 1*/

#include <iostream>
#include <limits.h>
using namespace std;

//Basic linked-list node
struct node {
    unsigned long long data1; //First integer
    unsigned long long data2; //Second integer
    struct node *next; //Pointer to next node

    node (unsigned long long data1, unsigned long long data2){ //Constructor used to add new node
        this->data1 = data1;
        this->data2 = data2;
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
        void append(unsigned long long data1, unsigned long long data2){
            node *last  = head; //Intialize a counter to mark where the last node is
            node *extra = new node(data1, data2); // Initialize new node containing the user data

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
        void output(){
            int counter = 1;
            node *temp = head;

            //Keep adding each integer pair together until a 0 0 pair is reached
            while (temp->data1 != 0 || temp->data2 != 0){
                cout << temp->data1 + temp->data2 << "\n";
                temp = temp->next;
                counter++;
            }
        }
};

int main(int argc, char const *argv[])
{
    unsigned long long a, b; //Two integers to be added

    LinkedList list; //Intialize a linkedlist object called "list"

    //Each pair of user input integers is added to end of lit
    while (a != 0 || b != 0){ //Terminate when 0 0 is detected
        cin >> a;
        cin >> b;
        list.append(a, b);
    }

    list.output();

    return 0;
}
