#include <iostream>
#include <string>
# include <list>
using namespace std;
int max_size = 10;

struct student{
    string name;
    string id;
};

int main()
{
    list<student>* bucket[max_size];
    for(int i=0;i<max_size;i++){
        bucket[i] = new list<student>;
    }
    int n;
    cout << "Enter n:" << '\n';
    cin >> n;
    for (int i=0;i<n;i++){
        cout << "Student:" << (i+1) << '\n';
        string name, id;
        int age;
        cout << "Enter name:" << '\n';
        cin >> name;
        cout << "Enter id:" << '\n';
        cin >> id;
        cout << "Enter age (between 18 and 27):" << '\n';
        cin >> age;
        cout << '\n';
        student s;
        s.name = name;
        s.id = id;
        bucket[age-18]->push_back(s);
    }
    int v;
    cout << "Enter query age (between 18 and 27):" << '\n';
    cin >> v;
    list<student>* l = bucket[v-18];
    for (auto itr=l->begin(); itr != l->end(); itr++){
        cout << itr->name << '\n';
    }
    return 0;
}
