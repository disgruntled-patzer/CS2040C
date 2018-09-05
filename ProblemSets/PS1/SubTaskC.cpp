/*Same as Task A except: 0 < TC < 1, 0 < N < 20,000,000, All integers are 1, 3 or 5*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#define NMAX 200000000

class Median {

	private:
		int TC; //Number of test cases (which is 1 in this case, so it is effectively just for show)
		int N; //Max number of integers in the array, for each test case
        vector<int> array; //Variable-Length Array used for each test case to find continuous median (only 1, 3 and 5) 

	public:

		//Get user to input number of test cases
		void inputTC () {
			int data;
			cin >> data;
			TC = data;
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

		/*Insert the newest array entry into its sorted position along the array entries before it
		  Note that we don't need to use a sorting algorithm, because all the entries before the new entry
		  would already have been sorted. Thus, all we need to do is perform a search to find the 
		  correct position to insert the new entry*/
		void insert(int low, int current){

			int temp; //Used when inserting the entry into its new position

			if (low == current){ //Edge Case 1: No array before new entry, no need to do any insert
				return;
			}
			if (low == current - 1){ //Edge Case 2: Only one entry before new entry
				if (array[low] > array[current]){ //Then just compare and swap if necessary
					swap(array[current], array[low]);
				}
				return;
			}
            //Edge Case 3: New entry is already larger than previous entry, thus it is in its correct position
            if (array[current - 1] <= array[current]){
                return;
            }

			//No edge cases: Must do a search to insert the new entry into its desired position
			temp = array[current]; //Assign the new entry to temp variable to be inserted later

			int i;

			/*Scan backwards along the array to find the point where to insert the new entry
			Since all entries are 1, 3 or 5, just scan until either of three conditions occur:

			1. Current entry equals new entry, then insert new array after current entry (array[i] != array[current])
			2. New entry's number is not present in array, and new entry is smaller than all
				other entries in the array. Then insert new entry at start of array (i >= 0)
			3. New entry's number is not present in array, but new entry is not the smallest
				number in array. Then insert new entry at the position immediately after
				the last array entry that is smaller than the new entry (array[i] > array[current]*/
			
			for (i = current - 1; i >= 0 && (array[i] != array[current]) || array[i] > array[current]; i--){
				array[i + 1] = array[i]; //While scanning, shift all scanned entries to the right to make space for new entry
			}
			//After exiting the loop, insert new entry into its desired position
			if (i == 0){
				array[i] = temp; //Insert new entry into the starting position (if i is at start of array)
			}
			else {
				array[i + 1] = temp; //Otherwise insert new entry into the position after ith entry
			}

		}

		//Finds median of a set of integers within an array
		int findmedian (int x){

			int median;

			if (x % 2 != 0){ //If number of integers is odd
				median = array[x/2]; //Return the middle integer (note: x/2 because arrays start from 0)
			}
			else { //If number of integers is even
				median = (array[(x/2) - 1] + array[x/2]) / 2; //Calculate average of middle two integers
				median = floor (median); //And return the rounded down value
			}
			cout << median << endl; //Debug statement

			return median;
		}

		//Main driver function to find continuous median for each test case
		void findmedians (){

			int output = 0; //Continuous median sum that will be printed

			inputN();
			inputarray();
			for (int b = 0; b < N; b++){ //When the bth integer of array is read, median of integers from 0 to b is calculated and added to "output"
				insert(0, b); //If the bth integer needs to be sorted, then insert it into the desired sorted position
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

	test.inputTC();
	test.findmedians();
    cout << "By submitting this source code, I declare that it is MY OWN implementation work. "
        "I fully understand the underlying algorithm behind the code that I wrote and can prove it "
        "to Lab TA if asked." << endl;

	return 0;
}
