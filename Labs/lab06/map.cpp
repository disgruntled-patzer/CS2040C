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
        // add to unordered map
        if (mapper.count(words[i]) == 1){
            mapper[words[i]] += 1;
        }
        else{
            mapper[words[i]] = 1;
        }

        // add to set
        if (st.count(words[i]) == 0){
            st.insert(words[i]);
        }

    }
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

    // erase 1 key from set or map
    mapper.erase("job");
    st.erase("job");

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
