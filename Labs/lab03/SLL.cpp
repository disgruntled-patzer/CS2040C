//The original program included a dummy head. Here, the dummy head is not used
//Note the convention here is that the 1st entry starts at 0, not 1 (similar to array)

#include <stdio.h>
#include <iostream>
using namespace std;

template<class V>
class SSL {
  struct node{
    V data;
    struct node* next;
  };

private:
  node* head;

public:
  SSL() {
    head = NULL;
  }

  struct node* createNode(V val){
      node* cur = new node();
      cur->data = val;
      cur->next == NULL;
      return cur;
  }

  void insertFirst(V v){ //Modified: InsertFirst inserts a new node to be the HEAD
      node* cur = createNode(v);
      // if empty list, the 1st inserted node will be the head
      if (head == NULL) {
        head = cur;
        return;
      }
      cur->next = head;
      head = cur;
  }

  void removeFirst() {
    if (head == NULL) {
      return;
    }

    node* preHead = head;
    head = head->next;

    delete preHead;
  }

  void reverseList(){ //This function assumes list has dummy head
      // no change if list has zero or one element
      if(head->next == NULL or head->next->next == NULL)
          return;
      node* cur = head->next->next;
      head->next->next = NULL;
      while(cur != NULL){
          node* temp = cur;
          cur = cur->next;
          temp->next = head->next;
          head->next = temp;
      }
  }

  void printList(){
      node* cur = head;
      while(cur != NULL){
          cout << cur->data << " ";
          cur = cur->next;
      }
      cout << endl;
  }

  void insertAtIndex(V v, int pos) {
  	//Edge Case 1: Insert at head (pos = 0)
  	if (pos == 0){
  		insertFirst(v);
  	}

  	node* insert = createNode(v); //Node to be inserted
  	//Edge Case 2: List is empty and not inserting at head
  	if (head == NULL){
  		cout << "Out of Range" << endl;
  		return;
  	}
  	//Default: Insert at any position along a list with at least one element
  	node* cur = head; //Iterator that starts at head
  	for (int i = 0; i < pos - 1; i++){ //Iterate i till it reaches one step before the insertion position
  		if (cur->next == NULL && i < pos - 1){ //If end of list is reached and desired position has not yet been reached
  			cout << "Out of Range" << endl;
  			return;
  		}
  		cur = cur->next;
  	}
  	//Perform the insertion of the new node
  	insert->next = cur->next;
  	cur->next = insert;

  }

  int findElement(V x) {

  	if (head == NULL){
  		return 0;
  	}

  	int i = 0; //Iterator to mark position
  	node* cur = head;

  	while (cur != NULL){
  		if(cur->data == x){
  			return i;
  		}
  		else{
  			cur = cur->next;
  			++i;
  		}
  	}

    return 0;
  }

  int length() {

  	if (head == NULL){
  		return 0;
  	}
  	
  	int i = 0; //Iterator to mark position
  	node* cur = head;

  	while (cur != NULL){
  			cur = cur->next;
  			++i;
  		}
    return i;
  }
};


int main()
{
  SSL<int> l;
  l.insertFirst(10);
  l.printList();
  l.insertFirst(20);
  l.printList();
  l.insertFirst(30);
  l.insertFirst(40);
  l.insertFirst(50);
  l.insertFirst(5);

  l.printList();
  int i = l.length();
  cout << i << endl;

  int j = l.findElement(20);
  cout << j << endl;

  l.removeFirst();
  l.insertAtIndex(60,4);
  l.printList();

  return 0;
}
