#include "relations_evaluator.h"
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

bool isReflexive(vector<Tuple> relations, set<char> s);

int main(){
    runTest1();
    runTest2();

    cout << "finished" << endl;

    return 0;
}

bool isReflexive(vector<Tuple> relations, vector<char> s) {
    for(int i = 0; i < s.size(); i++) {
        bool validCase = false;
        for(int j = 0; j < relations.size(); j++) {
            if(relations[j].left == s[i] && relations[j].left == relations[j].right) {
                validCase = true;
            }
        }
        if(!validCase) {
            return false;
        }
    }
     return true;
}

void runTest1(){
    Tuple t1;
    Tuple t2;
    t1.left = 'a';
    t1.right = 'a';
    t2.left = 'b';
    t2.right = 'b';
    vector<Tuple> relations;
    relations.push_back(t1);
    relations.push_back(t2);

    vector<char> set;
    set.push_back('a');
    set.push_back('b');

    // Reflexive
    cout << isReflexive(relations, set) << endl;
}

void runTest2(){}
