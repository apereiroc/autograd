#include <iostream>
#include <cmath>
#include <string>
#include "autodiff.h"
#include "variable_ptr_ops.h"

// Test helper
bool approx_equal(double a, double b, double epsilon = 1e-6) {
    return std::abs(a - b) < epsilon;
}

void print_test_result(const std::string& test_name, bool passed) {
    std::cout << test_name << ": " << (passed ? "PASS" : "FAIL") << std::endl;
}

// Test 1: Simple sine derivative d(sin(x))/dx = cos(x)
bool test_sin_derivative() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(M_PI / 4);  // 45 degrees
    auto* y = sin(x);  // sin(π/4) = √2/2

    ad.backward(*y);

    // dy/dx = cos(π/4) = √2/2 ≈ 0.707107
    double expected = std::cos(M_PI / 4);
    return approx_equal(x->get_gradient(), expected) &&
           approx_equal(y->get_value(), std::sin(M_PI / 4));
}

// Test 2: Simple cosine derivative d(cos(x))/dx = -sin(x)
bool test_cos_derivative() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(M_PI / 3);  // 60 degrees
    auto* y = cos(x);  // cos(π/3) = 0.5

    ad.backward(*y);

    // dy/dx = -sin(π/3) = -√3/2 ≈ -0.866025
    double expected = -std::sin(M_PI / 3);
    return approx_equal(x->get_gradient(), expected) &&
           approx_equal(y->get_value(), std::cos(M_PI / 3));
}

// Test 3: Simple tangent derivative d(tan(x))/dx = sec²(x)
bool test_tan_derivative() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(M_PI / 6);  // 30 degrees
    auto* y = tan(x);  // tan(π/6) = 1/√3

    ad.backward(*y);

    // dy/dx = sec²(π/6) = 1/cos²(π/6) = 4/3
    double cos_x = std::cos(M_PI / 6);
    double expected = 1.0 / (cos_x * cos_x);
    return approx_equal(x->get_gradient(), expected) &&
           approx_equal(y->get_value(), std::tan(M_PI / 6));
}

// Test 4: Chain rule with sin: z = sin(2x)
bool test_sin_chain_rule() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(M_PI / 8);
    auto* two_x = mul(ad.variable_ptr(2.0), x);  // 2x
    auto* z = sin(two_x);  // sin(2x)

    ad.backward(*z);

    // dz/dx = cos(2x) * 2
    double expected = std::cos(2.0 * M_PI / 8) * 2.0;
    return approx_equal(x->get_gradient(), expected);
}

// Test 5: Product of trig functions: z = sin(x) * cos(x)
bool test_sin_cos_product() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(M_PI / 6);
    auto* s = sin(x);
    auto* c = cos(x);
    auto* z = mul(s, c);  // sin(x) * cos(x)

    ad.backward(*z);

    // dz/dx = cos(x) * cos(x) + sin(x) * (-sin(x))
    //       = cos²(x) - sin²(x)
    //       = cos(2x)
    double sin_x = std::sin(M_PI / 6);
    double cos_x = std::cos(M_PI / 6);
    double expected = cos_x * cos_x - sin_x * sin_x;
    return approx_equal(x->get_gradient(), expected);
}

// Test 6: Composite function: z = sin(x²)
bool test_sin_of_square() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(2.0);
    auto* x_squared = mul(x, x);  // x²
    auto* z = sin(x_squared);     // sin(x²)

    ad.backward(*z);

    // dz/dx = cos(x²) * 2x
    double x_val = 2.0;
    double expected = std::cos(x_val * x_val) * 2.0 * x_val;
    return approx_equal(x->get_gradient(), expected);
}

// Test 7: tan(x) = sin(x) / cos(x) identity check
bool test_tan_identity() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(M_PI / 5);

    // Compute tan(x) directly
    auto* tan_x = tan(x);
    ad.backward(*tan_x);
    double grad_direct = x->get_gradient();

    // Reset and compute sin(x)/cos(x)
    AutoDiff ad2;
    auto* x2 = ad2.variable_ptr(M_PI / 5);
    auto* sin_x = sin(x2);
    auto* cos_x = cos(x2);
    auto* tan_x2 = div(sin_x, cos_x);
    ad2.backward(*tan_x2);
    double grad_identity = x2->get_gradient();

    // Both should give same gradient
    return approx_equal(grad_direct, grad_identity) &&
           approx_equal(tan_x->get_value(), tan_x2->get_value());
}

// Test 8: sin at special angles
bool test_sin_special_angles() {
    AutoDiff ad;

    // sin(0) = 0
    auto* x1 = ad.variable_ptr(0.0);
    auto* y1 = sin(x1);
    ad.backward(*y1);
    bool test1 = approx_equal(y1->get_value(), 0.0) &&
                 approx_equal(x1->get_gradient(), 1.0);  // cos(0) = 1

    // sin(π/2) = 1
    AutoDiff ad2;
    auto* x2 = ad2.variable_ptr(M_PI / 2);
    auto* y2 = sin(x2);
    ad2.backward(*y2);
    bool test2 = approx_equal(y2->get_value(), 1.0) &&
                 approx_equal(x2->get_gradient(), 0.0, 1e-5);  // cos(π/2) = 0

    return test1 && test2;
}

// Test 9: cos at special angles
bool test_cos_special_angles() {
    AutoDiff ad;

    // cos(0) = 1
    auto* x1 = ad.variable_ptr(0.0);
    auto* y1 = cos(x1);
    ad.backward(*y1);
    bool test1 = approx_equal(y1->get_value(), 1.0) &&
                 approx_equal(x1->get_gradient(), 0.0);  // -sin(0) = 0

    // cos(π) = -1
    AutoDiff ad2;
    auto* x2 = ad2.variable_ptr(M_PI);
    auto* y2 = cos(x2);
    ad2.backward(*y2);
    bool test2 = approx_equal(y2->get_value(), -1.0) &&
                 approx_equal(x2->get_gradient(), 0.0, 1e-5);  // -sin(π) = 0

    return test1 && test2;
}

// Test 10: Complex expression with trig: z = sin(x) + cos(y)
bool test_mixed_trig() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(M_PI / 4);
    auto* y = ad.variable_ptr(M_PI / 3);
    auto* sin_x = sin(x);
    auto* cos_y = cos(y);
    auto* z = add(sin_x, cos_y);

    ad.backward(*z);

    // dz/dx = cos(π/4)
    // dz/dy = -sin(π/3)
    double expected_dx = std::cos(M_PI / 4);
    double expected_dy = -std::sin(M_PI / 3);

    return approx_equal(x->get_gradient(), expected_dx) &&
           approx_equal(y->get_gradient(), expected_dy);
}

// Test 11: Nested trig: z = sin(cos(x))
bool test_nested_trig() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(M_PI / 4);
    auto* cos_x = cos(x);
    auto* z = sin(cos_x);  // sin(cos(x))

    ad.backward(*z);

    // dz/dx = cos(cos(x)) * (-sin(x))
    double x_val = M_PI / 4;
    double expected = std::cos(std::cos(x_val)) * (-std::sin(x_val));

    return approx_equal(x->get_gradient(), expected);
}

// Test 12: Pythagorean identity: sin²(x) + cos²(x)
bool test_pythagorean_identity() {
    AutoDiff ad;
    auto* x = ad.variable_ptr(M_PI / 7);
    auto* sin_x = sin(x);
    auto* cos_x = cos(x);
    auto* sin2 = mul(sin_x, sin_x);
    auto* cos2 = mul(cos_x, cos_x);
    auto* z = add(sin2, cos2);  // Should equal 1

    ad.backward(*z);

    // sin²(x) + cos²(x) = 1 (always)
    // dz/dx = 2sin(x)cos(x) + 2cos(x)(-sin(x)) = 0
    return approx_equal(z->get_value(), 1.0) &&
           approx_equal(x->get_gradient(), 0.0, 1e-5);
}

int main() {
    std::cout << "=== Autograd Trigonometric Operations Tests ===" << std::endl << std::endl;

    int passed = 0;
    int total = 12;

    print_test_result("Test 1: sin derivative", test_sin_derivative());
    if (test_sin_derivative()) passed++;

    print_test_result("Test 2: cos derivative", test_cos_derivative());
    if (test_cos_derivative()) passed++;

    print_test_result("Test 3: tan derivative", test_tan_derivative());
    if (test_tan_derivative()) passed++;

    print_test_result("Test 4: sin chain rule", test_sin_chain_rule());
    if (test_sin_chain_rule()) passed++;

    print_test_result("Test 5: sin*cos product", test_sin_cos_product());
    if (test_sin_cos_product()) passed++;

    print_test_result("Test 6: sin(x²)", test_sin_of_square());
    if (test_sin_of_square()) passed++;

    print_test_result("Test 7: tan identity", test_tan_identity());
    if (test_tan_identity()) passed++;

    print_test_result("Test 8: sin special angles", test_sin_special_angles());
    if (test_sin_special_angles()) passed++;

    print_test_result("Test 9: cos special angles", test_cos_special_angles());
    if (test_cos_special_angles()) passed++;

    print_test_result("Test 10: mixed trig", test_mixed_trig());
    if (test_mixed_trig()) passed++;

    print_test_result("Test 11: nested trig", test_nested_trig());
    if (test_nested_trig()) passed++;

    print_test_result("Test 12: Pythagorean identity", test_pythagorean_identity());
    if (test_pythagorean_identity()) passed++;

    std::cout << std::endl;
    std::cout << "Results: " << passed << "/" << total << " tests passed" << std::endl;

    if (passed == total) {
        std::cout << "\n✓ All trigonometric tests passed!" << std::endl;
    } else {
        std::cout << "\n✗ Some tests failed!" << std::endl;
    }

    return (passed == total) ? 0 : 1;
}
