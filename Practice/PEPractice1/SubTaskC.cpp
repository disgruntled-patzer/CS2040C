#include <bits/stdc++.h>
using namespace std;

#define MAX_INT 100000000000
#define MIN_INT 0

//1st int refers to actual element, 2nd int refers to number of times the element appears in the map
typedef map<long long, int> T; 

class Practice2{
    private:
        T array; //Required array of elements implemented as BST
        
        void insertnumber(long long num){
            auto it = array.find(num);
            if (it == array.end()){ //If number is not in array, insert it
                array.insert(pair<long long, int>(num, 1)); //Note frequency starts at 1 upon insertion
            }
            else { //If number already in array, then update its frequency
                it->second += 1;
            }
        }
        
        void handlequery(long long V){
            if (V < 0){
                insertnumber((-1)*V);
            }
            else if (V > 0){
                auto it = array.upper_bound(V); //Find element that is STRICLY larger than V
                long long next = it->first;
                --it; //Find element which is smaller than or equal to V
                if (it->first == V){
                    --it; //If current element is equal to V, decrement it further
                } //Since we want eleent that is STRICTLY smaller than V
                long long prev = it->first;
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
            array.insert(pair<long long, int>(MIN_INT, 1));
            array.insert(pair<long long, int>(MAX_INT, 1));
            long long input;
            while (cin >> input){
                insertnumber(input);
                if (cin.get() == '\n'){
                    break;
                }
            }
        }

        void inputqueries(){
            long long x;
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
    ios_base::sync_with_stdio(false); //Tells cin and scanf not to update each other
	cin.tie(0); //Tells cin and cout not to update each other
    
    Practice2 FailPE;
    FailPE.fillarray();
    FailPE.inputqueries();
    return 0;
}