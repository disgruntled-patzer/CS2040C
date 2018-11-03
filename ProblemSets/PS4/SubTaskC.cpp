/*Adopted the sample AVL demo from Mooshak and converted it into a string AVL Tree
This code gives loads of errors but I just submit first to let the TAs see my 
AVL implementation
Ten minutes left to closing of PS4. I submit this incorrect solution without regrets,
knowing that I learnt much about AVL Trees in the process*/

// write your matric number here: A0164750E (my matric no in previous submissions were wrong)
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

		int getsize(node* T){ //Return size of a node's tree (node itself inclusive)
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

			return T;
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
			if (T == NULL || T->data == v){
				return T;
			}
			else if (T->data < v){
				if (T->right == NULL){
					return T;
				}
				return lower_bound(T->right, v);
			}
			else{ //T->data >= v
				if (T->left == NULL){
					return T;
				}
				return lower_bound(T->left, v);
			}
			return T;
		}

		//Returns first entry that is larger than v. Algorithm is almost the same as lower_bound
		node* upper_bound(node* T, string v){
			if (T == NULL){
				return T;
			}
			else if (T->data <= v){
				if (T->right == NULL){
					return NULL;
				}
				if (successor(T)->data > v){
					return successor(T);
				}
				return lower_bound(T->right, v);
			}
			else{ //T->data > v
				if (T->left == NULL){
					return T;
				}
				if (predecessor(T)->data <= v){
					return T;
				}
				return lower_bound(T->left, v);
			}
			return T;
		}

		node* successor(node* T) {
			if (T->right != NULL) // this subtree has right subtree
				return findMin(T->right); // the successor is the minimum of right subtree
			else { //There is no more right subtree to search, backtrack to search higher up
				node* par = T->parent; //par(ent)
				node* cur = T; //cur(rent)
				// if par is not root and cur is its right children, continue moving up
				while ((par != NULL) && (cur == par->right)) {
					cur = par;
					par = cur->parent;
				}
				return par; //This is the successor of T. It will be NULL if not found
			}
		}

		node* predecessor(node* T) { //Code is almost the same as successor
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

		//Returns the number of nodes that come before node T
		//Algo modified from Tutorial 8. v is assumed to exist in the tree
		//All those silly NULL checks are to catch any NULL edge cases o.o
		int rank (node* T, string v){
			if (T->data == v){
				if  (T->left == NULL){
					return 0;
				}
				return T->left->size;
			}
			else if (T->data > v){
				if (T->left == NULL){
					return 0;
				}
				return rank(T->left, v);
			}
			else {
				if (T->left == NULL && T->right == NULL){
					return 0;
				}
				else if (T->left == NULL){
					return rank(T->right, v);
				}
				else if (T->right == NULL){
					return T->left->size + 1;
				}
				else{
					return (T->left->size + 1) + rank(T->right, v);
				}
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
		//Using predecessor/successor method is too inefficient hence use rank
		//Rank assumes the searched string exists in the tree, so NULL edge cases are resolved here
		int distance(node* start, node* end){			
			if (root == NULL || start == NULL){
				return 0;
			}
			else if (start == NULL && end == NULL) {
				return 0;
			}
			else if (end == NULL){
				return root->size - rank(root, start->data);
			}
			else{
				return rank(root, end->data) - rank(root, start->data) + 1;
			}
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
		  It is implemented as an array of sets, each array entry corresponds
		  to the first letter of each name*/
		AVLTree suggestions_male[26]; 
		AVLTree suggestions_female[26];	

		//Convert A - Z to 0 - 25 (using ASCII)
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
				ans = suggestions_male[startprefix].distance(start, end);
			}
			else{
				//Get distance from START to end of its set
				ans += suggestions_male[startprefix].distance(start, suggestions_male[startprefix].end());

				//For entries between start and end, get the entire set size
				for (int j = startprefix + 1; j < endprefix; ++j){
					ans += suggestions_male[j].size();
				}

				//Get distance from start of END set to END
				ans += suggestions_male[endprefix].distance(suggestions_male[endprefix].begin(), end);
			}

			/*Deal with edge case where the entry at the right boundary greater or equals END.
			Then this entry cannot be counted, since right boundary is open. Hence decrement ans by 1*/
			for (int k = startprefix; k != endprefix + 1; ++k){
				if (suggestions_male[k].find(END) != NULL){
					--ans;
					break;
				}
			}
			if (end != NULL && end->data >= END){
				--ans;
			}

			return ans;
		}

		//Do query for female names, essentially similar to query_male
		int query_female(string START, string END){
			int ans = 0;
			int startprefix = char_to_int(START[0]), endprefix = char_to_int(END[0]);
			auto start = suggestions_female[startprefix].lower_bound(START);
			auto end = suggestions_female[endprefix].upper_bound(END);
			
			if (startprefix == endprefix){		
				ans = suggestions_female[startprefix].distance(start, end);
			}
			else{
				ans += suggestions_female[startprefix].distance(start, suggestions_female[startprefix].end());
				for (int j = startprefix + 1; j < endprefix; ++j){
					ans += suggestions_female[j].size();
				}
				ans += suggestions_female[endprefix].distance(suggestions_female[endprefix].begin(), end);
			}

			for (int k = startprefix; k != endprefix + 1; ++k){
				if (suggestions_female[k].find(END) != NULL){
					--ans;
					break;
				}
			}
			if (end != NULL && end->data >= END){
				--ans;
			}

			return ans;
		}

	public:

		void AddSuggestion(string Name, int gender){

			//Assign the name to its respective entry in male/female sets based on first letter of name
			int prefix = char_to_int(Name[0]);
			switch (gender){
				case male:
					suggestions_male[prefix].insert(Name);
					break;
				case female:
					suggestions_female[prefix].insert(Name);
					break;
				default:
					break;
			}
		}

		void RemoveSuggestion(string Name){

			int prefix = char_to_int(Name[0]);
			suggestions_male[prefix].erase(Name);
			suggestions_female[prefix].erase(Name);
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
		int cmd = 0, gender;
		char Name[32], START[32], END[32];
		scanf("%d", &cmd);
		if (cmd == 0) break;
		else if(cmd == 1){
			scanf("%s%d", Name, &gender);
			CS2040C.AddSuggestion(string(Name), gender);
		}
		else if(cmd == 2){
			scanf("%s", Name);
			CS2040C.RemoveSuggestion(string(Name));
		}
		else if(cmd == 3){
			scanf("%s%s%d", START, END, &gender);
			int ans = CS2040C.Query(string(START), string(END), gender);
			printf("%d\n", ans);
		}
	}
	return 0;
}