#ifndef AUTOGRAD_OPERATORS_H
#define AUTOGRAD_OPERATORS_H

#include "operator_base.h"
#include "variable.h"
#include <cmath>

// Concrete operator implementations for automatic differentiation
// Each operator stores pointers to its operands and implements the chain rule

//
// Addition Operator: z = x + y
// Gradients: dL/dx = dL/dz * 1, dL/dy = dL/dz * 1
//
class AddOp : public Operator {
  public:
    AddOp(Variable<double>* left, Variable<double>* right, Variable<double>* output)
        : _left(left), _right(right), _output(output) {}

    void backward(double upstream_gradient) override {
        if (_left) _left->add_gradient(upstream_gradient * 1.0);
        if (_right) _right->add_gradient(upstream_gradient * 1.0);
    }

    Variable<double>* get_output() override { return _output; }

  private:
    Variable<double>* _left;
    Variable<double>* _right;
    Variable<double>* _output;
};

//
// Subtraction Operator: z = x - y
// Gradients: dL/dx = dL/dz * 1, dL/dy = dL/dz * (-1)
//
class SubOp : public Operator {
  public:
    SubOp(Variable<double>* left, Variable<double>* right, Variable<double>* output)
        : _left(left), _right(right), _output(output) {}

    void backward(double upstream_gradient) override {
        if (_left) _left->add_gradient(upstream_gradient * 1.0);
        if (_right) _right->add_gradient(upstream_gradient * -1.0);
    }

    Variable<double>* get_output() override { return _output; }

  private:
    Variable<double>* _left;
    Variable<double>* _right;
    Variable<double>* _output;
};

//
// Multiplication Operator: z = x * y
// Gradients: dL/dx = dL/dz * y, dL/dy = dL/dz * x
//
class MulOp : public Operator {
  public:
    MulOp(Variable<double>* left, Variable<double>* right, Variable<double>* output)
        : _left(left), _right(right), _output(output) {}

    void backward(double upstream_gradient) override {
        if (_left) _left->add_gradient(upstream_gradient * _right->get_value());
        if (_right) _right->add_gradient(upstream_gradient * _left->get_value());
    }

    Variable<double>* get_output() override { return _output; }

  private:
    Variable<double>* _left;
    Variable<double>* _right;
    Variable<double>* _output;
};

//
// Division Operator: z = x / y
// Gradients: dL/dx = dL/dz * (1/y), dL/dy = dL/dz * (-x/y²)
//
class DivOp : public Operator {
  public:
    DivOp(Variable<double>* left, Variable<double>* right, Variable<double>* output)
        : _left(left), _right(right), _output(output) {}

    void backward(double upstream_gradient) override {
        double y = _right->get_value();
        double x = _left->get_value();

        if (_left) _left->add_gradient(upstream_gradient * (1.0 / y));
        if (_right) _right->add_gradient(upstream_gradient * (-x / (y * y)));
    }

    Variable<double>* get_output() override { return _output; }

  private:
    Variable<double>* _left;
    Variable<double>* _right;
    Variable<double>* _output;
};

//
// Sine Operator: z = sin(x)
// Gradient: dL/dx = dL/dz * cos(x)
//
class SinOp : public Operator {
  public:
    SinOp(Variable<double>* input, Variable<double>* output)
        : _input(input), _output(output) {}

    void backward(double upstream_gradient) override {
        if (_input) {
            // d(sin(x))/dx = cos(x)
            double grad = upstream_gradient * std::cos(_input->get_value());
            _input->add_gradient(grad);
        }
    }

    Variable<double>* get_output() override { return _output; }

  private:
    Variable<double>* _input;
    Variable<double>* _output;
};

//
// Cosine Operator: z = cos(x)
// Gradient: dL/dx = dL/dz * (-sin(x))
//
class CosOp : public Operator {
  public:
    CosOp(Variable<double>* input, Variable<double>* output)
        : _input(input), _output(output) {}

    void backward(double upstream_gradient) override {
        if (_input) {
            // d(cos(x))/dx = -sin(x)
            double grad = upstream_gradient * (-std::sin(_input->get_value()));
            _input->add_gradient(grad);
        }
    }

    Variable<double>* get_output() override { return _output; }

  private:
    Variable<double>* _input;
    Variable<double>* _output;
};

//
// Tangent Operator: z = tan(x)
// Gradient: dL/dx = dL/dz * sec²(x) = dL/dz * (1/cos²(x))
//
class TanOp : public Operator {
  public:
    TanOp(Variable<double>* input, Variable<double>* output)
        : _input(input), _output(output) {}

    void backward(double upstream_gradient) override {
        if (_input) {
            // d(tan(x))/dx = sec²(x) = 1/cos²(x)
            double cos_x = std::cos(_input->get_value());
            double grad = upstream_gradient / (cos_x * cos_x);
            _input->add_gradient(grad);
        }
    }

    Variable<double>* get_output() override { return _output; }

  private:
    Variable<double>* _input;
    Variable<double>* _output;
};

#endif // AUTOGRAD_OPERATORS_H
