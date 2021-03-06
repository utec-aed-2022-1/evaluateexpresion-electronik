#include <iostream>
#include <string>
#include "stack.h"
#include "forward.h"
#include <math.h>
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
    // Devuelve cualquier retorno '1'
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
            if(isdigit(infix[infix.length()-2]) && !isOperator(*it) && *it != '(' && *it != ')'){
                infix.push_back('.');

            }
        }
    }

    error = !(leftPar == rightPar) || error;
    error = !(isdigit(infix.back()) || infix.back() == ')' || infix.back() == '.') || error;

    //* Si no cumple la validacion retornar Result.error = true;

    if(!error){
        // 2- convertir de Infijo a Postfijo
        // Create an empty stack called opstack for keeping operators. Create an empty list for output.
        Stack<char> opstack(50);
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
                opstack.pop(); // Remover par??ntesis
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
            } else if(*it == '.'){
                output.push_back(*it);
            }
        }
        // Any operators still on the stack can be removed and appended to the end of the output list
        while(!opstack.empty()){
            char temp = opstack.pop();
            output.push_back(temp);
        }

        // 3- resolver la expresion
            // Create an empty stack called operandStack.
        Stack<double> operandstack(50);

            // Scan the token list from left to right.
            for(int i = 0; i < output.size(); i++){
            // If the token is an operand, convert it from a string to an integer and push the value onto the operandStack.
                if(isdigit(output[i]) || output[i] == '.'){
                    double temp = 0;
                    if(output[i] == '.'){
                        int count = i-1;
                        double mult = 0;
                        while(!isOperator(output[count])){
                            temp += operandstack.pop()*pow(10,mult);
                            mult++;
                            count--;
                        }
                    } else{
                        temp = (double)output[i]-48; // todo lo que esta despu??s del () es double
                    }
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

// string ordenar(string input){
//     int length = input.length();

//     //Stack<char>* Postfijo = new Stack<char>();
//     Stack<char>* Caracteres = new Stack<char>();
//     string postfijo;
//     bool operacion = 0;
//     bool parentesis = 0;

//     char caracter;
//     for(int i = 0; i < length; ++i)
//     {
//         caracter = input[i];
//         if (caracter != 32){

//             if (isdigit(caracter))
//                 postfijo += caracter;
            

//             else {

//                 if (caracter != ')'){
//                     if (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/'){
//                         if (operacion == 1 && parentesis == 0){
//                             if(precedencia(Caracteres->front()) >= precedencia(caracter)){
//                             postfijo += Caracteres->pop();
//                             postfijo += input[i+2];
//                             postfijo += caracter;
//                             }
//                             //else if
//                             else{
//                                 postfijo += input[i+2];
//                                 postfijo += caracter;
//                                 postfijo += Caracteres->pop();
//                             }
//                             i += +2;
//                             operacion = 0;

                            
//                         }
//                         else{
//                             operacion = 1;
//                             Caracteres -> push(caracter);
//                         }

//                     }
//                     else{
//                         parentesis = 1;
//                         Caracteres -> push(caracter);
//                     }
                    
//                 }
//                 else{
//                     // Sacar todo lo que est?? en Stack
//                     // hasta encontrar el primer '('

//                     char carc;
//                     bool detener=0;
//                     while(Caracteres->size() != 0 && detener == 0){
//                         carc = Caracteres -> pop();
//                         if (carc == '+' || carc == '-' || carc == '*' || carc == '/')
//                             postfijo += carc;
//                         else if(carc == '(')
//                             detener = 1;
//                     }
//                     parentesis = 0;
//                     operacion = 0;

//                 }
//             }
//         }
//     }
//     while (Caracteres->size()!=0){
//         postfijo+=Caracteres->pop();}
//     return postfijo;
// }


