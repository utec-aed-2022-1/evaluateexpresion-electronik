#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>

using namespace std;

struct Result{
    double result;
    bool error;

    Result(double result, bool error){
        this->result = result;
        this->error = error;
    }
};


Result evaluate(string input)
{
    double result;
    bool error = false;
    string infix = ""; // input sin espacios
    // 1- descomponer el input y validar
    for(string::iterator it = input.begin(); it != input.end(); ++it) {
        if( !( (*it >= 40 && *it <= 43) || (*it >= 47 && *it <= 57) || *it == 45 || *it == ' ') ){ // ASCII
            result = 0;
            error = true;
            break;
        } else if(*it != ' '){
            infix.push_back(*it);
        }
    }
    
    //* Si no cumple la validacion retornar Result.error = true;

    if(!error){
        // 2- convertir de Infijo a Postfijo
        map<char, int> precedence = { { '(', 1 },
                                      { ')', 1 },
                                      { '+', 2 },
                                      { '-', 2 },
                                      { '*', 3 },
                                      { '/', 3 } };
        // Create an empty stack called opstack for keeping operators. Create an empty list for output.
        stack<char> opstack;
        vector<char> output; // postfix

        // Scan the token list from left to right.
        for(string::iterator it = infix.begin(); it != infix.end(); ++it) {
            // If the token is an operand, append it to the end of the output list
            if (*it >= 48 && *it <= 57){
                output.push_back(*it);            
            } else if(*it == '('){ // If the token is a left parenthesis, push it on the opstack
                opstack.push(*it);
            } else if(*it == ')'){ // If the token is a right parenthesis
                // Pop the opstack until the corresponding left parenthesis is removed
                while(opstack.top() != '('){
                    // Append each operator to the end of the output list
                    char temp = opstack.top();
                    output.push_back(temp);
                    opstack.pop();
                }
                opstack.pop(); // Remover paréntesis
            } else if(*it == '*' || *it == '/' || *it == '+' || *it == '-'){ // If the token is an operator, *, /, +, or -
                // Remove any operators already on the opstack that have higher or equal precedence and append them to the output list
                if(!opstack.empty()){
                    char temp = opstack.top();
                    if(precedence[temp] >= precedence[*it]){
                        output.push_back(temp);
                        opstack.pop();
                    }
                }
                // Push it on the opstack
                opstack.push(*it);
            }
        }
        // Any operators still on the stack can be removed and appended to the end of the output list
        while(!opstack.empty()){
            char temp = opstack.top();
            output.push_back(temp);
            opstack.pop();
        }

        // 3- resolver la expresion
    }   

    return Result(result, error);
}
