#include <bits/stdc++.h>
using namespace std;

class OddManOut{
    private:
        int N, G;
        unordered_set<unsigned long>guestlist;
        unordered_set<unsigned long>::iterator finder;

    public:
        void inputN(){
            cin >> N;
        }

        int input_guestcodes(){
            int result = -1, input;

            for (int i = 0; i < G; ++i){
                cin >> input;
                finder = guestlist.find(input); //Check whether input exists
                if (finder != guestlist.end()){
                    guestlist.erase(input); //If there is a corresponding entry, erase it
                }
                else{
                    guestlist.insert(input); //If no corresponding entry, insert it
                }
            }

            finder = guestlist.begin();
            result = *finder;
            guestlist.clear(); //Clear guestlist for next test case
            return result;
        }

        void scan_testcases(){
            for (int i = 1; i <= N; ++i){
                cin >> G;
                cout << "Case #" << i << ": " << input_guestcodes() << endl;
            }
        }
};

int main(int argc, char const *argv[])
{
    OddManOut CS2040C;

    CS2040C.inputN();
    CS2040C.scan_testcases();
    return 0;
}
