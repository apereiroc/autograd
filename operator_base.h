#ifndef AUTOGRAD_OPERATOR_BASE_H
#define AUTOGRAD_OPERATOR_BASE_H


#include <string_view>
#include <utility>
#include "node.h"

//
// Operator
//

class Operator: public Node {
  public:

    Operator() = default;

    //-----------------------------------------------------------------------------
    // Name: get_name() const
    // Desc.: Returns the name of the operator
    //-----------------------------------------------------------------------------
    /* virtual std::string_view get_name() const override  */
    /* {  */
    /*   return "Operator";  */
    /* } */
};


#endif // AUTOGRAD_OPERATOR_BASE_H
