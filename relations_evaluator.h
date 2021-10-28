#ifndef RELATIONS_EVALUATOR
#define RELATIONS_EVALUATOR

#include <set>
#include <vector>
#include <string>

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



/**
 * parser the input string into a vector of valid tuples over the set s
 *
 * @example input: "(a,b) (b,a)"
 *
 * @return vector<Tuple> relations
 **/
std::vector<Tuple> parseRelations(std::string input,std::set<char> &s);


/**
 * parse the input string into a valid set
 *
 * @example input: "a b c d"
 *
 * 
 * @return set::<>
 **/
std::set<char>     parseSet(std::string input);


std::string tupleToString(Tuple t);


/***
 * Get a subset of the relation Tuples where the it contains the
 * specified char on the left, or on the right if the third parameter is
 * set to true
 *
 * @returns a vector<Tuple> that is a subset of Relations
 **/
std::vector<Tuple> getAllTuplesThatHave(std::vector<Tuple> relations, char c, bool right = false);


/**
 * Check if the relations vector contains the specified tuple
 **/
bool hasTuple(std::vector<Tuple> relations, Tuple t);

#endif
