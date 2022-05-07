#ifndef AUTOGRAD_AUTOGRAD_H
#define AUTOGRAD_AUTOGRAD_H

#include <memory>
#include "graph.h"
#include "variable.h"

// TODO: add documentation

class AutoDiff {
  public:
    AutoDiff()
        : g(std::make_unique<Graph>())
    {}
    

    /* void restart_graph() */
    /* { */
    /*   g->restart(); */
    /*   delete g; */
    /*   g = new Graph(); */
    /*   std::cout << "Graph restarted." << std::endl; */
    /* } */

    template <typename T>
    Variable<T> variable(const T& value) {
      Variable x(value);
      g->add_variable(x);
      return x;
    }

    void print_variables() {
      g->print_variables_for_debug();
    }

    void print_operators() {
      g->print_operators_for_debug();
    }

private:
    std::unique_ptr<Graph> g;
};







// class Autograd{
//   public:
//     Autograd();
//     ~Autograd();
//     Variable variable();
//     Variable variable(double y);
//     void print();
//   private:
//     Graph* g;
// };

#endif //AUTOGRAD_AUTOGRAD_H
