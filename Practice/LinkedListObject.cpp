/*Linked-List practice using Object-Oriented Programming. The main functions tested are:
1. Adding node to start of list
2. Adding node to end of list
3. Reversing entire list
4. Printing contents of list*/

#include <iostream>
using namespace std;

struct node {
    int data;
    struct node *ptr;

    node (int data){ //Constructor used to add a new node
        this->data = data; //Assign user input data to the node data (using "this" pointer)
        ptr = NULL; //Intialize the new node to point to NULL
    }
};

class LinkedList {

    public:
        node *head; //Pointer to the head of the list
        LinkedList(){
            head = NULL; //Contructor to initialize a empty linked list
        }

        //Add a node to the start of the list
        void push (int data){
            node *extra = new node (data); // Initialize new node containing the user data

            //If the list is initially empty, then the new node becomes the head
            if (head == NULL){
                head = extra;
            }
            else {
                extra->ptr = head; //Assign the new node to point to the original head
                head = extra; //Then mark the new node as the head
            }
        }
        
        //Add a node to the end of the list
        void append(int data){
            node *last  = head; //Intialize a counter to mark where the last node is
            node *extra = new node(data); // Initialize new node containing the user data

            //If the list is initially empty, then the new node becomes the head
            if (head == NULL){
                head = extra;
            }
            else { //Traverse down the list
                while (last->ptr != NULL){ //Stop only when "last" is pointing to NULL; that means it is last node
                    last = last->ptr; //Otherwise, go to the next node
                }
                last->ptr = extra; //Set the original last node to point to the new node
            }
        }

        //Reverse the entire linked list
        void reverse(){
            if (head == NULL){ //Obviously, an empty list needs no reversing
                return;
            }

            //Initialize a "previous", "current" and "next" node to traverse the list
            node *current = head;
            node *prev = NULL, *next = NULL;

            while (current != NULL){ //When "current" exits the list, the loop is reversed
                next = current->ptr; //Store data of the "next" node before reversing
                current->ptr = prev; //Reverse the "current" node to point to "prev" node
                prev = current;
                current = next; //Advance "prev" and "current" node by one step
            }

            head = prev; //Now mark the new head of the reversed list

        }

        //Traverse the linked list to print its data
        void printlist(){
            int counter = 1;
            node *temp = head; //Initialize a pointer to traverse the list

            while (temp != NULL){
                cout << "Node " << counter << " contains " << temp->data << "\n";
                temp = temp->ptr;
                counter++;
            }
        }
};

int main(int argc, char const *argv[])
{
    LinkedList test; //Initialize a Linked List object and call it "test"
    int input, length; //Input: To store user input, Length = To store initial list length
    int counter; //Used for running loops

    cout << "Enter list length: "; //Linked lists can be variable length, unlike arrays!
    cin >> length;

    //User inputs data into the linked list
    for (counter = 1; counter <= length; counter++){
        cout << "Enter data for Node " << counter << ": ";
        cin >> input;
        test.append (input);
    }

    //Test that the push function works
    cout << "Now add a new data at the front of the list: ";
    cin >> input;
    test.push(input);
    test.printlist();

    //Test that the reverse function works
    test.reverse();
    cout << "The reversed list is as follows: \n";
    test.printlist();

    return 0;
}
