#include <bits/stdc++.h>
using namespace std;

// here, frequency is stored as negative to exploit sorting properties of pair

class SubTaskA{
    private:
        int N;
        map<int, int>numbers; //First int stores number, second int stores negative of number frequency
        set<pair<int, int>>numberoutput; //Resulting output: First int is negative number freq while second int is actual number

    public:
        
        void inputnumbers(){
            cin >> N;
            int input;
            for (int i = 0; i < N; ++i){
                cin >> input;
                if (numbers.find(input) == numbers.end()){
                    numbers[input] = -1; //If number not found, enter it with frequency 1
                }
                else{
                    numbers[input] -= 1; //Otherwise "increment" frequency by 1
                }
            }
        }

        //Transfer data from numbers map to numberoutput set
        void transfer_to_output(){
            
            for (auto it = numbers.begin(); it != numbers.end(); ++it){
                auto temp = make_pair(it->second, it->first); //Note: Swap freq and number around
                numberoutput.insert(temp);
            }
        }

        void output_result(){
            
            for (auto it = numberoutput.begin(); it != numberoutput.end(); ++it){
                cout << (-1)*it->first << " " << it->second << endl;
            }
        }
};

int main(){
    SubTaskA BellCurveGodA;
    BellCurveGodA.inputnumbers();
    BellCurveGodA.transfer_to_output();
    BellCurveGodA.output_result();
    return 0;
}