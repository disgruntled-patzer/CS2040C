/*Source: Merge Sort Algorithm is taken from https://www.geeksforgeeks.org/merge-sort/*/

#include <iostream>
#include <cmath>
using namespace std;

#define NMAX 500

class Sort {

    private:
        int N;
        int array[NMAX]; //Array used for each test case to find continuous median

    public:

        //Get user to input number of integers into the array
        void inputN () {
            int data;
            cin >> data;
            N = data;
        }

        //Get the user to input integers into the array before sorting them
        void inputarray (){

            inputN();
            
            for (int i = 0; i < N; i++){
                cin >> array[i];
            }

            mergesort(0, N);
        }

        //Merge function called by Merge Sort Algorithm
        void merge (int L, int M, int R){
            
            int i, j, k; //Loop counters used to merge subarrays
            int n1 = M - L + 1; //Number of cells in Left subarray (from l to m)
            int n2 = R - M; //Number of cells in Right subarray (from m+1 to r)
            int Left[n1], Right[n2]; //Left and Right subarrays

            //Assign the Left and Right subarrays with their respective data
            for (i = 0; i < n1; i++){
                Left[i] = array[L + i]; 
            }
            for (j = 0; j < n2; j++){
                Right[j] = array[M + 1 + j];
            }

            //Next step: Merge both subarrays back into the original array, 
            i = 0; //Counter for Left subarray
            j = 0; //Counter for Right subarray
            k = L; //Counter for main array

            //Traverse along both subarrays, keep taking the smaller value of each subarray and merge into the main array
            while (i < n1 && j < n2){ //Keep doing the merging until either one of the subarray has hit its limit
                if (Left[i] <= Right[j]){
                    array[k] = Left[i];
                    i++;
                }
                else {
                    array[k] = Right[j];
                    j++;
                }
                k++;
            }

            //When previous loop exits, one of the subarrays will still have data that isn't merged back into main array
            //Hence the next two loops take care of the remaining data
            while (i < n1){
                array[k] = Left[i];
                i++;
                k++;
            }
            while (j < n2){
                array[k] = Right[j];
                j++;
                k++;
            }

        }

        //Merge Sort Algorithm. L stands for left bound of array, R for right bound
        void mergesort (int L, int R){
            
            if (L < R){
                int M = L + (R-1)/2; //Same as (L+R)/2, but prevents overflow for large values of L and R

                mergesort(L, M);
                mergesort(M + 1, R);

                merge(L, M, R);
            }

        }

        //To print the final output: Continuous median for each test case
        void printresult (){

            for (int i = 0; i < N; i++){
                cout << array[i] << endl;
            }
        }

};

int main(int argc, char const *argv[])
{
    Sort test;

    test.inputarray();
    test.printresult();

    return 0;
}
