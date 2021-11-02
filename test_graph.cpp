#include <iostream>
#include <memory>
#include "graph.h"
#include "variable.h"

int main(){

  std::unique_ptr<Graph> g = std::make_unique<Graph>();

    auto x = Variable(5.4);
    auto y = Variable(-3.4);

    /* g->add_variable(x); */
    /* g->add_variable(y); */
    g->add_variable(x,y );

    std::cout << "Before creating z:" << std::endl;

    g->print_variables_for_debug();

    [[maybe_unused]] Variable z = x + y;

    std::cout << "\nAfter creating z:" << std::endl;

    g->print_variables_for_debug();

    return 0;
}
