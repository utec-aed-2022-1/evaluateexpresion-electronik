#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include "stack.h"

using namespace std;

struct Result{
    double result;
    bool error;

    Result(double result, bool error){
        this->result = result;
        this->error = error;
    }
};

int precedencia(char operador){
    int aux;
    if(operador == '/')
        aux=3;
    else if(operador == '*')
        aux=3;
    else if(operador == '+')
        aux=2;
    else if(operador == '-')
        aux=2;
    //else if(operador == '(')
        //aux=1;
    return aux;
};

double resolver(string input){
    Stack<double>* Numeros = new Stack<double>();
    int length = input.length();
    double op2, op1;

    for(int i = 0; i < length; ++i){

        if( !isdigit(input[i]) ){
            op2 = Numeros->pop();
            op1 = Numeros->pop();

            if(input[i] == '+'){
                Numeros->push(op1 + op2);
            }
            else if(input[i] == '-'){
                Numeros->push(op1 - op2);
            }
            else if(input[i] == '*'){
                Numeros->push(op1 * op2);
            }
            else if(input[i] == '/'){
                Numeros->push(op1 / op2);
            }
            cout << "op1: " << op1 << endl;
            cout << "op2: " << op2 << endl;
            
        }
        else{
            double aux=double(input[i])-48;
            if (int(input[i+1])>=48){
                aux = aux*10;
                aux += double(input[i+1])-48;
                i++;
            }
            Numeros -> push(aux);
        }
            
            cout << "Push: " << double(input[i]) << endl;
    }
    return Numeros->pop();
}

string ordenar(string input){
    int length = input.length();

    //Stack<char>* Postfijo = new Stack<char>();
    Stack<char>* Caracteres = new Stack<char>();
    string postfijo;
    bool operacion = 0;
    bool parentesis = 0;

    char caracter;
    for(int i = 0; i < length; ++i)
    {
        caracter = input[i];
        if (caracter != 32){

            if (isdigit(caracter))
                postfijo += caracter;
            

            else {

                if (caracter != ')'){
                    if (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/'){
                        if (operacion == 1 && parentesis == 0){
                            if(precedencia(Caracteres->front()) >= precedencia(caracter)){
                            postfijo += Caracteres->pop();
                            postfijo += input[i+2];
                            postfijo += caracter;
                            }
                            //else if
                            else{
                                postfijo += input[i+2];
                                postfijo += caracter;
                                postfijo += Caracteres->pop();
                            }
                            i += +2;
                            operacion = 0;

                            
                        }
                        else{
                            operacion = 1;
                            Caracteres -> push(caracter);
                        }

                    }
                    else{
                        parentesis = 1;
                        Caracteres -> push(caracter);
                    }
                    
                }
                else{
                    // Sacar todo lo que está en Stack
                    // hasta encontrar el primer '('

                    char carc;
                    bool detener=0;
                    while(Caracteres->size() != 0 && detener == 0){
                        carc = Caracteres -> pop();
                        if (carc == '+' || carc == '-' || carc == '*' || carc == '/')
                            postfijo += carc;
                        else if(carc == '(')
                            detener = 1;
                    }
                    parentesis = 0;
                    operacion = 0;

                }
            }
        }
    }
    while (Caracteres->size()!=0){
        postfijo+=Caracteres->pop();}
    return postfijo;
}

string conversion(string expresion){
    Stack<char>* converter = new Stack<char>();
    converter->push(' ');
    string posfija;

    for (int i=0; i<expresion.length();i++){
        char token = expresion[i];
        if (token == '0' || token == '1' || token == '2' || token == '3' || token == '4' || token == '5' || token == '6' || token == '7' || token == '8' || token == '9' || token == ' '){
            posfija += token;
            if (int(expresion[i+1])>=48){
                posfija += expresion[i+1];
                i++;
            }
        }
        else if (token == '('){
            converter->push(token);
        }
            
        else if (token == ')'){
            char topToken = converter->pop();
            while (topToken != '('){
                posfija += topToken;
                topToken = converter->pop();
            }
        }
        else{
            while (converter->size()!=0 && precedencia(converter->back()) >= precedencia(token))
                  posfija+=converter->pop();
            converter->push(token);
        }
    }
    while (converter->size()!=0){
        posfija+=converter->pop();}
    return posfija;
}

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
