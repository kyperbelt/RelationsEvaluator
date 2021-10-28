#include "relations_evaluator.h"
#include <iostream>
#include <locale>


using namespace std;



int main(){
    runTest1();
    runTest2();

    cout << "finished" << endl;

    return 0;
}

void runTest1(){

    cout << "tests1" << endl;
}

void runTest2(){
    cout << "tests2" << endl;


    string s = "a,b,c,d,e,f,g";

    set<char> s1 = parseSet(s);

    cout << "set:" << endl;
    for(char item: s1){
        cout << item << endl;
    }

    vector<Tuple> relations = parseRelations("(a,b) (c,d) (b,a)",s1);

    cout << "relations: " << endl;
    for(Tuple t: relations){

        cout << tupleToString(t) << endl;

    }

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
                            result.push_back(Tuple{left,c});
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
