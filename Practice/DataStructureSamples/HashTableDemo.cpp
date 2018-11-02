#include <bits/stdc++.h>
using namespace std;

#define M 13 // M = table size is a prime number, rather small, for illustration purpose only, generally make M > 2*K where K is the maximum number of keys that you will likely need for your application

class BasicHashTable { // this is an attempt to emulate unordered_map<string, int> mapper;
// the 'easiest' and most robust Hash Table is actually the one with Separate Chaining collision resolution technique
private:
  list<pair<string, int>> underlying_table[M]; // you can change list to vector :O

  // from https://visualgo.net/en/hashtable?slide=4-7
  int hash_function(string v) { // assumption 1: v uses ['A'..'Z'] only
    int sum = 0;                // assumption 2: v is a short string
    for (auto &c : v) // for each character c in v
      sum = ((sum*26)%M + (c-'A'+1))%M; // M is table size
    return sum;
  }

public:
  BasicHashTable() {
    for (int i = 0; i < M; i++)
      underlying_table[i].clear(); // clear the linked list
  }

  void Insert(string key, int value) { // to emulate mapper[key] = value
    bool contains_key = false;
    for (auto &key_value : underlying_table[hash_function(key)])
      if (key_value.first == key) { // if there is an existing key
        contains_key = true;
        key_value.second = value; // update the satellite data
      }
    if (!contains_key) // no previous key before
      underlying_table[hash_function(key)].emplace_back(key, value); // just append at the back
  }

  int Search(string key) { // to emulate mapper[key]
    bool contains_key = false;
    for (auto &key_value : underlying_table[hash_function(key)]) // O(k), k is the length of this list
      if (key_value.first == key) { // if there is an existing key
        contains_key = true;
        return key_value.second; // return this satellite data
      }
    if (!contains_key) // no previous key before
      return -1; // a symbol to say such key does not exist
  }

  void Remove(string key) { // to emulate mapper.erase(key)
    auto &row = underlying_table[hash_function(key)]; // get the reference of the row
    for (auto it = row.begin(); it != row.end(); it++)
      if (it->first == key) { // if there is an existing key
        row.erase(it); // erase this (key, value) pair from this vector
        break; // do not do anything else
      }
    // we do nothing if key is not actually found
  }

  bool IsEmpty() {
    int total = 0;
    for (int i = 0; i < M; i++)
      total += (int)underlying_table[i].size();
    return total == 0;
  }
};

int main() {
  cout << "Our own Hash Table with Separate Chaining collision resolution technique" << endl;
  BasicHashTable ht;
  cout << ht.IsEmpty() << endl; // should be 1/true
  ht.Insert("STEVEN", 77);
  cout << ht.IsEmpty() << endl; // should be 0/false
  ht.Insert("STEVEN", 36); // will update instead of creating a new one
  ht.Insert("GRACE", 35);
  ht.Insert("JANE", 7);
  ht.Insert("JOSHUA", 4);
  ht.Insert("JEMIMAH", 1);
  cout << ht.Search("STEVEN") << endl; // should be 36 (not 77, it has been overwritten)
  cout << ht.Search("GRACE") << endl; // should be 35
  cout << ht.Search("STRANGER") << endl; // should be -1 (does not exist)
  ht.Remove("STEVEN");
  cout << ht.Search("STEVEN") << endl; // should be -1 now (has just been deleted)
  cout << ht.Search("GRACE") << endl; // should remain 35
  cout << ht.Search("JANE") << endl; // should be 7
  ht.Remove("JANE");
  cout << ht.Search("JANE") << endl; // should be -1 now (has just been deleted)

  cout << "C++ STL version" << endl;
  unordered_map<string, int> mapper;
  cout << mapper.empty() << endl; // should be 1/true
  mapper["STEVEN"] = 77;
  cout << mapper.empty() << endl; // should be 0/false
  mapper["STEVEN"] = 36; // will update instead of creating a new one
  mapper["GRACE"] = 35;
  mapper["JANE"] = 7;
  mapper["JOSHUA"] = 4;
  mapper["JEMIMAH"] = 1;
  cout << mapper["STEVEN"] << endl; // should be 36 (not 77, it has been overwritten)
  cout << mapper["GRACE"] << endl; // should be 35
  cout << (mapper.find("STRANGER") == mapper.end()) << endl; // should be 1 (true) ("STRANGER" does not exist)
  mapper.erase("STEVEN");
  cout << (mapper.find("STEVEN") == mapper.end()) << endl; // should be 1 (true) now (has just been deleted)
  cout << mapper["GRACE"] << endl; // should remain 35
  cout << mapper["JANE"] << endl; // should be 7
  mapper.erase("JANE");
  cout << (mapper.find("JANE") == mapper.end()) << endl; // should be 1 (true) now (has just been deleted)

  return 0;
}