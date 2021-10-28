#include "relations_evaluator.h"
#include <iostream>
#include <locale>
#include <map>
#include <algorithm>
#include <sstream>

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


void runTest2(){
    cout << "tests2 =================" << endl;

    auto relationSetToString = [](vector<Tuple> r)->string{
        stringstream s;
        s << "R:{";
        for(Tuple t: r){
            s << " " << tupleToString(t);
        }
        s << " }";
        return s.str();
    };

    auto setToString = [](set<char> x)->string{
        stringstream s;
        s << "X:{";
        for (char c : x){
            s << " " << c;
        }
        s << " }";

        return s.str();
    };

    string s = "a,b,c";

    set<char> s1 = parseSet(s);

    // cout << "set:" << endl;
    // for(char item: s1){
    //     cout << item << endl;
    // }

    vector<Tuple> relations = parseRelations("(a,b) (c,a) (a,c) (b,a)",s1);

    // cout << "relations: " << endl;
    // for(Tuple t: relations){
    //     cout << tupleToString(t) << endl;
    // }

    cout << "Symmetry Tests for " << setToString(s1) << endl;
    cout << "is the set "<< relationSetToString(relations)<<" Symmetric? : " << (isSymmetric(relations, s1) ? "true" : "false") << endl;
    relations = parseRelations("(a,a) (c,c) (b,b)", s1);
    cout << "is the set "<< relationSetToString(relations)<<" Symmetric? : " << (isSymmetric(relations, s1) ? "true" : "false") << endl;
    relations = parseRelations("(a,a),(c,c) (b,b) (b,c)", s1);
    cout << "is the set "<< relationSetToString(relations)<<" Symmetric? : " << (isSymmetric(relations, s1) ? "true" : "false") << endl;

    set<char> s2 = parseSet("0 1 2 3");
    relations = parseRelations("(1,2) (3,3),(2,1),(1,1),(1,0)", s2);

    cout << "AntiSymmetry Tests for " << setToString(s2) << endl;
    cout << "is the set "<< relationSetToString(relations)<<" AntiSymmetric? : " << (isAntiSymmetric(relations, s2) ? "true" : "false") << endl;
    relations = parseRelations("(3,3),(2,1),(1,1),(0,1),(0,0)", s2);
    cout << "is the set "<< relationSetToString(relations)<<" AntiSymmetric? : " << (isAntiSymmetric(relations, s2) ? "true" : "false") << endl;
}

std::string tupleToString(Tuple t){
    string result;

    result.push_back('(');
    result.push_back(t.left);
    result.push_back(',');
    result.push_back(' ');
    result.push_back(t.right);
    result.push_back(')');

    return result;
}

set<char> parseSet(string input){
    set<char> result;

    for(int i=0; i < input.size(); i++){
        char c = input[i];
        if (c == ' ' || c == ',') continue; // this is a space or a comma so we skip it
        result.insert(c);
    }

    return result;
}


std::vector<Tuple> parseRelations(std::string input,std::set<char> &s){
    vector<Tuple> result;

    const int BASE = 0;
    const int ERROR = 1;
    const int TUPLE = 2;
    const int CLOSE = 3;

    int currentState = BASE;

    char left = '\0';

    for(int i=0; i< input.size(); i++){
        char c = input[i];
        switch(currentState){
            case BASE:{
               // in the base case we ignore all spaces and commas, we are looking for '(' to bring a tuple
                if (c == '('){
                    currentState = TUPLE;
                }else if (c == ' ' || c == ','){
                    continue;
                }else{
                    // we have encountered an invalid vaiable
                    //TODO: throw an error or notify user of mistake
                    cerr << "invalid chacacter on line:" << input << " at index:" << i
                         << " was expecting a tuple opening char '(' got '" << c << "' instead." << endl;
                }
            }
            break;
            case TUPLE: {
                if (isalnum(c)){
                    if (s.count(c) == 0){
                        cerr << "Invalid element <" << c << "> @index:" << i << " not found in set provided." << endl;
                        currentState = ERROR;
                    }else{
                        if (left == '\0'){
                            left = c;
                        }else{
                            Tuple t = {left,c};
                            if(!hasTuple(result, t)){ // if we already added this tuple then we dont want do it again
                                result.push_back(t);
                            }else{
                                cerr << "Duplicate Tuple '" << tupleToString(t) << "' - did not add." << endl;
                            }
                            left = '\0';
                            currentState = CLOSE;
                        }
                    }
                }else if(c == ')'){
                    currentState = BASE;
                }else{
                    continue;
                }
            }
                break;
            case ERROR: {
                cerr << "discarding " << c << " at index:" << i << endl;
            }
            case CLOSE: {
                if (c == ')') currentState = BASE;
            }break;
            default: break; // reached an invalid state
        }

    }

    return result;
}


bool isSymmetric(std::vector<Tuple> relations,std::set<char> s){

    // using this set container to check
    // the different elemetns we have checked for
    // and by the end it should be the same size as our
    // set s. Otherwise the symmetry does not apply since
    // it will not be for all elements of our set.
    set<char> checked;

    for(Tuple t: relations){
        if(!hasTuple(relations,Tuple{t.right,t.left}))
            return false;
        checked.insert(t.right);
        checked.insert(t.left);
    }
    bool checkedAll = checked.size() == s.size();

    if(!checkedAll){
        cerr << "Forall elements condition unmet, not all elements in set were accounted for in the relation" << endl;
    }

    return checkedAll;
}

bool isAntiSymmetric(std::vector<Tuple> relations,std::set<char> s){
    // same premise as in isSymmetric. We want to make sure we
    // check all ements in the set S
    set<char> checked;

    for (Tuple t: relations){
        if(hasTuple(relations,Tuple{.left = t.right, .right = t.left}) && t.left != t.right)
            return false;
        checked.insert(t.left);
    }
    bool checkedAll = checked.size() == s.size();

    if(!checkedAll){
        cerr << "Forall elements condition unmet, not all elements in set were accounted for in the relation" << endl;
    }

    return checkedAll;
}

bool hasTuple(std::vector<Tuple> relations, Tuple t){
    for (Tuple n: relations){
        if (n.left == t.left && n.right == t.right) return true;
    }
    return false;
}


// TODO: remember why I even made this function xD
// std::vector<Tuple> getAllTuplesThatHave(std::vector<Tuple> relations, char c, bool right){
//     vector<Tuple> results;

//     for(Tuple t: relations){
//         bool matched = (right && t.right == c) || t.left == c;
//         if (matched)
//             results.push_back(Tuple{t.left,t.right});
//     }

//     return results;
// }
