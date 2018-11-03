#include <bits/stdc++.h>
using namespace std;

class Practice2{
    private:
        set<string>reachable_cities;
    
    public:

        void inputdata(){
            int F;
            cin >> F;
            string origin, dest;
            for (int i = 0; i < F; ++i){
                cin >> origin >> dest;
                if (origin.compare("SINGAPORE") == 0){
                    reachable_cities.insert(dest);
                }
                else if (dest.compare("SINGAPORE") == 0){
                    reachable_cities.insert(origin);
                }
                else{
                    continue;
                }
            }
        }

        void outputresult(){
            
            for (auto it: reachable_cities){
                cout << it << endl;
            }
        }
};

int main(int argc, char const *argv[])
{
    Practice2 MugforPE;
    MugforPE.inputdata();
    MugforPE.outputresult();
    return 0;
}
