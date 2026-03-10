#ifndef AUTOGRAD_VARIABLE_PTR_OPS_H
#define AUTOGRAD_VARIABLE_PTR_OPS_H

// Pointer-based variable operations that create operator objects for backward pass
// These functions work with Variable* instead of Variable& to enable gradient tracking

#include "variable.h"
#include "graph.h"
#include "operators.h"
#include <memory>

// Addition: z = x + y
inline Variable<double>* add(Variable<double>* left, Variable<double>* right) {
    if (left->get_graph() != right->get_graph()) {
        throw std::invalid_argument("Variables exist in different graphs");
    }

    Graph* g = const_cast<Graph*>(static_cast<const Graph*>(left->get_graph()));

    // Create result variable
    auto result = std::make_unique<Variable<double>>(
        left->get_value() + right->get_value()
    );
    Variable<double>* result_ptr = g->add_variable_ptr(std::move(result));

    // Create and register operator
    auto op = std::make_unique<AddOp>(left, right, result_ptr);
    g->add_operator(std::move(op));

    return result_ptr;
}

// Subtraction: z = x - y
inline Variable<double>* sub(Variable<double>* left, Variable<double>* right) {
    if (left->get_graph() != right->get_graph()) {
        throw std::invalid_argument("Variables exist in different graphs");
    }

    Graph* g = const_cast<Graph*>(static_cast<const Graph*>(left->get_graph()));

    // Create result variable
    auto result = std::make_unique<Variable<double>>(
        left->get_value() - right->get_value()
    );
    Variable<double>* result_ptr = g->add_variable_ptr(std::move(result));

    // Create and register operator
    auto op = std::make_unique<SubOp>(left, right, result_ptr);
    g->add_operator(std::move(op));

    return result_ptr;
}

// Multiplication: z = x * y
inline Variable<double>* mul(Variable<double>* left, Variable<double>* right) {
    if (left->get_graph() != right->get_graph()) {
        throw std::invalid_argument("Variables exist in different graphs");
    }

    Graph* g = const_cast<Graph*>(static_cast<const Graph*>(left->get_graph()));

    // Create result variable
    auto result = std::make_unique<Variable<double>>(
        left->get_value() * right->get_value()
    );
    Variable<double>* result_ptr = g->add_variable_ptr(std::move(result));

    // Create and register operator
    auto op = std::make_unique<MulOp>(left, right, result_ptr);
    g->add_operator(std::move(op));

    return result_ptr;
}

// Division: z = x / y
inline Variable<double>* div(Variable<double>* left, Variable<double>* right) {
    if (std::abs(right->get_value()) < std::numeric_limits<double>::epsilon()) {
        throw std::invalid_argument("Division by zero or near-zero value");
    }

    if (left->get_graph() != right->get_graph()) {
        throw std::invalid_argument("Variables exist in different graphs");
    }

    Graph* g = const_cast<Graph*>(static_cast<const Graph*>(left->get_graph()));

    // Create result variable
    auto result = std::make_unique<Variable<double>>(
        left->get_value() / right->get_value()
    );
    Variable<double>* result_ptr = g->add_variable_ptr(std::move(result));

    // Create and register operator
    auto op = std::make_unique<DivOp>(left, right, result_ptr);
    g->add_operator(std::move(op));

    return result_ptr;
}

// Sine: z = sin(x)
inline Variable<double>* sin(Variable<double>* input) {
    if (!input->get_graph()) {
        throw std::invalid_argument("Variable must belong to a graph");
    }

    Graph* g = const_cast<Graph*>(static_cast<const Graph*>(input->get_graph()));

    // Create result variable
    auto result = std::make_unique<Variable<double>>(
        std::sin(input->get_value())
    );
    Variable<double>* result_ptr = g->add_variable_ptr(std::move(result));

    // Create and register operator
    auto op = std::make_unique<SinOp>(input, result_ptr);
    g->add_operator(std::move(op));

    return result_ptr;
}

// Cosine: z = cos(x)
inline Variable<double>* cos(Variable<double>* input) {
    if (!input->get_graph()) {
        throw std::invalid_argument("Variable must belong to a graph");
    }

    Graph* g = const_cast<Graph*>(static_cast<const Graph*>(input->get_graph()));

    // Create result variable
    auto result = std::make_unique<Variable<double>>(
        std::cos(input->get_value())
    );
    Variable<double>* result_ptr = g->add_variable_ptr(std::move(result));

    // Create and register operator
    auto op = std::make_unique<CosOp>(input, result_ptr);
    g->add_operator(std::move(op));

    return result_ptr;
}

// Tangent: z = tan(x)
inline Variable<double>* tan(Variable<double>* input) {
    if (!input->get_graph()) {
        throw std::invalid_argument("Variable must belong to a graph");
    }

    Graph* g = const_cast<Graph*>(static_cast<const Graph*>(input->get_graph()));

    // Create result variable
    auto result = std::make_unique<Variable<double>>(
        std::tan(input->get_value())
    );
    Variable<double>* result_ptr = g->add_variable_ptr(std::move(result));

    // Create and register operator
    auto op = std::make_unique<TanOp>(input, result_ptr);
    g->add_operator(std::move(op));

    return result_ptr;
}

#endif // AUTOGRAD_VARIABLE_PTR_OPS_H
