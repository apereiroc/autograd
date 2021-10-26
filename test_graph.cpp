#include "graph.h"
#include "variable.h"
#include <iostream>

int main(){

    Graph* g = new Graph();

    auto x = Variable(5.4);
    auto y = Variable(-3.4);

    g->add_variable(x);
    g->add_variable(y);

    std::cout << "Before creating z:" << std::endl;

    g->print_variables_for_debug();

    Variable z = x + y;

    std::cout << "\nAfter creating z:" << std::endl;

    g->print_variables_for_debug();

    delete g;

    return 0;
}
