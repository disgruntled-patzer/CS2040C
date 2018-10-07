#include<iostream>
#include<unordered_map>

using namespace std;

int main() {
  unordered_map<string, int> mapper({{"john", 78}, {"billy", 69}});

  mapper["andy"] = 80; 
  mapper["steven"] = 77;
  mapper["felix"] = 82;

  mapper.insert({"grace", 75});
  mapper.insert({"martin", 81});

  string key = "andy";

  cout << mapper.count(key) << " ";

  if (mapper.find(key) != mapper.end()) {
    cout << (*mapper.find(key)).second << endl;
  } else {
    cout << key + " does not exist in map." << endl;
  }
  cout << endl;

  cout << mapper.size() << endl;
  for(pair<string,int> item: mapper) {
    cout << item.first << " " << item.second << endl;
  }
  cout << endl;

  mapper.erase(key);
  cout << mapper.size() << endl;
  for(auto item: mapper) {
    cout << item.first << " " << item.second << endl;
  }
  cout << endl;

  mapper.clear();
  cout << mapper.empty() << endl;
}
