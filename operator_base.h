#ifndef AUTOGRAD_OPERATOR_BASE_H
#define AUTOGRAD_OPERATOR_BASE_H

#include <string_view>
#include <utility>
#include "node.h"

// Forward declarations
template <typename T>
class Variable;

//
// Operator Base Class
// Provides interface for backward pass gradient computation
//

class Operator: public Node {
  public:
    Operator() = default;
    virtual ~Operator() = default;

    // Compute gradients for operands given upstream gradient
    // Each concrete operator implements the chain rule for its operation
    virtual void backward(double upstream_gradient) = 0;

    // Get the output variable this operator produced
    virtual Variable<double>* get_output() = 0;
};


#endif // AUTOGRAD_OPERATOR_BASE_H
