/*Adopted the sample AVL demo from Mooshak and converted it into a string AVL Tree
This code gives loads of errors but I just submit first to let the TAs see my 
AVL implementation*/

// write your matric number here: A0164850E
// write your name here: Lau Yan Han
// write list of collaborators here: Pretty much anyone who was discussing in the CS2040C telegram group
// year 2018/19 Sem1 hash code: IEXVAR3BOJ4VIYLO (do NOT delete this line)

#include <bits/stdc++.h>
using namespace std;

#define male 1
#define female 2

struct node { //AVL Tree node
	node* parent;
	node* left;
	node* right;
	string data;
	int height;
	int size;
};

class AVLTree {
	private:
		node *root;

		int h(node* T){ //Return height of a node
			if (T == NULL){
				return -1;
			}
			else {
				return T->height;
			}
		}

		int getsize(node* T){
			if (T == NULL){
				return 0;
			}
			else {
				return T->size;
			}
		}

		node* insert(node* T, string v) {
			if (T == NULL) { //Insertion point is found
				T = new node;
				T->data = v;
				T->parent = T->left = T->right = NULL; //Parent relationships are not initialized yet
				T->height = 0;
				T->size = 1;
			}
			else if (T->data < v) { //If v is larger than T, then search the right
				T->right = insert(T->right, v);
				T->right->parent = T; //Parent relationships are initialized after insertion
			}
			else { //If v smaller than T, then search the left
				T->left = insert(T->left, v);
				T->left->parent = T;
			}

			/*Checking balance: +ve means left has more nodes, -ve means right has more nodes
			  Magnitude greater than 2 means a rotation is needed*/
			int balance = h(T->left) - h(T->right);
			if (balance == 2) { //left too many nodes, need to rotate right
				int balance2 = h(T->left->left) - h(T->left->right);
				if (balance2 == 1) { //If the "offending" branch is on the "outside"
					T = rotateRight(T); //Then just rotate right once
				}
				else { //If the "offending" branch is on the "inside"
					T->left = rotateLeft(T->left); //Then rotate inner node left to bring "offending" branch "outside"
					T = rotateRight(T); //Before rotating main node to the right
				}
			}
			else if (balance == -2) { //right too many nodes, need to rotate left
				int balance2 = h(T->right->left) - h(T->right->right);
				if (balance2 == -1) //Mechanism is the opposite case of balance = -2 case
					T = rotateLeft(T);
				else { // 1
					T->right = rotateRight(T->right);
					T = rotateLeft(T);
				}
			}

			T->height = max(h(T->left), h(T->right)) + 1;
			T->size = getsize(T->left) + getsize(T->right) + 1;
			return T; //return the updated AVL
		}

		node* erase(node* T, string v) {
			if (T == NULL){ //Edge Case: v is not found
				return T;
			}

			if (T->data == v) { //Found node that should be deleted
				if (T->left == NULL && T->right == NULL) //Case 1: Node has no children, can just delete
					T = NULL;
				else if (T->left == NULL && T->right != NULL) { //Case 2: Node has only one right child
					node* temp = T;
					T->right->parent = T->parent; //Link T's parent directly to T's child
					T = T->right; //bypass T
					temp = NULL;
				}
				else if (T->left != NULL && T->right == NULL) { //Case 3: Node has only one left child
					node* temp = T;
					T->left->parent = T->parent;
					T = T->left;
					temp = NULL;
				}
				else { //Case 4: Node has two children. Find the successor of the node
					string successorV = (successor(v))->data;
					T->data = successorV; //Then replace current node with the successor
					T->right = erase(T->right, successorV); //And delete the original position of the successor
				}
			}
			else if (T->data < v)
				T->right = erase(T->right, v);
			else
				T->left = erase(T->left, v);

			/*The following code checks for the balance conditions. It is same as the balance
			  checking for insert function, except the first line (check balance only if T != NULL*/
			if (T != NULL) {
				int balance = h(T->left) - h(T->right);
				if (balance == 2) {
					int balance2 = h(T->left->left) - h(T->left->right);
					if (balance2 == 1) {
						T = rotateRight(T);
					}
					else { // -1
						T->left = rotateLeft(T->left);
						T = rotateRight(T);
					}
				}
				else if (balance == -2) {
					int balance2 = h(T->right->left) - h(T->right->right);
					if (balance2 == -1)
						T = rotateLeft(T);
					else {
						T->right = rotateRight(T->right);
						T = rotateLeft(T);
					}
				}

				T->height = max(h(T->left), h(T->right)) + 1;
				T->size = getsize(T->left) + getsize(T->right) + 1;
			}

			return T; //Return the updated AVL
		}

		node* findMin(node* T) {
			if (T == NULL || T->left == NULL){
				return T; //Return NULL if not found, return pointer to element if found
			}
			else{
				return findMin(T->left); //Keep going left until minimum found
			}
		}

		node* findMax(node* T) {
			if (T == NULL || T->right == NULL){
				return T;
			}
			else{
				return findMax(T->right);
			}
		}

		node* rotateLeft(node* T) {
			node* temp = T->right; //Do all the fancy pointer rotations here
			temp->parent = T->parent;
			T->parent = temp;
			T->right = temp->left;
			if (temp->left != NULL) temp->left->parent = T;
			temp->left = T;
			//Then update the heights and sizes of the affected nodes
			T->height = max(h(T->left), h(T->right)) + 1;
			T->size = getsize(T->left) + getsize(T->right) + 1;
			temp->height = max(h(temp->left), h(temp->right)) + 1;
			temp->size = getsize(temp->left) + getsize(temp->right) + 1;

			return temp;
		}

		node* rotateRight(node* T) {
			node* temp = T->left; //Algorithm is almost the same as rotateleft
			temp->parent = T->parent;
			T->parent = temp;
			T->left = temp->right;
			if (temp->right != NULL) temp->right->parent = T;
			temp->right = T;

			T->height = max(h(T->left), h(T->right)) + 1;
			T->size = getsize(T->left) + getsize(T->right) + 1;
			temp->height = max(h(temp->left), h(temp->right)) + 1;
			temp->size = getsize(temp->left) + getsize(temp->right) + 1;

			return temp;
		}

		node* find(node* T, string v){
			if (T == NULL || T->data == v){ //Return NULL if not found, return pointer to element if found
				return T;
			} //If still searching, search to the right if T < v; search to the left if T > v
			else if (T->data < v){
				return find(T->right, v);
			}
			else{
				return find(T->left, v);
			}
		}

		//Return first entry that is NOT smaller than v
		node* lower_bound(node* T, string v){
			if (T == NULL){
				return T;
			}
			if (T->data < v){ //If less, then keep going up till T is no longer smaller than v
				while (T->data < v){
					T = successor(T);
					if (T == NULL){
						return T; //Edge case: All elements smaller than T, then no lower bound exists
					}
				}
			}
			else{ //If greater or equal, then keep going down till T is no longer equals or larger than v
				while (T->data >= v){
					auto temp = predecessor(T);
					if (temp == NULL || temp->data < v){
						return T; //If predecessor doesn't exist or is already smaller than v
					} //Then T is already the first entry that is not smaller than v
					T = temp;
				}
			}
			return T;
		}

		//Returns first entry that is larger than v. Algorithm is almost the same as lower_bound
		node* upper_bound(node* T, string v){
			if (T == NULL){
				return T;
			}
			if (T->data <= v){
				while (T->data <= v){
					T = successor(T);
				}
				if (T == NULL){
					return T;
				}
			}
			else{
				while (T->data > v){
					auto temp = predecessor(T);
					if (temp == NULL || temp->data <= v){
						return T;
					}
					T = temp;
				}
			}
			return T;
		}

		node* successor(node* T) {
			if (T->right != NULL) // this subtree has right subtree
				return findMin(T->right); // the successor is the minimum of right subtree
			else { //There is no more right subtree to search, backtrack to see if successor is higher up the tree
				node* par = T->parent; //par = par(ent)
				node* cur = T; //cur = cur(rent)
				// if par is not root and cur is its right children, continue moving up
				while ((par != NULL) && (cur == par->right)) {
					cur = par;
					par = cur->parent;
				}
				return par; //This is the successor of T. It will be NULL if successor is not found
			}
		}

		node* predecessor(node* T) { //code is basically same as successor except it searches the left subtrees
			if (T->left != NULL)
				return findMax(T->left);
			else {
				node* par = T->parent;
				node* cur = T;
				while ((par != NULL) && (cur == par->left)) { 
					cur = par;
					par = cur->parent;
				}
				return par;
			}
		}

	public:
		AVLTree() {
			root = NULL;
		}

		void insert(string v) {
			root = insert(root, v);
		}

		void erase(string v) {
			root = erase(root, v);
		}

		node* find(string v) {
			node* res = find(root, v);
			return res;
		}

		node* begin(){
			return findMin(root);
		}

		node* end(){
			return findMax(root);
		}

		node* successor(string v){
			node* vPos = find(root, v);
			if (vPos == NULL){
				return vPos;
			}
			else{
				return successor(vPos);
			}
		}

		node* predecessor(string v) { 
			node* vPos = find(root, v);
			if (vPos == NULL){
				return vPos;
			}
			else{
				return predecessor(vPos);
			}
		}

		node* lower_bound(string v){
			return lower_bound(root, v);
		}

		node* upper_bound(string v){
			return upper_bound(root, v);
		}

		//Return distance between two nodes, start and end INCLUSIVE
		int distance(node* start, node* end){
			if (start == NULL && end == NULL){
				return 0;
			}

			int count = 0;
			node* temp = start;
			while (temp != end){
				++count;
				temp = successor(temp);
			}
			++count;
			return count;
		}

		int size(){
			if (root == NULL){
				return 0;
			}
			else{
				return root->size;
			}
		}

};

class PS4{
	private:

		/*List of suggestions implemented as AVLTree - male and female
		  It is implemented as an array of sets, with each array entry corresponding
		  to the first letter of each baby name*/
		AVLTree suggestions_male[26]; 
		AVLTree suggestions_female[26];	

		//Convert A - Z to 0 - 25 (using ASCII definitions)
		int char_to_int(char data){
			return int(data) - 65;
		}

		//Do query for male names: Called by Query Function
		int query_male(string START, string END){
			int ans = 0; //Final answer

			//Start and End prefixes to determine which entry of the array to go to
			int startprefix = char_to_int(START[0]), endprefix = char_to_int(END[0]);

			//Iterators that point to boundaries of START and END
			auto start = suggestions_male[startprefix].lower_bound(START);
			auto end = suggestions_male[endprefix].upper_bound(END);

			if (startprefix == endprefix){ //If both START and END have same first digit		
				cout << "Same Range" << endl;
				ans = distance(start, end);
			}
			else{
				cout << "Different Ranges" << endl;
				//Get distance from START to end of its set
				ans += distance(start, suggestions_male[startprefix].end());

				//For entries between start and end, get the entire set size
				for (int j = startprefix + 1; j < endprefix; ++j){
					ans += suggestions_male[j].size();
				}

				//Get distance from start of END set to END
				ans += distance(suggestions_male[endprefix].begin(), end);
			}

			/*Deal with the edge case where the entry at the
			  right boundary equals END. Then this entry cannot be counted, since right
			  boundary is open. Hence decrement ans by 1 in such a case*/
			for (int k = startprefix; k != endprefix + 1; ++k){
				if (suggestions_male[k].find(END) != NULL){
					--ans;
					break;
				}
			}

			return ans;
		}

		//Do query for female names, essentially similar to query_male, called by Query Function
		int query_female(string START, string END){
			int ans = 0;
			int startprefix = char_to_int(START[0]), endprefix = char_to_int(END[0]);
			auto start = suggestions_female[startprefix].lower_bound(START);
			auto end = suggestions_female[endprefix].upper_bound(END);
			
			if (startprefix == endprefix){		
				ans = distance(start, end);
			}
			else{
				ans += distance(start, suggestions_female[startprefix].end());
				for (int j = startprefix + 1; j < endprefix; ++j){
					ans += suggestions_female[j].size();
				}
				ans += distance(suggestions_female[endprefix].begin(), end);
			}

			for (int k = startprefix; k != endprefix + 1; ++k){
				if (suggestions_female[k].find(END) != NULL){
					--ans;
					break;
				}
			}

			return ans;
		}

	public:

		void AddSuggestion(string babyName, int genderSuitability){

			//Assign the name to its respective entry in male/female sets based on first letter of name
			int prefix = char_to_int(babyName[0]);
			switch (genderSuitability){
				case male:
					suggestions_male[prefix].insert(babyName);
					break;
				case female:
					suggestions_female[prefix].insert(babyName);
					break;
				default:
					break;
			}
		}

		void RemoveSuggestion(string babyName){

			int prefix = char_to_int(babyName[0]);
			suggestions_male[prefix].erase(babyName);
			suggestions_female[prefix].erase(babyName);
		}

		int Query(string START, string END, int gender){
			int ans = 0;

			switch (gender){
				case male:
					ans = query_male(START, END);
					break;
				case female:
					ans = query_female(START, END);
					break;
				default:
					ans = query_male(START, END) + query_female(START, END);
			}

			return ans;
		}
};

int main(int argc, char const *argv[])
{
	PS4 CS2040C;

	while(true) {
		int cmd = 0, genderSuitability;
		char babyName[32], START[32], END[32];
		scanf("%d", &cmd);
		if (cmd == 0) break;
		else if(cmd == 1){
			scanf("%s%d", babyName, &genderSuitability);
			CS2040C.AddSuggestion(string(babyName), genderSuitability);
		}
		else if(cmd == 2){
			scanf("%s", babyName);
			CS2040C.RemoveSuggestion(string(babyName));
		}
		else if(cmd == 3){
			scanf("%s%s%d", START, END, &genderSuitability);
			int ans = CS2040C.Query(string(START), string(END), genderSuitability);
			printf("%d\n", ans);
		}
	}
	return 0;
}