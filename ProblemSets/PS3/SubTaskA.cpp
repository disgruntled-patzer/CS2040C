#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

#define ARRIVE_AT_HOSPITAL 0
#define UPDATE_DIL 1
#define GIVE_BIRTH 2
#define QUERY 3

class Hospital{
    private:
        int cmd, arrival; //cmd = number of commands, arrival = arrival sequence (lower number = arrive 1st)
        vector<tuple<int, int, string>> roster; //Stores roster of patients: 0 = dilation number, 1 = arrival sequence, 2 = name
        vector <string> output; //List of names to be output

    public:
        //Constructor to intialize arrival sequence and get number of commands
        Hospital(){
            arrival = 0;
            cin >> cmd;
        }

        //Add a new patient with her dilation number and arrival sequence
        void arrive_at_hospital(string WomanName, int dilation){
            //cout << WomanName << dilation << endl;
            roster.push_back(make_tuple(dilation, arrival, WomanName));
            ++arrival; //Update arrival counter to prepare for next patient's arrival
        }

        //Update a patient's dilation number (Dilation can only increase, not decrease)
        void update_dil(string WomanName, int increaseDilation){
            int j;
            for (j = 0; WomanName != get<2>(roster[j]); ++j){
            } //Iterate until patient's name (in get<2>(roster[j])) is found
            get<0>(roster[j]) += increaseDilation; //Update dilaton (in get<0>)
        }

        //Search for the patient that has given birth and remove her from the list
        void give_birth(string WomanName){
            vector<tuple<int, int, string>>::iterator j; //Need to use iterator here for erase function
            for (j = roster.begin(); WomanName != get<2>(*j); ++j){
            } //Iterate until patient's name (in get<2>(j)) is found
            roster.erase(j);
        }

        string query(){
            string WomanName;

            if (roster.empty()){ //Edge case: If no patients
                WomanName = "The delivery suite is empty";
                return WomanName;
            }

            //Initialize iterator and output variables to the 0th entry in the roster
            int maxdil = get<0>(roster[0]); //Stores max dilation of patients
            int first_arrival = get<1>(roster[0]); //Determines which patient arrived first if maxdil is same
            WomanName = get<2>(roster[0]);

            //Perform iteration through roster to find earliest arrival of the largest dilation
            vector<tuple<int, int, string>>::iterator j = roster.begin();
            ++j; //Start j at 1st entry, since maxdil and first_arrival are initalized to 0th entry
            while (j != roster.end()){
                if (get<0>(*j) > maxdil){ //If a bigger dilation number is found
                    maxdil = get<0>(*j);
                    first_arrival = get<1>(*j);
                    WomanName = get<2>(*j);
                }
                else if (get<0>(*j) == maxdil){ //If dilation number matches
                    if (get<1>(*j) < first_arrival){ //Then use arrival sequence as tiebreak
                        maxdil = get<0>(*j);
                        first_arrival = get<1>(*j);
                        WomanName = get<2>(*j);
                    }
                }
                else {
                    //Do nothing and continue to next iteration
                }
                ++j;
            }
            return WomanName;
        }

        void input_commands(){

            //These variables handle user input commands
            int current_cmd, dil; //Current cmd = user input command, dil = user input dilation
            string patient; //patient = user input name

            //Continually read input commands and process them accordingly
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
                        cin >> patient >> dil;
                        update_dil(patient, dil);
                        break;
                    case GIVE_BIRTH:
                        cin >> patient;
                        give_birth(patient);
                        break;
                    case QUERY:
                        patient = query();
                        output.push_back(patient);
                        break;
                }
            }
        }

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
