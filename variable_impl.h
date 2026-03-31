#ifndef AUTOGRAD_VARIABLE_IMPL_H
#define AUTOGRAD_VARIABLE_IMPL_H

// Variable operator implementations
// This file must be included after both variable.h and graph.h are defined

template <typename T>
Variable<T> Variable<T>::operator+(const Variable& other) const
{
    if (this->_g != other.get_graph()){
        throw std::invalid_argument("Variables exist in different graphs");
    }

    Variable result( this->_value + other.get_value(), this->_g);
    if (this->_g != nullptr)
      this->_g->add_variable(result);

    return result;
}

template <typename T>
Variable<T> Variable<T>::operator-(const Variable& other) const
{
    if (this->_g != other.get_graph()){
        throw std::invalid_argument("Variables exist in different graphs");
    }

    Variable result( this->_value - other.get_value(), this->_g);
    if (this->_g != nullptr)
      this->_g->add_variable(result);

    return result;
}

template <typename T>
Variable<T> Variable<T>::operator*(const Variable& other) const
{
    if (this->_g != other.get_graph()){
        throw std::invalid_argument("Variables exist in different graphs");
    }

    Variable result( this->_value * other.get_value(), this->_g);

    if (this->_g != nullptr)
      this->_g->add_variable(result);

    return result;
}

template <typename T>
Variable<T> Variable<T>::operator/(const Variable& other) const
{
    if (std::abs(other.get_value()) < std::numeric_limits<T>::epsilon())
        throw std::invalid_argument("Division by zero or near-zero value");

    if (this->_g != other.get_graph()){
        throw std::invalid_argument("Variables exist in different graphs");
    }

    Variable result( this->_value / other.get_value(), this->_g);

    if (this->_g != nullptr)
      this->_g->add_variable(result);

    return result;
}

#endif // AUTOGRAD_VARIABLE_IMPL_H
