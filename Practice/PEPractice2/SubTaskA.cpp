#include <bits/stdc++.h>
using namespace std;

typedef unordered_set<string> T;

//Custom comparator for the "sorted names" set
//Returns true if lhs should come before rhs
//Sorting criteria: lhs should come before rhs if it is (1) longer,
//(2) in case of tie, comes first in alphabetical order
struct Compare{
    bool operator()(const string &lhs, const string &rhs){
        
        if (lhs.length() == rhs.length()){
            return (lhs < rhs);
        } //If length is equal, then return true if lhs comes first in alphabetical order
        else {
            return (lhs.length() > rhs.length());
        } //Otherwise, return true if lhs has greater length
    }
};

class Practice2{
    private:
        T names, names_J; //names_J store all names that start with J, names store other non-J names
        set<string, Compare> sorted_names; //Will eventually contain list of sorted suggestions to be output

        void insert_into_list(string &input, T &list){
            if (list.find(input) == list.end()){
                list.insert(input);
            }
        }
        
        void delete_from_list(string &input, T &list){
            auto it = list.find(input);
            if (it != list.end()){
                list.erase(it);
            }
        }

        void insert_into_sorted_list(T::iterator &it1, T::iterator &it2){
            if (*it1 != *it2){
                string newname = *it1 + " " + *it2;
                sorted_names.insert(newname);
            }
        }

    public:

        void inputnames(){
            int N;
            cin >> N;
            string input;
            for (int i = 0; i < N; ++i){
                cin >> input;
                if (input[0] == 'J'){
                    insert_into_list(input, names_J);
                }
                else{
                    insert_into_list(input, names);
                }
            }
        }

        void input_undesired_names(){
            int M;
            cin >> M;
            string input;
            for (int i = 0; i < M; ++i){
                cin >> input;
                if (input[0] == 'J'){
                    delete_from_list(input, names_J);
                }
                else{
                    delete_from_list(input, names);
                }
            }
        }

        //Generate list of all names and insert them into the sorted list
        void generatelist(){
            auto it1 = names_J.begin();
            while (it1 != names_J.end()){ //Outer iterator iterates through names_J
                auto it2 = names_J.begin(); //Innter iterator iterates through both names_J and names
                while (it2 != names_J.end()){
                    insert_into_sorted_list(it1, it2);
                    ++it2;
                }
                it2 = names.begin();
                while (it2 != names.end()){
                    insert_into_sorted_list(it1, it2);
                    ++it2;
                }
                ++it1;
            }
        }

        void output_result(){
            int count = 1;
            auto it = sorted_names.begin();

            //Only output first 100 names if list is greater than 100
            while (it != sorted_names.end() && count <= 100){
                cout << *it << endl;
                ++it;
                ++count;
            }
        }

};

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    Practice2 SUthismod;
    SUthismod.inputnames();
    SUthismod.input_undesired_names();
    SUthismod.generatelist();
    SUthismod.output_result();
    return 0;
}
