#include <iostream>
#include "solution.h"
#include "tester.h"

using namespace std;


int main()
{
    string expr="";
    //expr = "5 + 8 / 2";
    
    //expr = "(7 + 8) / 2";

    expr = "(6 + 8) / (5 + 2)";

    //expr = "(6 + 8) / (5 + 2) * 12";
    
    string expr1 = expr;
    expr = ordenar(expr);
    expr1 = conversion(expr1);
    cout << expr << endl;
    cout << expr1 << endl;

    expr = "68+52+12*/";
    cout << resolver(expr);
    //double to = 8/2;
    //cout << to;

    //expr = "(6 + 8 / (5 + 2) * 3";
    //ASSERT(evaluate(expr).error == true, "The function evaluate is not working");

    //expr = "(6 + 8) / (5 + 2) * 3 +";
    //ASSERT(evaluate(expr).error == true, "The function evaluate is not working");

    //expr = "(6 + 8) 10 / (5 + 2) * 3 +";
    //ASSERT(evaluate(expr).error == true, "The function evaluate is not working");

    return  0;
}
