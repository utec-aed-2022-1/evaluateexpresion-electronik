#include <iostream>
#include "solution.h"
#include "tester.h"

using namespace std;


int main()
{
    string expr="";
    //expr = "5 + 8 / 2";
    
    //expr = "(7 + 8) / 2";

    //expr = "(6 + 8) / (5 + 2)";

    expr = "(6 + 8) / (5 + 2) * 12";

    expr = ordenar(expr);
    cout << expr;
    //expr = "(6 + 8 / (5 + 2) * 3";
    //ASSERT(evaluate(expr).error == true, "The function evaluate is not working");

    //expr = "(6 + 8) / (5 + 2) * 3 +";
    //ASSERT(evaluate(expr).error == true, "The function evaluate is not working");

    //expr = "(6 + 8) 10 / (5 + 2) * 3 +";
    //ASSERT(evaluate(expr).error == true, "The function evaluate is not working");

    return  0;
}
