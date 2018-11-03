#include <bits/stdc++.h>
using namespace std;

class Practice1{
    private:
        int N, Q;
        map<int, int>array;

        void insertnumber(int num){
            auto it = array.find(num);
            if (it == array.end()){
                array.insert(pair<int, int>(num, 1));
            }
            else {
                it->second += 1;
            }
        }
        
        void handlequery(int V){
            if (V > 0){
                insertnumber(V);
            }
            else if (V < 0){
                int V2 = (-1)*V;
                auto it2 = array.find(V2);
                if (it2 == array.end()){
                    //Do nothing
                }
                else if (it2->second > 1){
                    it2->second -= 1;
                }
                else {
                    array.erase(it2);
                }
            }
            else {
                auto lowest = array.begin();
                auto highest = array.end();
                --highest;
                int difference = highest->first - lowest->first;
                cout << difference << endl;
            }
        }
    
    public:
        
        void fillarray(){
            cin >> N;
            int input;
            for (int i = 0; i < N; ++i){
                cin >> input;
                insertnumber(input);
            }
        }

        void inputqueries(){
            cin >> Q;
            int V;
            for (int i = 0; i < Q; ++i){
                cin >> V;
                handlequery(V);
            }
        }

};

int main(int argc, char const *argv[])
{
    Practice1 FailPE;
    FailPE.fillarray();
    FailPE.inputqueries();
    return 0;
}