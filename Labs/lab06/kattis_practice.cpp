//Solution for Kattis CD Problem, Lab Session 6
//This is the two-pointer method
#include<bits/stdc++.h>
using namespace std;

class kattis {
	private:
		vector <int> JACK, JILL; //To store the CDs of jack and jill
		int jacksize, jillsize; //Number of CDs each person has
        int jack_it, jill_it; //Iterators
        int input; //User input when filling vectors
        int output; //The final answer that will be returned

	public:
		void input_commands(){
			
			while ((cin >> jacksize >> jillsize), (jacksize || jillsize)){ //Fill the number of CDs each person has

                if (jacksize == 0 && jillsize == 0){
                    break; //If receive instruction to terminate input
                }

                //Reset all variables from previous test case
                JACK.clear();
                JILL.clear();
                jack_it = 0, jill_it = 0, output = 0;

				//Fill the vectors with their values
				for (int i = 0; i < jacksize; ++i){
					cin >> input;
					JACK.push_back(input);
				}
				for (int j = 0; j < jillsize; ++j){
					cin >> input;
					JILL.push_back(input);
				}

				//Next step is to traverse both vectors with the two pointers to find common CDs
				while (jack_it < jacksize && jill_it < jillsize){
					if (JACK[jack_it] == JILL[jill_it]){
						++output;
						++jack_it;
						++jill_it;
					}
					else if (JACK[jack_it] < JILL[jill_it]){
						++jack_it;
					}
					else {
						++jill_it;
					}
				}

				cout << output << endl; //Output answer

			}//End of while loop

		}
};

int main(int argc, char const *argv[])
{
	kattis Lab06;
	Lab06.input_commands();

	return 0;
}
