/*This is a practice linked list program. It first creates a linked-list which consists of
three nodes. The first node is marked using a head node (which doesn't change its position).
Then, a new node is added in front of the first node, and it is marked as the new first node
by getting the head to point to the new node. */

#include <iostream>
using namespace std;

//This is a basic linked-list node
//data variable represents data stored in each node, *ptr points to the next node in the list
struct node {
    int data;
    struct node *ptr;
};

void CreateList(node *head, node *n1, node *n2, node *n3);
void Push(node *head, node *newnode);
void PrintList(node *head, node *n);

//Main function. Things to improve on: Able to shift initialization of node variables
//(e.g. zero, first, second, third) into the functions? So as to make main function neater
int main(int argc, char const *argv[]) {
    
    //Initalize head + three nodes that all point to NULL at first
    node *head = NULL;
    node *first = NULL; 
    node *second = NULL;
    node *third = NULL;

    //Allocate memory of size NODE to these nodes
    head = new node;
    first = new node;
    second = new node;
    third = new node;

    //Pass the nodes into a CreateList function as pointers, to link them together into a list
    CreateList(head, first, second, third);

    //We only need to access the head to access the rest of the nodes (by traversing the list)
    PrintList(head, head);

    //Now we add a new node called "zero" to the start of the list, and mark it as the new start.
    node *zero = NULL; //First, initalize the new node and allocate it the required memory
    zero = new node;

    Push (head, zero); //Next, assign this node to the start of the list using the Push function
    PrintList(head, head); //Finally, reprint the updated list

    return 0;
}

//Links the three nodes together in a list. Note the nodes as passed as pointers, not pass by value
void CreateList(node *head, node *n1, node *n2, node *n3){

    //Assign -1 to head node (to mark it as head), link it to first node
    head->data = -1;
    head->ptr = n1; //Head node now points to first node, which is currently pointing to NULL
    
    //Assign data to first node, and then link it to the second node
    cout <<"Enter 1st node value:";
    cin >> n1->data;
    n1->ptr = n2;

    //Assign data to second node and link it to third node
    cout <<"Enter 2nd node value:";
    cin >> n2->data;
    n2->ptr = n3;

    //Assign data to third node and point it to NULL
    cout <<"Enter 3rd node value:";
    cin >> n3->data;
    n3->ptr = NULL;

}

//Place a new node at the start of the list. The process is as follows:
// (1) Point the new node to the original first node in the list
// (2) Point the head to the new node, thus marking the new node as the start
void Push (node *head, node *newnode){

    //Add in the data for the new node
    cout << "Now add a value at the front of the list: ";
    cin >> newnode->data;

    //Assign the new node to point to the original first node in the list (which is pointed to by the head node pointer)
    newnode->ptr = head->ptr;

    head->ptr = newnode; //Then assign the head to point to the new node(thus marking the new node as the start)

}

//Traverse the linked list to print out its values, as well as mark where the head is
//In this function, head will keep pointing to the head node, while n will traverse the list
void PrintList(node *head, node *n){

    int counter = 1;
    n = n->ptr; //n is pointing to head node, so move it up to the next (first) node.

    while (n != NULL){
        cout << "Node " << counter << " contains " << n->data << "\n";
        n = n->ptr;
        counter++;
    }
    cout << "The first node contains " << head->ptr->data << "\n";
}