/*In this task, cmd <= 1,000,000 while roster size <= 200,000.
Update_Dilation is included, and Give_Birth doesn't have to target patient with highest dilation
In the solution, the ARRIVE_AT_HOSPITAL function is absorbed into the Hospital::input_commands switch-case statement
As for the other three functions, they have been shifted from the Hospital class into the Patientheap class*/
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <tuple>
#include <unordered_map>
using namespace std;

//For switch-case stateents in Hospital::input_commands()
#define ARRIVE_AT_HOSPITAL 0
#define UPDATE_DIL 1
#define GIVE_BIRTH 2
#define QUERY 3

//Patient data: 0 = dilation, 1 = arrival sequence, 2 = name, 3 = Whether entry has been deleted
#define Dil_Num 0
#define Arriv_Seq 1
#define Name 2
#define Deleted 3
typedef tuple<int, int, string, bool> patient;

//Priority Queue (PQ) specially designed to store patient tuples (see typedef above)
//Also designed to manipulate them in accordance to the commands by the Hospital class
class patientheap {

    private:
        vector<patient> tree; //Here is where the Binary Max Heap / PQ is implemented
        int size = 0; //Number of elements in tree, with 1st item starting from size 1
        unordered_map<string, int> find; //Hash table for quick access to the PQ using patient's name
        //string contains patient name int contains the key which to access the PQ

    public:

        /******************************************************************/
        /*The following set of functions cater specially to this Problem Set
        They are not general functions for a Binary Max Heap / PQ, but added here
        to give the Hospital class access to the "find" hash table and the "tree" PQ*/

        //When two patients are swapped, their indexes must be updated in the "find" hash table
        void update_findpatient_index(string patientname, int index){
            find[patientname] = index;
        }

        //To mark a patient that has given birth
        void mark_as_deleted(string patientname){
            get<Deleted> (tree [ find[patientname] ] ) = true;
            //cout << patientname << " " << get<Deleted>(tree[find[patientname]]) << " is marked as deleted" << endl;
            //That was a debugging statement o.o
        }

        //Increase the dilation number of a patient
        void update_dilation(string patientname, int add){
            get<Dil_Num> (tree [find[patientname] ] ) += add;
            bubbleup(find[patientname]); //Place the updated node into its correct position in the PQ
            bubbledown(find[patientname]);
        }

        //Query what is the top priority patient
        //Notice all those commented out cout statements... they were for debugging purposes
        string query(){
            
            string patientname;

            if (empty()){ //Edge case: If no patients
                patientname = "The delivery suite is empty";
                return patientname;
            }
            else {
                //cout << get<Name>(top()) << " " << get<Deleted>(top()) << " is shown" << endl;
                while (get<Deleted> (top()) == true){
                    //cout << "Removed " << get<Name>(top()) << endl;
                    pop(); //If the patients at the top of the PQ were already marked as deleted, delete them
                    if (empty()){ //Edge case: If all nodes are marked as deleted, then it is as good as having no patients
                        patientname = "The delivery suite is empty";
                        return patientname;
                    }
                }
                patientname = get<Name>(top()); //What is left over is the top priority patient that hasn't been "deleted"
            }
            //cout << "Revealed " << patientname << endl;
            return patientname;
        }

        /*End of Problem-Set Specific Functions. The rest are general PQ functions
        Exceptions are when update_findpatient_index and unordered_set erase functions
        are called when inserting/swapping/shifting nodes*/
        /******************************************************************/

        //Get the parent position of any node at position "pos"
        int getparent(int pos){
            return floor((pos - 1) / 2);
        }

        //Get the left child position of any node at position "pos"
        int getleftchild(int pos){
            return 2*pos + 1;
        }

        //Get the right child position of any node at position "pos"
        int getrightchild(int pos){
            return 2*pos + 2;
        }

        //Swap nodes a and b
        void swap(int a, int b){

            //The following two functions update the name-to-index key in the "findpatient" hash table
            update_findpatient_index(get<Name>(tree[a]), b);
            update_findpatient_index(get<Name>(tree[b]), a);

            patient temp; //swap
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
        void bubbledown(int pos){

            int child = getleftchild(pos); //Start with left child first
            
            if (child < size){ //If left child exists (if not, then the base case has been reached)
                int rightchild = getrightchild(pos);
                //If right child exists and it is larger than the left child
                if (rightchild < size && tree[rightchild] > tree[child]){
                    child = rightchild; //Always take the larger child
                }
                if (tree[pos] < tree[child]) { //Compare parent and child and swap if necessary
                    swap(pos, child);
                    bubbledown(child); //Then go to the new child position and continue bubbling down
                }
            } //If max heap property satisfied, do nothing
        }

        //Insert a new node
        void push(patient data){
            
            tree.push_back(data); //Insert at the leaf position
            ++size;
            update_findpatient_index(get<Name>(data),size - 1); //Update the "find" hash table on the new node's index
            bubbleup(size - 1); //Then bubble up until max heap property is satisfied
        } //Note (size - 1) because vectors start from zero

        //Delete the largest node (at the root)
        void pop(){
            //find.erase( get<Name>(tree[0]) ); //Remove the node from the "find" hash table
            tree[0] = tree[--size]; //Take the leaf at the end of the vector and put it at the root (and decrease size)
            update_findpatient_index(get<Name>(tree[0]), 0); //Since a shift of nodes occured, have to update "find" hash table accordingly
            tree.pop_back(); //Delete the leaf that was moved
            bubbledown(0); //Then bubble down the new "root" until max heap property is satisfied
        }

        //Access the largest node (at the root)
        patient top(){
            return tree[0];
        }

        //Check whether PQ is empty
        bool empty(){
            if (tree.empty()){
                return true;
            }
            else {
                return false;
            }
        }

};

//Hospital class to handle input and output
class Hospital{
    
    private:
        int cmd, arrival; //cmd = number of commands, arrival = arrival sequence
        /*Note the difference from Subtask A: Here, earlier arrival is marked by
        a LESS NEGATIVE NUMBER. This is to exploit the sorting properties of tuple without
        having to write custom comparator. Also note that arrival sequence will always be
        distinct, so no need to worry about accidental sorting based on name*/

        patientheap roster; //Stores roster of patients and orders them according to priority
        //Priority: Higher dilation number. If dilation is same, then the patient with LESS NEGATIVE ARRIVAL has higher priority
        
        vector<string> output; //List of names to be output

    public:
        //Constructor to intialize arrival sequence and get number of commands
        Hospital(){
            arrival = 0;
            cin >> cmd;
        }

        void input_commands(){

            int current_cmd, dil; //current_cmd = current command, dil = input dilation number
            string patient; //Input patient name
            for (int i = 0; i < cmd; ++i){
                cin >> current_cmd;
                cin.get(); //To prevent space or newline from messing with subsequent character operations
                switch (current_cmd){
                    case ARRIVE_AT_HOSPITAL:
                        cin >> patient >> dil;
                        cin.get();
                        roster.push(make_tuple(dil, arrival, patient, false)); //Note "false": Patient hasn't been deleted :O
                        --arrival; //Update arrival counter for next patient
                        break;
                    case UPDATE_DIL:
                        cin >> patient >> dil;
                        roster.update_dilation(patient, dil);
                        break;
                    case GIVE_BIRTH:
                        cin >> patient;
                        roster.mark_as_deleted(patient);
                        break;
                    case QUERY:
                        patient = roster.query();
                        output.push_back(patient);
                        break;
                }
            }
        }

        //Print the desired output
        void print_output(){

            vector<string>::iterator it;
            for (it = output.begin(); it != output.end(); ++it){
                cout << *it << endl;
            }
        }
};

int main(int argc, char const *argv[])
{
    Hospital PS3;

    PS3.input_commands();
    PS3.print_output();
    
    return 0;
}
