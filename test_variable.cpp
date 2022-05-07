#include <iostream>
/* #include "variable.h" */
#include "graph.h"


int main(){

  // Declare two doubles to get the true values of the operations
  const double a = 5.4, b = 3.2;
  const double a_plus_b = a + b;
  const double a_minus_b = a - b;
  const double a_times_b = a * b;
  const double a_divided_by_b = a / b;
  const double a_plus_constant_int = a + 5;
  const double a_minus_constant_int = a - 5;
  const double a_times_constant_int = a * 5;
  const double a_divided_by_constant_int = a / 5;
  const double a_plus_constant_double = a + 3.14;
  const double a_minus_constant_double = a - 3.14;
  const double a_times_constant_double = a * 3.14;
  const double a_divided_by_constant_double = a / 3.14;


  // Declare Variables to test the operations
  const Variable x(a);
  const Variable y(b);
  // Addition, Subtraction, Multiplication, Division between variables
  const Variable x_plus_y = x + y;
  const Variable x_minus_y = x - y;
  const Variable x_times_y = x * y;
  const Variable x_divided_by_y = x / y;
  // Addition, Subtraction, Multiplication, Division between variables and constants ints
  const Variable x_plus_constant_int = x + 5;
  const Variable x_minus_constant_int = x - 5;
  const Variable x_times_constant_int = x * 5;
  const Variable x_divided_by_constant_int = x / 5;
  // Addition, Subtraction, Multiplication, Division between variables and constants doubles
  const Variable x_plus_constant_double = x + 3.14;
  const Variable x_minus_constant_double = x - 3.14;
  const Variable x_times_constant_double = x * 3.14;
  const Variable x_divided_by_constant_double = x / 3.14;


  const std::string test_x_plus_y = x_plus_y == a_plus_b ? "OK" : "FAIL";
  const std::string test_x_minus_y = x_minus_y == a_minus_b ? "OK" : "FAIL";
  const std::string test_x_times_y = x_times_y == a_times_b ? "OK" : "FAIL";
  const std::string test_x_divided_by_y = x_divided_by_y == a_divided_by_b ? "OK" : "FAIL";
  const std::string test_x_plus_constant_int = x_plus_constant_int == a_plus_constant_int ? "OK" : "FAIL";
  const std::string test_x_minus_constant_int = x_minus_constant_int == a_minus_constant_int ? "OK" : "FAIL";
  const std::string test_x_times_constant_int = x_times_constant_int == a_times_constant_int ? "OK" : "FAIL";
  const std::string test_x_divided_by_constant_int = x_divided_by_constant_int == a_divided_by_constant_int ? "OK" : "FAIL";
  const std::string test_x_plus_constant_double = x_plus_constant_double == a_plus_constant_double ? "OK" : "FAIL";
  const std::string test_x_minus_constant_double = x_minus_constant_double == a_minus_constant_double ? "OK" : "FAIL";
  const std::string test_x_times_constant_double = x_times_constant_double == a_times_constant_double ? "OK" : "FAIL";
  const std::string test_x_divided_by_constant_double = x_divided_by_constant_double == a_divided_by_constant_double ? "OK" : "FAIL";
  const std::string test_comparison = x == a ? "OK" : "FAIL";
  const std::string combined_test = test_x_plus_y + " " + test_x_minus_y + " " +
     test_x_times_y + " " + test_x_divided_by_y + " " + test_x_plus_constant_int + " " +
     test_x_minus_constant_int + " " + test_x_times_constant_int + " " +
      test_x_divided_by_constant_int + " " + test_x_plus_constant_double + " " +
       test_x_minus_constant_double + " " + test_x_times_constant_double + " " +
        test_x_divided_by_constant_double + " " + test_comparison;

  std::cout << "Addition test between variables: " << test_x_plus_y << std::endl;
  std::cout << "x + y = " << x_plus_y << std::endl;

  std::cout << "Subtraction test between variables: " << test_x_minus_y << std::endl;
  std::cout << "x - y = " << x_minus_y << std::endl;

  std::cout << "Multiplication test between variables: " << test_x_times_y << std::endl;
  std::cout << "x * y = " << x_times_y << std::endl;

  std::cout << "Division test between variables: " << test_x_divided_by_y << std::endl;
  std::cout << "x / y = " << x_divided_by_y << std::endl;

  std::cout << "Addition test between variables and constants ints: " << 
    test_x_plus_constant_int << std::endl;
  std::cout << "x + 5 = " << x_plus_constant_int << std::endl;

  std::cout << "Subtraction test between variables and constants ints: " << 
    test_x_minus_constant_int << std::endl;
  std::cout << "x - 5 = " << x_minus_constant_int << std::endl;

  std::cout << "Multiplication test between variables and constants ints: " << 
    test_x_times_constant_int << std::endl;
  std::cout << "x * 5 = " << x_times_constant_int << std::endl;

  std::cout << "Division test between variables and constants ints: " << 
    test_x_divided_by_constant_int << std::endl;
  std::cout << "x / 5 = " << x_divided_by_constant_int << std::endl;

  std::cout << "Addition test between variables and constants doubles: " << 
    test_x_plus_constant_double << std::endl;
  std::cout << "x + 3.14 = " << x_plus_constant_double << std::endl;

  std::cout << "Subtraction test between variables and constants doubles: " << 
    test_x_minus_constant_double << std::endl;
  std::cout << "x - 3.14 = " << x_minus_constant_double << std::endl;

  std::cout << "Multiplication test between variables and constants doubles: " << 
    test_x_times_constant_double << std::endl;
  std::cout << "x * 3.14 = " << x_times_constant_double << std::endl;

  std::cout << "Division test between variables and constants doubles: " << 
    test_x_divided_by_constant_double << std::endl;
  std::cout << "x / 3.14 = " << x_divided_by_constant_double << std::endl;

  std::cout << "Comparison test between x and a: " << test_comparison << std::endl << std::endl;

  std::cout << "Full test: " << combined_test << std::endl;

  return 0;
}
