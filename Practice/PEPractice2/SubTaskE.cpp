#include <bits/stdc++.h>
using namespace std;

#define offlimits "SINGAPORE"

typedef pair<string, string>link; //Defines a link between two cities (origin to destination)

class Practice2{
    private:
        vector<link>non_source_inputs; //For any inputs that don't contain "SINGAPORE"
        unordered_set<string>transit_cities; //To store cities that can be reached directly from Singapore
        set<string>reachable_cities; //Final output of cities that can be reached in two flights max
    
    public:

        void inputdata(){
            int F;
            cin >> F; //Number of flights
            string origin, dest; //Inputs origin and destination
            for (int i = 0; i < F; ++i){
                cin >> origin >> dest;
                //Compare both origin and destination;
                //If either contains Singapore, the other is reachable in one flight
                if (origin.compare(offlimits) == 0){
                    //Mark city as reachable, as well as being a transit city
                    reachable_cities.insert(dest);
                    transit_cities.insert(dest);
                }
                else if (dest.compare(offlimits) == 0){
                    reachable_cities.insert(origin);
                    transit_cities.insert(origin);
                }
                else{
                    //Store the non Singapore inputs to be processed later
                    non_source_inputs.push_back(make_pair(origin, dest));
                }
            }
        }

        void handletransits(){
            
            /*Iterate through the inputs that do not contain Singapore
            If any contains a transit city, then the other city
            Is reachable by Singapore within two flights. Note that the STL set
            will automatically take care of any repeats*/
            auto it = non_source_inputs.begin();
            while (it != non_source_inputs.end()){
                if (transit_cities.find(it->first) != transit_cities.end()){
                    reachable_cities.insert(it->second);
                }
                else if (transit_cities.find(it->second) != transit_cities.end()){
                    reachable_cities.insert(it->first);
                }
                else {
                    //Do nothing
                }
                ++it;
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
    MugforPE.handletransits();
    MugforPE.outputresult();
    return 0;
}
