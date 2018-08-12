/*A more robust linked-list test program that makes greater usage of functions.
Here, the main properties being tested are the addition of nodes to the end of the list
and deleting a node that contains a specified data*/

#include <iostream>
using namespace std;

//This is a basic linked-list node
//data variable represents data stored in each node, *ptr points to the next node in the list
struct node {
    int data;
    struct node *ptr;
};

void append (node **headref, int newdata);
void deletenode(node **headref, int key);
void deletenodeN(node **headref, int N);
void printlist (node *n);

int main(int argc, char const *argv[])
{
    int input, length; //Input: To store user input, Length = To store initial list length
    int counter; //Used for running loops

    node *head  = NULL; //Start with an empty list

    cout << "Enter list length: "; //Linked lists can be variable length, unlike arrays!
    cin >> length;

    //User inputs data into the linked list
    for (counter = 1; counter <= length; counter++){
        cout << "Enter data for Node " << counter << ": ";
        cin >> input;
        append (&head, input);
    }

    printlist(head);

    //To test that our deletenode function works
    cout << "Input a data to be deleted from the list: ";
    cin >> input;
    deletenode(&head, input);
    printlist(head);

    //To test that deletenodeN function works
    cout << "Input a node to delete: ";
    cin >> input;
    deletenodeN(&head, input);
    printlist(head);

    return 0;
}

//Add a node to the end of the linked list
//Note the headref pointer to pointer: It points to the head, which in turn points to start of the list
void append (node **headref, int newdata){ 

    //Counter used to mark where the last node is. It is initalized to point at the head
    //But it will traverse down the linked list later on
    node *last = *headref;
    
    node *extra = NULL; //Initialize new node called "extra"
    extra  = new node; //Allocate dynamic memory of "node" size to the new node
    extra->data = newdata; //Assign the data to the new node
    extra->ptr = NULL; //Since new node is at the end of the list, it will point to NULL

    //If the list is initially empty, then the new node becomes the head
    if (*headref == NULL){
        *headref = extra;
    }
    else{ //Traverse down the list
        while (last->ptr != NULL){ //Stop only when "last" is pointing to NULL; that means it is last node
            last = last->ptr; //Otherwise, go to the next node
        }
        last->ptr = extra; //Set the original last node to point to the new node
    }
}

//Traverse the list finding the first node which contains the key, and delete that node
void deletenode(node **headref, int key) {

    //Edge Case 1: If the list is initially empty
    if (*headref == NULL){
        cout << "List is empty\n";
        return;
    }

    //If list is not empty, then initialize a "finder" variable to point to the head
    node *finder = *headref; //This variable will later traverse down the list to find the key
    node *previous; //This will mark the node that is before "finder"

    //Edge Case 2: If the head itself contains the key
    if (finder->data == key){
        *headref = finder->ptr; //Assign head to next node
        delete finder; //Delete the original node that contained the key, and free its allocated data
        return;
    }

    //Default case: Traverse down the list to find the key
    while (finder != NULL && finder->data != key){
        previous = finder;
        finder = finder->ptr;
    }
    
    //After loop exits, there are two possible scenarios:
    //Scenario 1: Loop exited without finding key
    if (finder == NULL){ //Note: not *finder == NULL. We want to see whether the finder POINTS to NULL
        cout<<"Key not found\n";
        return;
    }
    //Scenario 2: Loop has found the key. "finder" is pointing to it while "previous" is ponting to previous node
    else{
        previous->ptr = finder->ptr; //Link the previous node to the node after "finder"
        delete finder; //Then delete the node that contains the key
    }
}

//Delete a node at position N in the linked list
void deletenodeN(node **headref, int N){

    //Edge Case 1: List is empty
    if (*headref == NULL){
        cout << "List is empty\n";
        return;
    }

    //Intialize "finder" and "previous" variables same as deletenode function
    node *finder = *headref;
    node *previous;

    //Edge Case 2: Node to be deleted is the first node
    if (N == 1){
        *headref = finder->ptr;
        delete finder; //Then we delete the node straightaway, no need to use "previous" variable
    }

    //Default: Intialize a "counter" variable to traverse the list using a loop
    int counter = 1;

    //Use a do-while loop to ensure previous-finder variable updates are done at least once
    //If we use a for/while loop, then in the special case N = 2, loop will exit without updating 
    do {
        counter++; //Start at counter = 2, since N = 1 is already taken care of in Edge Case 2
        previous = finder;
        finder = finder->ptr; //previous-finder is updated similarly to deletenode function
        if (finder == NULL){ //If N is longer than list length, exit
            cout << "Data input exceeds list length\n";
            return;
        } //Note that counter is updated before previous-finder
        //This is to make sure the NULL check is always performed
        //Especially in the special case where N is greater than list length by 1
    } while (counter < N);

    //At the end of the do-while loop, "finder" points to the node N that will be deleted
    //While "previous" points to the previous node. Hence, perform the necessary delete functions
    previous->ptr = finder->ptr;
    delete finder;

}

//Traverse the linked list to print out its values
void printlist(node *n){ //n is initalized to start at the head, before traversing down

    int counter = 1;

    /*Note we use n != NULL instead of n->ptr != NULL. If we use the latter, then the loop will break
    when the last note is reached, and the data in the last node will not be printed. So instead, we
    let the n variable "exit" the end of the list by checking only when the structure itself is NULL,
    instead of checking whether the structure points to NULL. This allows the last node data to be printed*/
    while (n != NULL){
        cout << "Node " << counter << " contains " << n->data << "\n";
        n = n->ptr;
        counter++;
    }
}
