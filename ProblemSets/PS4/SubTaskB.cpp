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

		/*List of suggestions implemented in an ordered map (BST) - male and female
		It is implemented as an array of sets, with each array entry corresponding
		to the first letter of each baby name*/
		set<string> suggestions_male[26]; 
		set<string> suggestions_female[26];	

		//A cheap method to convert A - Z to 0 - 25 (using ASCII definitions)
		int char_to_int(char data){
			return int(data) - 65;
		}

		//Do query for male names: Called by Query Function
		int query_male(string START, string END){
			int ans = 0; //Final answer

			//Start and End prefixes to determine which entry of the array to go to
			int startprefix = char_to_int(START[0]), endprefix = char_to_int(END[0]);
			
			//Iterators that point to boundaries of START and END
			auto start = suggestions_male[startprefix].lower_bound(START);
			auto end = suggestions_male[endprefix].upper_bound(END);

			if (startprefix == endprefix){ //If both START and END have same first digit		
				ans = distance(start, end);
			}
			else{
				//Get distance from START to end of its set
				ans += distance(start, suggestions_male[startprefix].end());

				//For entries between start and end, get the entire set size
				for (int j = startprefix + 1; j < endprefix; ++j){
					ans += suggestions_male[j].size();
				}

				//Get distance from start of END set to END
				ans += distance(suggestions_male[endprefix].begin(), end);
			}

			/*Brute force method to deal with the edge case where the entry at the
			right boundary equals END. Then this entry cannot be counted, since right
			boundary is open. Hence decrement ans by 1 in such a case*/
			for (int k = startprefix; k != endprefix + 1; ++k){
				if (suggestions_male[k].find(END) != suggestions_male[k].end()){
					--ans;
					break;
				}
			}

			return ans;
		}

		//Do query for female names, essentially similar to query_male, called by Query Function
		int query_female(string START, string END){
			int ans = 0;
			int startprefix = char_to_int(START[0]), endprefix = char_to_int(END[0]);
			auto start = suggestions_female[startprefix].lower_bound(START);
			auto end = suggestions_female[endprefix].upper_bound(END);

			if (startprefix == endprefix){		
				ans = distance(start, end);
			}
			else{
				ans += distance(start, suggestions_female[startprefix].end());
				for (int j = startprefix + 1; j < endprefix; ++j){
					ans += suggestions_female[j].size();
				}
				ans += distance(suggestions_female[endprefix].begin(), end);
			}

			for (int k = startprefix; k != endprefix + 1; ++k){
				if (suggestions_female[k].find(END) != suggestions_female[k].end()){
					--ans;
					break;
				}
			}

			return ans;
		}

	public:

		void AddSuggestion(string babyName, int genderSuitability){

			//Assign the name to its respective entry in male/female sets based on first letter of name
			int prefix = char_to_int(babyName[0]);
			switch (genderSuitability){
				case male:
					suggestions_male[prefix].insert(babyName);
					break;
				case female:
					suggestions_female[prefix].insert(babyName);
					break;
				default:
					break;
			}
		}

		void RemoveSuggestion(string babyName){

			//Note that can just call erase in both male and female sets
			//If name doesn't exit in either of the sets, the set contents aren't affected anyway
			int prefix = char_to_int(babyName[0]);
			suggestions_male[prefix].erase(babyName);
			suggestions_female[prefix].erase(babyName);
		}

		int Query(string START, string END, int gender){
			int ans = 0;

			//Split up the query function into their respective gender functions
			switch (gender){
				case male:
					ans = query_male(START, END);
					break;
				case female:
					ans = query_female(START, END);
					break;
				default:
					ans = query_male(START, END) + query_female(START, END);
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