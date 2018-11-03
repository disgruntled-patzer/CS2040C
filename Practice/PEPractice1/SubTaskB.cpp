#include <bits/stdc++.h>
using namespace std;

#define MAX_INT 1000000
#define MIN_INT 0

//1st int refers to actual element, 2nd int refers to number of times the element appears in the map
typedef map<int, int> T; 

class Practice2{
    private:
        T array; //Required array of elements implemented as BST

        //Find successor of an element V using upper_bound
        //Note upper_bound always returns nearest element that is STRICTLY higher than V
        int findsuccessor(int V){
            T::iterator it = array.upper_bound(V);
            return it->first;
        }

        int findpredecessor(int V){
            T::iterator it = array.lower_bound(V);
            while (it->first >= V){ //Get nearest element that is STRICTLY lower than V
                --it;
            }
            return it->first;
        }
        
        void insertnumber(int num){
            auto it = array.find(num);
            if (it == array.end()){ //If number is not in array, insert it
                array.insert(pair<int, int>(num, 1)); //Note frequency starts at 1 upon insertion
            }
            else { //If number already in array, then update its frequency
                it->second += 1;
            }
        }
        
        void handlequery(int V){
            if (V < 0){
                insertnumber((-1)*V);
            }
            else if (V > 0){
                auto next = findsuccessor(V);
                auto prev = findpredecessor(V);
                //cout << next << " " << prev << " "; //Debugging
                cout << next - prev << endl;
            }
            else {
                //Do nothing
            }
        }
    
    public:
        
        void fillarray(){
            //Insert MAX and MIN INT to avoid handling edge cases later on
            array.insert(pair<int, int>(MIN_INT, 1));
            array.insert(pair<int, int>(MAX_INT, 1));
            int input;
            while (cin >> input){
                insertnumber(input);
                if (cin.get() == '\n'){
                    break;
                }
            }
        }

        void inputqueries(){
            int x;
            while (cin >> x){
                handlequery(x);
                if (cin.get() == '\n'){
                    break;
                }
            }
        }

};

int main(int argc, char const *argv[])
{
    Practice2 FailPE;
    FailPE.fillarray();
    FailPE.inputqueries();
    return 0;
}