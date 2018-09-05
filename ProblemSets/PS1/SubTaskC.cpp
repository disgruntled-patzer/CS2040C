/*Same as Task A except: 0 < TC < 1, 0 < N < 20,000,000, All integers are 1, 3 or 5*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#define NMAX 200000000

class Median {

	private:
		int TC; //Number of test cases (which is 0 or 1 in this case, so it is effectively just for show)
		int N; //Max number of integers in the array, for each test case
        vector<int> array; //Variable-Length Array used for each test case to find continuous median (only 1, 3 and 5)
		int count[3] = {0}; //Array to store the number of occurences of 1, 3 and 5 in the "array" vector above

	public:

		//Get user to input number of test cases (in this case, it is limited to 0 or 1)
		int inputTC () {
			int data;
			cin >> data;
			TC = data;
			return TC;
		}

		//Get user to input number of integers in each test case array
		void inputN () {
			int data;
			cin >> data;
			N = data;
		}

		//Get the user to input integers into the array for each test case
		void inputarray (){

			int a;

			for (int i = 0; i < N; i++){
				cin >> a;
				array.push_back(a);
			}
		}

		/*Insert new data into its sorted position. Since all data is either 1, 3 or 5, we can just count the number
		of occurences of each digit, and store them in an array called "count". In the "count" array, the 0th entry
		stores occurences of digit 1, 1st entry stores occurences of digit 3, 2nd entry stores occurences of digit 5*/
		void insert(int data){

			switch (data){
				case 1:
					count[0]++;
					break;
				case 3:
					count[1]++;
					break;
				case 5:
					count[2]++;
					break;
				default:
					break;
			}

		}

		/*Finds median of a set of integers within an array. Note that since all integers are 1, 3 or 5
		This allows us to use simple if-else statements to scan the "count" array finding the median*/
		int findmedian (int x){

			int position = x/2, median; //Position returns the location of the entry that will be stored in median

			if (x % 2 != 0){ //If number of integers is odd, then compare the middle entry (position + 1)
				if (position + 1 <= count[0]){
					median = 1;
				}
				else if (position + 1 <= count[0] + count[1]){
					median = 3;
				}
				else {
					median = 5;
				}
			}
			else { //If number of integers is even
				int median1, median2; //Because we will be taking average of two middle entries

				if (position <= count[0]){ //First, find the value of the first middle entry
					median1 = 1;
				}
				else if (position <= count[0] + count[1]){
					median1 = 3;
				}
				else {
					median1 = 5;
				}

				if (position + 1 <= count[0]){ //Then find value of second middle entry
					median2 = 1;
				}
				else if (position + 1 <= count[0] + count[1]){
					median2 = 3;
				}
				else {
					median2 = 5;
				}

				median = (median1 + median2)/2; //Calculate average of middle two integers
				median = floor (median); //And return the rounded down value
			}
			//cout << median << endl; //Debug statement

			return median;
		}

		//Main driver function to find continuous median for each test case
		void findmedians (){

			int output = 0; //Continuous median sum that will be printed

			inputN();
			inputarray();
			for (int b = 0; b < N; b++){ //When the bth integer of array is read, median of integers from 0 to b is calculated and added to "output"
				insert(array[b]); //Scan whether the bth integer is 1, 3 or 5 (for sorting purposes later)
				output = output + findmedian(b + 1); // Use b + 1 since arrays start from 0 instead of 1
			}
			cout << output << endl; //Reset continuous median variable for next iteration
		}

};

int main(int argc, char const *argv[])
{
	//The next two lines were recommended by tutor to be inserted so as to speed up cin/cout
	ios_base::sync_with_stdio(false); //Tells cin and scanf not to update each other
	cin.tie(0); //Tells cin and cout not to update each other
	
	Median test;

	int TC = test.inputTC();

	if (TC == 0){ //If zero test cases, then no point continuing
		return 0;
	}

	test.findmedians();
    cout << "By submitting this source code, I declare that it is MY OWN implementation work. "
        "I fully understand the underlying algorithm behind the code that I wrote and can prove it "
        "to Lab TA if asked." << endl;

	return 0;
}
