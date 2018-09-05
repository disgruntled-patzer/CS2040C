/*Problem Set 1 Subtask A, Lau Yan Han
There are up to 100 test cases (TC)
For each test case, the user inputs an array of 0 < N < 500 integers (range 0 to 10^9 for each integer)
Then the program iterates through the array. When it reads the ith integer of the array
It computes the median of the SORTED array up till the ith integer, and adds it to a continuous median sum
It then repeats this for the rest of the array and outputs the final continuous median sum
Then the whole process is repeated for all test cases*/

#include <iostream>
#include <cmath>
using namespace std;

#define TCMAX 100
#define NMAX 500

class Median {

    private:
        int TC; //Number of test cases
        int N; //Max number of integers in the array, for each test case
        unsigned long TotalTC[TCMAX]; //Total number of test cases. Used to store output of each test case for printing
        unsigned long array[NMAX]; //Array used for each test case to find continuous median

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
            
            for (int i = 0; i < N; i++){
                cin >> array[i];
            }
        }

        /*Insert the newest array entry into its sorted position along the array entries before it
        Note that we don't need to use a sorting algorithm, because all the entries before the new entry
        would already have been sorted. Thus, all we need to do is perform a binary search to find the 
        correc position to insert the new entry*/
        void binaryinsert(int low, int current){
            
            unsigned long temp; //Used when inserting the entry into its new position

            if (low == current){ //Edge Case 1: No array before new entry, no need to do any insert
                return;
            }
            if (low == current - 1){ //Edge Case 2: Only one entry before new entry
                if (array[low] > array[current]){ //Then just compare and swap if necessary
                    temp = array[current];
                    array[current] = array[low];
                    array[low] = temp;
                }
                return;
            }
            //Edge Case 3: New entry is already larger than previous entry, thus it is in its correct position
            if (array[current - 1] <= array[current]){
                return;
            }

            //No edge cases: Must do a binary search to insert the new entry into its desired position
            int high = current - 1; //Position of entry right before the new entry
            int mid = low + (high - low)/2; //Same as (high + low)/2 but prevents overflow if low and high are large

            //Binary search loop: Search for the position in array to insert new entry/
            while (low < high){
                if (array[mid] == array[current]){
                    break;
                } 
                else if (array[mid] < array[current]){
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
                mid = low + (high - low)/2; //Update mid for next iteration, or to mark position of new entry after exiting loop
            }

            /*At the end of the binary search, "mid" entry is the closest to where the new entry
            should be inserted. If "mid" entry is larger than new entry, than new entry goes before
            "mid". If "mid" is smaller, then new entry goes after "mid"*/

            temp = array[current]; //Assign the new entry to temp variable to be inserted later

            if (array[mid] > array[current]){ //If "mid" is larger than new entry
                for (int i = current - 1; i >= mid; i--){
                    array[i + 1] = array[i]; //Inner loops translate all entries after "mid" to the right by one entry
                }
                array[mid] = temp; //Then assign the new entry to its desired position
            }
            else { //If "mid" entry is smaller or equals to new entry
                for (int i = current - 1; i >= mid + 1; i--){ //Then do same as first 'if' statment
                    array[i + 1] = array[i]; //Except that "mid" entry does not shift
                }
                array[mid + 1] = temp;
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
            //cout << median << endl; //Debug statement

            return median;
        }
        
        //To print the final output: Continuous median for each test case
        void printresult (){

            for (int i = 0; i < TC; i++){
                cout << TotalTC[i] << endl;
            }
        }
        
        //Main driver function to find continuous median for each test case
        void findmedians (){

            unsigned long output = 0; //Continuous median sum that will be printed
            int a, b; //Loop counters

            for (a = 0; a < TC; a++){ //For each test case, find N, input array, sort array, and calculate continuous median
                inputN();
                inputarray();
                for (b = 0; b < N; b++){ //When the bth integer of array is read, median of integers from 0 to b is calculated and added to "output"
                    binaryinsert(0, b); //If the bth integer needs to be sorted, then insert it into the desired sorted position
                    output = output + findmedian(b + 1); // Use b + 1 since arrays start from 0 instead of 1
                }
                TotalTC[a] = output; //Add this final continuous median to the TotalTC array to be printed later
                output = 0; //Reset continuous median variable for next iteration
            }
        }

};

int main(int argc, char const *argv[])
{
    Median test;

    test.inputTC();
    test.findmedians();
    test.printresult();

    return 0;
}