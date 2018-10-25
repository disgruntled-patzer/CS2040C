#include <bits/stdc++.h>
using namespace std;

#define M_MAX 10000

//For the "ordered_words" priority queue
#define frequency 0
#define word 1
typedef tuple<int, string> common_words;

//This T typedef will be used frequently to store word/name and either (1) Frequency or (2) Name index
typedef unordered_map<string, int> T;

//Custom Comparator for "ordered words" priority queue (obtained through trial and error o.o)
struct CustomCompare {
    bool operator()(const common_words& lhs, const common_words& rhs){
        if (get<frequency>(lhs) < get<frequency>(rhs)){
            return true;
        }
        else if (get<frequency>(lhs) > get<frequency>(rhs)){
            return false;
        }
        else {
            if (get<word>(lhs) > get<word>(rhs)){
                return true;
            }
            else {
                return false;
            }
        }
    }
};

class Log {
    private:
        
        //M = number of messages, no_of_users will eventually store total number of users on the forum
        //Current user will be used to mark the current name in the line whose messages are being read
        int M, no_of_users, current_user;
        
        //Name and Input store user-input names and message words respectively
        string name, input;
        
        //A vector of sets. Each vector entry represents a unique user.
        //The set within each entry stores all the unique words which the user typed
        unordered_set<string> words[M_MAX];
        
        //names is a list of all unique users on the forum, mapped to their entries in the "words" vector-set above
        //User and Total word_freq store all unique words on the entire forum
        //user_word_freq: The "int" refers to how many unique users have used this word
        //total_word_freq: The "int" refers to total number of times this word has appeared in the forum
        T names, user_word_freq, total_word_freq;
        
        //This PQ will be used to output the final words: Highest priority element has (1) Highest frequency
        //(2) Lower alphabet in case of a tie. The "int" in common_words here refers to frequency
        priority_queue<common_words, vector<common_words>, CustomCompare>ordered_words;
        
        //Update the user_word_freq hashtable to denote how many unique users have used each word
        void update_user_word_freq(){
            if (user_word_freq.find(input) == user_word_freq.end()){ //If input word is not found
                user_word_freq[input] = 1; //Then initialize it: 1 because one user has already used the word
            }
            else { //If word already exists, then just increment value by 1 (to mark a new user has used the word)
                T::iterator it = user_word_freq.find(input);
                it->second += 1;
            }
        }

        //Update total_word_freq hashtable to denote total times each word has appeared.
        //Working principle is same as update_user_word_freq
        void update_total_word_freq(){
            if (total_word_freq.find(input) == total_word_freq.end()){
                total_word_freq[input] = 1;
            }
            else{
                T::iterator it = total_word_freq.find(input);
                it->second += 1;
            }
        }
    
    public:

        Log(){
            no_of_users = 0; //Number of users initially zero
        }
        
        //Read messages from each user and process all of the words
        void read_messages(){
            cin >> M;
            for (int i = 0; i < M; ++i){ //Loop through all messages
                cin >> name;
                
                //This if-else keeps track of number of unique users
                if (names.find(name) == names.end()){
                    ++no_of_users;
                    names[name] = no_of_users - 1; //-1 because array starts from zero ):
                    current_user = names[name]; //Current user will be used to access "words" vector-set later
                }
                else{
                    current_user = names[name];
                }

                //This loop reads the words in each message, marks their frequency and how many users have used it
                while (cin >> input){
                    
                    //If it is the first time the current user has used this word, then add it into
                    //the current user's set of unique words.
                    if (words[current_user].find(input) == words[current_user].end()){
                        words[current_user].insert(input);
                        update_user_word_freq(); //Mark that the current user has used this word
                    }

                    update_total_word_freq(); //Then update the total frequency of the current word

                    if (cin.get() == '\n'){ //Terminate when reach end of line
                        break;
                    }
                } //End of while loop
            } //End of for loop
        }
        
        /*At the end of read_messages, the "words" vector-set contains all users on the forum
        And within each user is a list of unique words that they use. The user_word_freq and total_word_freq
        also contains the number of users who used each word, and the total number of times each word appears
        respectively. Next is to shortlist words that are used by all users, taken care of below*/

        void find_words_common_to_all_users(){
            T::iterator i;

            for (i = user_word_freq.begin(); i != user_word_freq.end(); ++i){
                
                //Words that have been used by everyone must have a user_word_freq count
                //That is equal to the total number of users
                if (i->second == no_of_users){
                    int temp_word_freq = total_word_freq[i->first]; //Get the total word frequency
                    string temp_word_name = i->first; //Get the word (duh)
                    common_words temp = make_tuple(temp_word_freq, temp_word_name);
                    ordered_words.push(temp); //Then push the combined data into the priority queue
                    //The above 4 lines can actually be condensed into
                    //ordered_words.push(make_tuple((-1)*total_word_freq[i->first], i->first));
                    //But it's better to break it up to make the code easier to trace
                }
            }
        }

        /*Once the unique words are identified, inserting into ordered_words priority queue
        will sort them automatically. Finally, what is left is to just output the common words*/

        void output(){
            if (ordered_words.empty()){
                cout << "ALL CLEAR" << endl;
            }
            else {
                common_words temp;
                while (!ordered_words.empty()){
                    cout << get<word>(ordered_words.top()) << endl;
                    ordered_words.pop();
                }
            }
        }
        
};

int main(int argc, char const *argv[])
{
    
    Log FailPE;
    FailPE.read_messages();
    FailPE.find_words_common_to_all_users();
    FailPE.output();
    
    return 0;
}
