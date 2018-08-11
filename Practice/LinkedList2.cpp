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
void printlist (node *n);

int main(int argc, char const *argv[])
{
    node *head  = NULL; //Start with an empty list
    append (&head, 6);
    append (&head, 5);
    append (&head, 7);
    printlist(head);
    deletenode(&head, 5);
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
    if (finder == NULL){
        cout<<"Key not found\n";
        return;
    }
    //Scenario 2: Loop has found the key. "finder" is pointing to it while "previous" is ponting to previous node
    else{
        previous->ptr = finder->ptr; //Link the previous node to the node after "finder"
        delete finder; //Then delete the node that contains the key
    }


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
