#include <bits/stdc++.h>
using namespace std;

// write your matric number here: A0164750E
// write your name here: Lau Yan Han
// write list of collaborators here: Pretty much anyone who was discussing in the CS2040C telegram group
// year 2018/19 Sem1 hash code: IEXVAR3BOJ4VIYLO (do NOT delete this line)

#define male 1
#define female 2

class PS4{
	private:

		map<string, int>suggestions; //List of suggestions implemented in an ordered map (BST)
		//String contains baby name, int contains gender (1 = male, 2 = female)

	public:
		void AddSuggestion(string babyName, int genderSuitability){

			suggestions.insert(make_pair(babyName, genderSuitability));
		}

		void RemoveSuggestion(string babyName){

			suggestions.erase(babyName);
		}

		int Query(string START, string END, int gender){
			int ans = 0;
			
			//Get the boundaries of START and END using iterators
            map<string, int>::iterator first, last, count;
			first = suggestions.lower_bound(START);
			last = suggestions.upper_bound(END);

			//Edge Case: The entry on the right boundary matches END
			//Then the following block of code takes case of that by shifting "last" back one step
			//Remember that the question requires the right boundary to be open!
			--last;
			if (last->first != END){
				++last;
			}

            //Edge case: no names that are within the specified boundaries
            if (*first == *last){
				return ans;
			}

            // Iterate through range finding entries that match gender (auto match all if gender = 0)
			for (count = first; count != last; ++count){
				if (gender == 0 || count->second == gender){
					++ans;
				}
			}
			return ans;
		}
};

int main(){

	PS4 CS2040C;

	while(true) {
		int cmd = 0, genderSuitability;
		char babyName[32], START[32], END[32];
		scanf("%d", &cmd);
		if (cmd == 0) break;
		else if(cmd == 1){
			scanf("%s%d", babyName, &genderSuitability);
			CS2040C.AddSuggestion(string(babyName), genderSuitability);
		}
		else if(cmd == 2){
			scanf("%s", babyName);
			CS2040C.RemoveSuggestion(string(babyName));
		}
		else if(cmd == 3){
			scanf("%s%s%d", START, END, &genderSuitability);
			int ans = CS2040C.Query(string(START), string(END), genderSuitability);
			printf("%d\n", ans);
		}
	}
	return 0;
}