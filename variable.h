#ifndef AUTOGRAD_VARIABLE_H
#define AUTOGRAD_VARIABLE_H

#include "node.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

// Forward declaration to avoid circular dependency
class Graph;

template <typename T = double> class Variable : public Node {
public:
  Variable(const T &value) : _value(value), _gradient(0), _g(nullptr) {}

  Variable(const T &value, Graph *g) : _value(value), _gradient(0), _g(g) {}

  void set_value(const T &value) { _value = value; }

  const T &get_value() const { return _value; }

  void set_gradient(const T &grad) { _gradient = grad; }

  const T &get_gradient() const { return _gradient; }

  void add_gradient(const T &grad) { _gradient += grad; }

  void zero_gradient() { _gradient = 0; }

  void set_graph(Graph *g) { _g = g; }

  const Graph *get_graph() const { return _g; }

  // Operator declarations - implementations at end of file
  Variable operator+(const Variable &other) const;
  Variable operator-(const Variable &other) const;
  Variable operator*(const Variable &other) const;
  Variable operator/(const Variable &other) const;

  bool operator==(const Variable &other) const {
    return this->_value == other.get_value();
  }

  bool operator!=(const Variable &other) const {
    return this->_value != other.get_value();
  }

  bool operator==(const T &other) const { return this->get_value() == other; }

  // TODO: implement more operators

  friend std::ostream &operator<<(std::ostream &os, const Variable &var) {
    os << var.get_value();
    return os;
  }

private:
  T _value;
  T _gradient;
  Graph *_g;
};

#endif // AUTOGRAD_VARIABLE_H
