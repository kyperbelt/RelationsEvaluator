#ifndef RELATIONS_EVALUATOR
#define RELATIONS_EVALUATOR

#include <set>
#include <vector>

struct Tuple{
    char left = '\0';
    char right = '\0';
};


bool isTransitive(std::vector<Tuple> relations,std::set<char> s);
bool isReflexive(std::vector<Tuple> relations,std::set<char> s);
bool isSymmetric(std::vector<Tuple> relations,std::set<char> s);
bool isAntiSymmetric(std::vector<Tuple> relations,std::set<char> s);
bool isComparable(std::vector<Tuple> relations,std::set<char> s);


void runTest1();
void runTest2();

#endif
