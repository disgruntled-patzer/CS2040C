//Ordered set and map, sorts the elemnets in increasing order by default (unlike unordered set or map)
#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

int main()
{
    string words[10] = {"job", "vacancy", "singapore", "student", "job", "job", "vacancy", "university", "play", "job"};
    map<string, int> mapper;
    set<string> st;
    for (int i=0;i<10;i++){
        // add to map
        if (mapper.count(words[i]) == 1){ //If the key exists inside the map
            mapper[words[i]] += 1;
        }
        else{
            mapper[words[i]] = 1;
        }

        // add to set
        if (st.count(words[i]) == 0){ //Check whether element exists inside the set
            st.insert(words[i]); //Note: Actually don't need to check whether elements exists
        } //Because set does not allow duplicates, it will automatically not add elements that already exist

    }
    // print from ordered map (note: map is sorted from smallest to largest value, unless comparator function is modified)
    for (const auto& itr : mapper){
        cout << itr.first << '\t' << itr.second << '\n';
    }

    cout << "\n\n";

    // print from ordered set
    for (const auto& itr : st){
        cout << itr << '\n';
    }
    cout << "\n\n";

    // erase 1 key from set or map
    mapper.erase("job");
    st.erase("job"); //Note: Just need the key to access the set or map, no need to know any index

    // print from ordered map
    for (const auto& itr : mapper){
        cout << itr.first << '\t' << itr.second << '\n';
    }

    cout << "\n\n";

    // print from ordered set
    for (const auto& itr : st){
        cout << itr << '\n';
    }
    cout << "\n\n";
    return 0;
}
