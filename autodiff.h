#ifndef AUTOGRAD_AUTOGRAD_H
#define AUTOGRAD_AUTOGRAD_H

#include "graph.h"
#include "variable.h"
#include <memory>

// TODO: add documentation

class AutoDiff {
public:
  AutoDiff() : g(std::make_unique<Graph>()) {}

  // Old API (returns by value)
  template <typename T> Variable<T> variable(const T &value) {
    Variable x(value);
    g->add_variable(x);
    return x;
  }

  // New API (returns pointer for backward pass)
  Variable<double> *variable_ptr(double value) {
    auto var = std::make_unique<Variable<double>>(value);
    return g->add_variable_ptr(std::move(var));
  }

  void print_variables() { g->print_variables_for_debug(); }

  void print_operators() { g->print_operators_for_debug(); }

  // Run backward pass from a variable
  void backward(Variable<double> &root_var) { g->backward(root_var); }

  // Zero all gradients
  void zero_gradients() { g->zero_gradients(); }

private:
  std::unique_ptr<Graph> g;
};

#endif // AUTOGRAD_AUTOGRAD_H
