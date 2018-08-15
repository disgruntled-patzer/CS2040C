#include <iostream>
using namespace std;

struct node {
    int data;
    struct node *next;
    struct node *prev; //Double linked list with "nexx" and "prev"

    node (int data){ //Constructor used to add a new node
        this->data = data; //Assign user input data to the node data (using "this" pointer)
        next = NULL; //Intialize the new node to point to NULL (for both next and prev)
        prev = NULL;
    }
};

class LinkedList {

    public:
        node *head;
        LinkedList(){
            head = NULL; //Constructor to initialize an empty linked list
        }

    //Add a node to the start of the list
    void push (int data){
        node *extra = new node (data);

            //If the list is initially empty, then the new node becomes the head
            if (head == NULL){
                head = extra;
            }
            else {
                extra->next = head; //Assign the new node to point to the original head
                extra->prev = NULL; //Assign the new node to point backwards to NULL
                head->prev = extra; //Assign the old head node to point backwards to new node
                head = extra; //Then mark the new node as the head
            }
        }

    //Delete a node at a given position N
    void deletenodeN(int N){
        
        if (head == NULL){
            return;
        }
        
        node *finder = head; //"Finder" will traverse the list looking for node N

        if (N == 1){
            head = finder->next;
            delete finder;
        }

        int counter = 1;

        do {
            counter++;
            finder = finder->next;
            if (finder == NULL){
                cout << "Data input exceeds list length\n";
                return;
            }
        } while (counter < N);

        finder->prev->next = finder->next;
        delete finder;

    }

    void printlist(){

        int counter = 1;
        node *temp = head;

        while (temp != NULL){
            cout << "Node " << counter << " contains " << temp->data << "\n";
            temp = temp->next;
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
        cout << "Insert data at the start of the list: ";
        cin >> input;
        test.push (input);
    }

    test.printlist();

    //Test that deletenodeN function works
    cout << "Now select a node to delete: ";
    cin >> input;
    test.deletenodeN(input);
    test.printlist();

    return 0;
}
