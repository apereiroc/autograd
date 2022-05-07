#include <iostream>
#include "autodiff.h"
#include "variable.h"

int main(){

  AutoDiff ad;


  Variable x = ad.variable(5.8);
  
  
  Variable y = ad.variable(-3.9);

  ad.print_variables();

  [[maybe_unused]]const auto z = x*y;

  ad.print_variables();

  return 0;
}
