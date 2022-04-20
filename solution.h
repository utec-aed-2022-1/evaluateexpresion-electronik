#include <iostream>
#include <string>
#include "stack.h"
#include "forward.h"
// #include <stack>
// #include <vector>

using namespace std;

struct Result{
    double result;
    bool error;

    Result(double result, bool error){
        this->result = result;
        this->error = error;
    }
};


bool isOperator(char input){
    bool isPlus = input == '+';
    bool isMin = input == '-';
    bool isMul = input == '*';
    bool isDiv = input == '/';
    return isPlus || isMin || isMul || isDiv;
}

int precedence(char oper){
    int aux;
    switch (oper){
        case '(':
            aux = 1;
            break;
        case ')':
            aux = 1;
            break;
        case '+':
            aux = 2;
            break;
        case '-':
            aux = 2;
            break;
        case '*':
            aux = 3;
            break;
        case '/':
            aux = 4;
            break;            
        default:
            break;
    }
    return aux;
}

double performOp(double op1, double op2, char op){
    double result;
    switch (op){
        case '+':
            result = op1 + op2;
            break;
        case '-':
            result = op1 - op2;
            break;
        case '*':
            result = op1 * op2;
            break;
        case '/':
            result = op1 / op2;
            break;            
        default:
            break;
    }
    return result;
}

Result evaluate(string input)
{
    double result;
    bool error = false;
    string infix = ""; // input sin espacios
    int leftPar = 0;
    int rightPar = 0;
    // 1- descomponer el input y validar
    for(string::iterator it = input.begin(); it != input.end(); ++it) {
        if( !( isdigit(*it) || isOperator(*it) || *it == ' ' || *it == ')' || *it == '(') ){
            result = 0;
            error = true;
            break;
        } else if(*it != ' '){
            if(*it == '('){
                leftPar++;
            }
            else if(*it == ')'){
                rightPar++;
            }
            infix.push_back(*it);
        }
    }

    error = !(leftPar == rightPar) || error;
    error = !(isdigit(infix.back()) || infix.back() == ')') || error;

    //* Si no cumple la validacion retornar Result.error = true;

    if(!error){
        // 2- convertir de Infijo a Postfijo
        // Create an empty stack called opstack for keeping operators. Create an empty list for output.
        Stack<char> opstack(20);
        ForwardList<char> output; // postfix

        // Scan the token list from left to right.
        for(string::iterator it = infix.begin(); it != infix.end(); ++it){
            // If the token is an operand, append it to the end of the output list
            if (isdigit(*it)){
                output.push_back(*it);            
            } else if(*it == '('){ // If the token is a left parenthesis, push it on the opstack
                opstack.push(*it);
            } else if(*it == ')'){ // If the token is a right parenthesis
                // Pop the opstack until the corresponding left parenthesis is removed
                while(opstack.top() != '('){
                    // Append each operator to the end of the output list
                    char temp = opstack.pop();
                    output.push_back(temp);
                }
                opstack.pop(); // Remover paréntesis
            } else if(*it == '*' || *it == '/' || *it == '+' || *it == '-'){ // If the token is an operator, *, /, +, or -
                // Remove any operators already on the opstack that have higher or equal precedence and append them to the output list
                if(!opstack.empty()){
                    char temp = opstack.top();
                    if(precedence(temp) >= precedence(*it)){
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
            char temp = opstack.pop();
            output.push_back(temp);
        }

        // 3- resolver la expresion
            // Create an empty stack called operandStack.
        Stack<double> operandstack(20);

            // Scan the token list from left to right.
            for(int i = 0; i < output.size(); i++){
            // If the token is an operand, convert it from a string to an integer and push the value onto the operandStack.
                if(isdigit(output[i])){
                    double temp = (double)output[i]-48; // todo lo que esta después del () es double
                    operandstack.push(temp);
                } else if(isOperator(output[i])){ // If the token is an operator, *, /, +, or -.
                    // Pop the operandStack twice.
                    double op2 = operandstack.pop(); // The first pop is the second operand
                    double op1 = operandstack.pop();  // The second pop is the first operand.
                    // Perform the arithmetic operation.
                    double opResult = performOp(op1, op2, output[i]);
                    //Push the result back on the operandStack.
                    operandstack.push(opResult);
                }
            }
            // Pop the operandStack and return the value.
            result = operandstack.pop();
    }
    return Result(result, error);
}
