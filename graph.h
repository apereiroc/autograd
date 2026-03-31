#ifndef AUTOGRAD_GRAPH_H
#define AUTOGRAD_GRAPH_H

#include "node.h"
#include "operator_base.h"
#include "variable.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

// TODO: add documentation

class Graph {
public:
  Graph() : n_variables(0), n_operators(0) {}

  ~Graph() = default;

  void restart() {
    n_variables = 0;
    n_operators = 0;

    operator_ptrs.clear();
    variable_ptrs.clear();
    variables.clear();
  }

  // Add variable by value (old API for compatibility)
  void add_variable(Variable<> &var) {
    variables.push_back(var);
    variables.back().set_graph(this);
    n_variables++;
  }

  // Add variable by unique_ptr (new API for backward pass)
  Variable<double> *add_variable_ptr(std::unique_ptr<Variable<double>> var) {
    var->set_graph(this);
    Variable<double> *ptr = var.get();
    variable_ptrs.push_back(std::move(var));
    n_variables++;
    return ptr;
  }

  template <class... Variables>
  void add_variable(Variable<> &var, Variables &...vars) {
    add_variable(var);
    add_variable(vars...);
  }

  void add_operator(std::unique_ptr<Operator> op) {
    operator_ptrs.push_back(std::move(op));
    n_operators++;
  }

  void print_variables_for_debug() {
    unsigned int i = 0;
    for (auto &var : variables) {
      std::cout << "Var #" << ++i << ": " << var.get_value() << std::endl;
    }
  }

  void print_operators_for_debug() {
    std::cout << operator_ptrs.size() << std::endl;
  }

  // Zero all gradients before a new backward pass
  void zero_gradients() {
    for (auto &var_ptr : variable_ptrs) {
      var_ptr->zero_gradient();
    }
  }

  // Topological sort for backward pass
  // Returns operators in reverse topological order (ready for backward pass)
  std::vector<Operator *> topological_sort() {
    // For now, use simple reverse order of creation
    // This works because operators are added in forward pass order
    std::vector<Operator *> sorted;
    sorted.reserve(operator_ptrs.size());

    for (auto &op : operator_ptrs) {
      sorted.push_back(op.get());
    }

    // Reverse to get backward pass order
    std::reverse(sorted.begin(), sorted.end());
    return sorted;
  }

  // Run backward pass from a root variable
  void backward(Variable<double> &root_var) {
    // 1. Zero all gradients
    zero_gradients();

    // 2. Set gradient of root to 1.0 (dL/dL = 1)
    root_var.set_gradient(1.0);

    // 3. Get operators in reverse topological order
    auto sorted_ops = topological_sort();

    // 4. Backward pass: propagate gradients
    for (Operator *op : sorted_ops) {
      Variable<double> *output = op->get_output();
      double upstream_grad = output->get_gradient();

      // Propagate gradient to operands
      op->backward(upstream_grad);
    }
  }

private:
  // Old storage (for compatibility with existing tests)
  std::vector<Variable<>> variables;

  // New pointer-based storage (for backward pass)
  std::vector<std::unique_ptr<Operator>> operator_ptrs;
  std::vector<std::unique_ptr<Variable<double>>> variable_ptrs;

  unsigned int n_variables;
  unsigned int n_operators;
};

// Include variable operator implementations after Graph is fully defined
#include "variable_impl.h"

#endif // AUTOGRAD_GRAPH_H
