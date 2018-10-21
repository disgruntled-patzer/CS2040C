/*In this task, cmd <= 1,000,000 while roster size <= 200,000.
However, no update_dilation, and give_birth always takes in the patient with highest dilation*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

#define ARRIVE_AT_HOSPITAL 0
#define UPDATE_DIL 1
#define GIVE_BIRTH 2
#define QUERY 3

typedef tuple<int, int, string> patient; //Data of patient: 0 = dilation, 1 = arrival sequence, 2 = name

class Hospital{
    
    private:
        int cmd, arrival; //cmd = number of commands, arrival = arrival sequence (less negative number = arrive 1st)
        priority_queue<patient> roster; //Stores roster of patients and orders them according to priority
        //Priority: Higher dilation number. If dilation is same, then the patient with less negative arrival number has higher priority
        vector <string> output; //List of names to be output
        
        //How is bool(operator)const handled in priority queue? Need to ask Ranald / Jun An
        /*bool operator() (const patient& a, const patient& b) const {
            if (get<0>(a) > get<0>(b)){
                return true;
            }
            else if (get<0>(a) == get<0>(b)){
                if (get<1>(a) <= get<1>(b)){
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }*/
    public:
        //Constructor to intialize arrival sequence and get number of commands
        Hospital(){
            arrival = 0;
            cin >> cmd;
        }

        //Add a new patient with her dilation number and arrival sequence
        void arrive_at_hospital(string WomanName, int dilation){;
            roster.push(make_tuple(dilation, arrival, WomanName));
            //cout << get<2>(roster.top()) << endl; //Debug statement
            --arrival; //Update arrival counter to prepare for next patient's arrival
            /*Note the difference from Subtask A: Here, earlier arrival is marked by
            a less negative number. This is to exploit the sorting properties of tuple without
            having to write custom comparator. Also note that arrival sequence will always be
            distinct, so no need to worry about accidental sorting based on name*/
        }

        //Update a patient's dilation number (Dilation can only increase, not decrease): Not required for SubTask B
        /*void update_dil(string WomanName, int increaseDilation){
            //
        }*/

        //Search for the patient that has given birth and remove her from the list
        //Note for Subtask B, the patient with highest priority is ALWAYS the one that has given birth
        void give_birth(){
            roster.pop();
        }

        string query(){
            
            string WomanName;

            if (roster.empty()){ //Edge case: If no patients
                WomanName = "The delivery suite is empty";
                return WomanName;
            }
            else {
                WomanName = get<2>(roster.top()); //Top priority patient is already at top of roster
            }
            return WomanName;
        }

        void input_commands(){

            int current_cmd, dil;
            string patient;
            for (int i = 0; i < cmd; ++i){
                cin >> current_cmd;
                cin.get(); //To prevent space or newline from messing with subsequent character operations
                switch (current_cmd){
                    case ARRIVE_AT_HOSPITAL:
                        cin >> patient >> dil;
                        cin.get();
                        arrive_at_hospital(patient, dil);
                        break;
                    case UPDATE_DIL:
                        /*cin >> patient >> dil;
                        update_dil(patient, dil);*/
                        break;
                    case GIVE_BIRTH:
                        cin >> patient;
                        give_birth(); //Conditions of Subtask B: Get patient with highest priority
                        break;
                    case QUERY:
                        patient = query();
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
