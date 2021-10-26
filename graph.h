#ifndef AUTOGRAD_GRAPH_H
#define AUTOGRAD_GRAPH_H

#include <vector>
#include <iostream>
#include "node.h"
#include "operator_base.h"
#include "variable.h"

// TODO: add documentation

class Graph {
  public:
    Graph() : n_variables(0),
              n_operators(0)
    {}

    ~Graph() = default;

    void restart() {
      n_variables = 0;
      n_operators = 0;

      operators.clear();
      variables.clear();
    }

    /* template <class... Variables> */
    /* void add_variable(Variables&... vars){ */
    /*   (variables.push_back(vars), ...); */
    /*   (vars.set_graph(this), ...); */
    /*   n_variables += variables.size(); */
    /* } */

    void add_variable(Variable<>& var){
        variables.push_back(var);
        var.set_graph(this);
        n_variables += 1;
    }

    void add_operator( const Operator& op )
    {
      operators.push_back( op );
      n_operators++;
    }

    void print_variables_for_debug()
    {
      unsigned int i = 0;
      for ( auto& var : variables ) {
          i++;
          std::cout << "Var #" << i << ": " << var.get_value() << std::endl;
      }
    }

    void print_operators_for_debug()
    {
        std::cout << operators.size() << std::endl;
    }


  private:
    std::vector<Operator> operators;
    std::vector<Variable<>> variables;

    unsigned int n_variables;
    unsigned int n_operators;
};

#endif //AUTOGRAD_GRAPH_H
