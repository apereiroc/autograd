# Autograd

A lightweight, header-only C++ library for **automatic differentiation** using reverse-mode accumulation (backpropagation). Compute gradients of arbitrary mathematical expressions automatically without manual derivative calculations.

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Tests](https://img.shields.io/badge/tests-32%2F32%20passing-brightgreen.svg)](#testing)

## Table of Contents

- [What is Automatic Differentiation?](#what-is-automatic-differentiation)
- [Features](#features)
- [Quick Start](#quick-start)
- [Installation](#installation)
- [Usage Examples](#usage-examples)
- [API Reference](#api-reference)
- [Building and Testing](#building-and-testing)
- [How It Works](#how-it-works)
- [Limitations](#limitations)
- [Contributing](#contributing)
- [License](#license)

## What is Automatic Differentiation?

Automatic differentiation (autodiff) is a technique for efficiently computing derivatives of functions specified by computer programs. Unlike:

- **Symbolic differentiation**: No symbolic manipulation needed
- **Numerical differentiation**: No approximation errors, exact derivatives

This library uses **reverse-mode autodiff** (backpropagation) - the same technique that powers modern deep learning frameworks like PyTorch and TensorFlow.

### Use Cases

- **Machine Learning**: Training neural networks
- **Optimization**: Gradient-based optimization algorithms
- **Scientific Computing**: Sensitivity analysis, parameter estimation
- **Physics Simulations**: Computing Jacobians and Hessians

## Features

✅ **Automatic gradient computation** via backpropagation
✅ **Arithmetic operations**: `+`, `-`, `*`, `/`
✅ **Trigonometric functions**: `sin`, `cos`, `tan`
✅ **Chain rule handling**: Nested operations work automatically
✅ **Gradient accumulation**: Variables used multiple times handled correctly
✅ **Memory safe**: Smart pointers, RAII, no manual memory management
✅ **Exception-based error handling**: No silent failures
✅ **Comprehensive tests**: 32 tests covering all operations

## Quick Start

```cpp
#include "autodiff.h"
#include "variable_ptr_ops.h"

int main() {
    // Create autodiff instance
    AutoDiff ad;

    // Create variables
    auto* x = ad.variable_ptr(3.0);
    auto* y = ad.variable_ptr(4.0);

    // Forward pass: build computation graph
    auto* z = add(mul(x, y), x);  // z = x*y + x = 15

    // Backward pass: compute all gradients
    ad.backward(*z);

    // Access gradients
    std::cout << "z = " << z->get_value() << std::endl;           // 15.0
    std::cout << "∂z/∂x = " << x->get_gradient() << std::endl;    // 5.0
    std::cout << "∂z/∂y = " << y->get_gradient() << std::endl;    // 3.0

    return 0;
}
```

**Compile and run:**

```bash
g++ -std=c++17 -I. your_program.cpp -o your_program
./your_program
```

## Installation

This is a **header-only library**. No compilation or installation needed.

1. Clone or download the repository:

```bash
git clone https://github.com/yourusername/autograd.git
cd autograd
```

2. Include the headers in your project:

```cpp
#include "autodiff.h"
#include "variable_ptr_ops.h"
```

3. Compile with C++17:

```bash
g++ -std=c++17 -I/path/to/autograd your_program.cpp -o your_program
```

## Usage Examples

### Example 1: Basic Arithmetic Operations

```cpp
AutoDiff ad;
auto* x = ad.variable_ptr(5.0);
auto* y = ad.variable_ptr(2.0);

// z = (x + y) * (x - y) = x² - y²
auto* sum = add(x, y);
auto* diff = sub(x, y);
auto* z = mul(sum, diff);

ad.backward(*z);

std::cout << "z = " << z->get_value() << std::endl;        // 21.0
std::cout << "∂z/∂x = " << x->get_gradient() << std::endl; // 10.0 (= 2x)
std::cout << "∂z/∂y = " << y->get_gradient() << std::endl; // -4.0 (= -2y)
```

### Example 2: Trigonometric Functions

```cpp
AutoDiff ad;
auto* x = ad.variable_ptr(M_PI / 4);  // 45 degrees

// z = sin(x) * cos(x)
auto* sin_x = sin(x);
auto* cos_x = cos(x);
auto* z = mul(sin_x, cos_x);

ad.backward(*z);

// dz/dx = cos²(x) - sin²(x) = cos(2x)
std::cout << "∂z/∂x = " << x->get_gradient() << std::endl;
```

### Example 3: Chain Rule (Nested Functions)

```cpp
AutoDiff ad;
auto* x = ad.variable_ptr(2.0);

// z = sin(x²)
auto* x_squared = mul(x, x);
auto* z = sin(x_squared);

ad.backward(*z);

// dz/dx = cos(x²) * 2x
std::cout << "∂z/∂x = " << x->get_gradient() << std::endl;
```

### Example 4: Neural Network Neuron

```cpp
AutoDiff ad;

// Parameters (trainable)
auto* w1 = ad.variable_ptr(0.5);
auto* w2 = ad.variable_ptr(0.3);
auto* b = ad.variable_ptr(0.1);

// Inputs
auto* x1 = ad.variable_ptr(2.0);
auto* x2 = ad.variable_ptr(3.0);

// Forward pass: output = w1*x1 + w2*x2 + b
auto* term1 = mul(w1, x1);
auto* term2 = mul(w2, x2);
auto* sum = add(term1, term2);
auto* output = add(sum, b);

// Backward pass
ad.backward(*output);

// Gradients for gradient descent
std::cout << "∂output/∂w1 = " << w1->get_gradient() << std::endl;  // 2.0
std::cout << "∂output/∂w2 = " << w2->get_gradient() << std::endl;  // 3.0
std::cout << "∂output/∂b = " << b->get_gradient() << std::endl;    // 1.0

// Update weights (simple gradient descent)
// w1_new = w1 - learning_rate * gradient
```

### Example 5: Gradient Accumulation

```cpp
AutoDiff ad;
auto* x = ad.variable_ptr(3.0);

// z = x² (x appears twice)
auto* z = mul(x, x);

ad.backward(*z);

// Gradient accumulates from both uses: dz/dx = 2x
std::cout << "∂z/∂x = " << x->get_gradient() << std::endl;  // 6.0
```

## API Reference

### Core Classes

#### `AutoDiff`

Main interface for creating variables and running backward pass.

**Methods:**

- `Variable<double>* variable_ptr(double value)` - Create a new variable
- `void backward(Variable<double>& root)` - Compute gradients via backpropagation
- `void zero_gradients()` - Reset all gradients to zero

#### `Variable<T>`

Represents a scalar value with gradient tracking.

**Methods:**

- `const T& get_value() const` - Get the current value
- `const T& get_gradient() const` - Get the computed gradient
- `void set_gradient(const T& grad)` - Set gradient manually
- `void zero_gradient()` - Reset gradient to zero

### Operations

All operations are defined in `variable_ptr_ops.h`:

#### Arithmetic Operations

- `Variable<double>* add(Variable<double>* x, Variable<double>* y)` - Addition (x + y)
- `Variable<double>* sub(Variable<double>* x, Variable<double>* y)` - Subtraction (x - y)
- `Variable<double>* mul(Variable<double>* x, Variable<double>* y)` - Multiplication (x \* y)
- `Variable<double>* div(Variable<double>* x, Variable<double>* y)` - Division (x / y)

#### Trigonometric Operations

- `Variable<double>* sin(Variable<double>* x)` - Sine
- `Variable<double>* cos(Variable<double>* x)` - Cosine
- `Variable<double>* tan(Variable<double>* x)` - Tangent

### Gradient Rules

| Operation      | Formula    | Gradient                    |
| -------------- | ---------- | --------------------------- |
| Addition       | z = x + y  | ∂z/∂x = 1, ∂z/∂y = 1        |
| Subtraction    | z = x - y  | ∂z/∂x = 1, ∂z/∂y = -1       |
| Multiplication | z = x \* y | ∂z/∂x = y, ∂z/∂y = x        |
| Division       | z = x / y  | ∂z/∂x = 1/y, ∂z/∂y = -x/y²  |
| Sine           | z = sin(x) | ∂z/∂x = cos(x)              |
| Cosine         | z = cos(x) | ∂z/∂x = -sin(x)             |
| Tangent        | z = tan(x) | ∂z/∂x = sec²(x) = 1/cos²(x) |

## Building and Testing

### Compile Examples

```bash
# Compile backward pass example
g++ -std=c++17 -Wall -Wextra -pedantic -I. example_backward.cpp -o example_backward

# Run
./example_backward
```

### Run Tests

The library includes comprehensive test suites:

```bash
# Test arithmetic operations (10 tests)
g++ -std=c++17 -I. test_backward.cpp -o test_backward
./test_backward

# Test trigonometric operations (12 tests)
g++ -std=c++17 -I. test_trig.cpp -o test_trig
./test_trig

# Test variable operations (13 tests)
g++ -std=c++17 -I. test_variable.cpp -o test_variable
./test_variable

# Run comprehensive demo
g++ -std=c++17 -I. demo.cpp -o demo
./demo
```

### Testing

**Test Coverage:** 32/32 tests passing ✓

- ✅ Arithmetic operations (addition, subtraction, multiplication, division)
- ✅ Trigonometric operations (sin, cos, tan)
- ✅ Chain rule application
- ✅ Gradient accumulation
- ✅ Special values and edge cases
- ✅ Complex nested expressions
- ✅ Mathematical identities (Pythagorean, tan = sin/cos)

## How It Works

### Reverse-Mode Automatic Differentiation

The library implements backpropagation using a computation graph:

1. **Forward Pass**: Build computation graph

   ```cpp
   auto* x = ad.variable_ptr(3.0);
   auto* y = ad.variable_ptr(4.0);
   auto* z = mul(x, y);  // Graph tracks: z depends on x, y via multiplication
   ```

2. **Backward Pass**: Propagate gradients in reverse

   ```cpp
   ad.backward(*z);  // Start with dz/dz = 1, propagate backwards
   ```

3. **Chain Rule**: Automatically applied at each operation
   ```
   If z = f(y) and y = g(x), then:
   dz/dx = dz/dy * dy/dx
   ```

### Architecture

```
┌─────────────┐
│  AutoDiff   │  Main interface
└──────┬──────┘
       │
       ├──► Graph          Manages computation graph
       │      ├──► Variables    Stores values & gradients
       │      └──► Operators    Stores operations (AddOp, MulOp, etc.)
       │
       └──► backward()     Traverses graph in reverse, computes gradients
```

### Memory Management

- Uses `std::unique_ptr` for ownership
- Variables stored in graph with stable pointers
- RAII ensures automatic cleanup
- No manual memory management required

## Limitations

Current limitations (potential future enhancements):

- **Precision**: Only `double` precision supported
- **Operations**: Limited to basic arithmetic and trigonometric functions
- **Single output**: One root variable per backward pass
- **No higher-order derivatives**: Only first-order gradients
- **No GPU support**: CPU-only implementation
- **No broadcasting**: Scalar operations only

## Project Structure

```
autograd/
├── autodiff.h              # Main AutoDiff interface
├── graph.h                 # Computation graph implementation
├── variable.h              # Variable class definition
├── variable_impl.h         # Variable template implementations
├── operator_base.h         # Operator base class
├── operators.h             # Concrete operators (AddOp, MulOp, SinOp, etc.)
├── variable_ptr_ops.h      # Helper functions (add, mul, sin, etc.)
├── node.h                  # Base node class
├── example_backward.cpp    # Working example
├── demo.cpp                # Comprehensive demonstration
├── test_backward.cpp       # Arithmetic operation tests
├── test_trig.cpp           # Trigonometric operation tests
├── test_variable.cpp       # Variable operation tests
├── test_graph.cpp          # Graph management tests
├── test_autodiff.cpp       # AutoDiff interface tests
├── QUICK_START.md          # Quick start guide
└── IMPLEMENTATION_SUMMARY.md  # Technical details
```

## Contributing

Contributions welcome! Areas for enhancement:

- [ ] Additional operations (exp, log, pow, sqrt)
- [ ] Matrix/tensor operations
- [ ] Higher-order derivatives
- [ ] GPU acceleration
- [ ] Sparse gradients
- [ ] Optimization algorithms (SGD, Adam, etc.)
- [ ] Better error messages
- [ ] Performance optimizations

## License

[Specify your license here - MIT, Apache 2.0, etc.]

## Acknowledgments

Inspired by modern automatic differentiation libraries:

- PyTorch's autograd
- TensorFlow's GradientTape
- JAX

Built from scratch in C++ for educational purposes and practical use in C++ projects requiring gradient computation.

---

**Author**: [Your name]
**Repository**: [Your repo URL]
**Documentation**: See [QUICK_START.md](QUICK_START.md) for more examples
