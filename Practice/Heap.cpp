/*Practice Program for Binary Max Heap (priority queue)*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Heap {

    private:
        vector <int> tree; //To store binary max heap
        int size = 0; //Number of elements in tree, with 1st item starting from size 1

    public:
        
        //Constructor to receive user input and build a binary max heap automatically
        Heap(){
            int temp;
            while (cin >> temp){ //Receive user input
                tree.push_back(temp);
                ++size;
                if (cin.get() == '\n'){
                    break;
                }
            }
            heapbuild(); //Build heap
        }

        //Build binary max heap from the "unheaped" vector
        void heapbuild(){
            for (int i = (size/2) - 1; i >=0; --i){ //Start from the 1st non-leaf node and go upwards
                bubbledown(i); //Perform bubble down process for each non-leaf node
            }
        }

        //Get the parent of any node at position "pos"
        int getparent(int pos){
            return floor((pos - 1) / 2);
        }

        //Get the left child of any node at position "pos"
        int getleftchild(int pos){
            return 2*pos + 1;
        }

        //Get the right child of any node at position "pos"
        int getrightchild(int pos){
            return 2*pos + 2;
        }

        //Swap nodes a and b
        void swap(int a, int b){
            int temp;
            temp = tree[a];
            tree[a] = tree[b];
            tree[b] = temp;
        }

        //Bubble up procedure to maintain max heap property
        void bubbleup(int pos){
            while (getparent(pos) >= 0 && tree[getparent(pos)] < tree[pos]){
                swap(getparent(pos), pos);
                pos = getparent(pos);
            } //Stop bubbling up when "pos" hits the root (0) or when the parent of "pos" is larger than "pos"
        }

        //Bubble down procedure to maintain max heap property
        void bubbledown(int root){

            int child = getleftchild(root); //Start with left child first
            
            if (child < size){ //If left child exists (if not, then the base case has been reached)
                int rightchild = getrightchild(root);
                //If right child exists and it is larger than the left child
                if (rightchild < size && tree[rightchild] > tree[child]){
                    child = rightchild; //Always take the larger child
                }
                if (tree[root] < tree[child]) { //Compare parent and child and swap if necessary
                    swap(root, child);
                    bubbledown(child); //Then go to the new child position and continue bubbling down
                }
            } //If max heap property satisfied, do nothing
        }

        //Insert a new node
        void insert(int data){
            
            tree.push_back(data); //Insert at the leaf position
            ++size;
            bubbleup(size - 1); //Then bubble up until max heap property is satisfied
        } //Note (size - 1) because vectors start from zero

        //Delete the largest node (at the root) and return it as an int
        int deleteroot(){
            int rootitem = tree[0]; //Extract root
            tree[0] = tree[--size]; //Take the leaf at the end of the vector and put it at the root (and decrease size)
            tree.pop_back(); //Delete the leaf that was moved
            bubbledown(0); //Then bubble down the new "root" until max heap property is satisfied
            return rootitem;
        }

        //Print contents of the heap
        void printtree(){
            for (int i = 0; i < size; ++i){
                cout << tree[i];
            }
            cout << '\n';
        }
};

int main(int argc, char const *argv[])
{
    Heap CS2040C;

    CS2040C.printtree();
    CS2040C.insert(10);
    CS2040C.printtree();
    int extract = CS2040C.deleteroot();
    CS2040C.printtree();
    cout << extract << endl;
    
    return 0;
}
