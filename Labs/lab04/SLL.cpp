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
  int len;

public:
  SSL() {
    head = NULL;
    len = 0;
  }

  struct node* createNode(V val){
      node* cur = new node();
      cur->data = val;
      cur->next == NULL;
      return cur;
  }

  void insertFirst(V v){
      len++;
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
    len--;

    delete preHead;
  }

  void reverseList(){
      // no change if list has zero or one element
      if(head == NULL || head->next == NULL)
          return;

      node* cur = head->next;
      head->next = NULL;
      while(cur != NULL){
          node* temp = cur->next;
          cur->next = head;
          head = cur;
          cur = temp;
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
    if (pos == 0) {
      insertFirst(v);
      return;
    }

    if (pos < 0 || pos > len) {
      return;
    }

    len++;

    node* cur = createNode(v);
    node* pre = head;
    while (--pos) {
      pre = pre->next;
    }

    cur->next = pre->next;
    pre->next = cur;
  }

  int findElement(V x) {
    int pos = 0;
    node* cur = head;
    while (cur) {
      if (cur->data == x) {
        return pos;
      }
      pos++;
      cur = cur->next;
    }

    return -1;
  }

  int length() {
    return len;
  }
};


int main()
{
  SSL<int> l;
  l.insertFirst(10);
  l.insertFirst(20);
  l.insertFirst(30);
  l.insertFirst(40);
  l.insertFirst(50);
  l.insertFirst(5);

  l.printList();
  cout << l.length() << endl;

  l.removeFirst();
  l.printList();
  cout << l.length() << endl;

  l.reverseList();
  l.printList();

  cout << l.findElement(10) << endl;
  cout << l.findElement(50) << endl;
  cout << l.findElement(8) << endl;

  l.insertAtIndex(60, 5);
  l.insertAtIndex(35, 3);
  l.insertAtIndex(25, 2);

  l.printList();

  return 0;
}
