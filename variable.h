#ifndef VARIABLE_H
#define VARIABLE_H

#include <cstddef>
#include "node.h"
#include "graph.h"

//TODO: add documentation
class Graph;

template <typename T = double>
class Variable : public Node {
  public:
    //Variable() { _value = 0; }

    Variable(const T& value)
    : _value(value),
      _g(nullptr)
    {}

    Variable(const T& value, Graph *g)
    : _value(value),
      _g(g)
    {}

    void set_value(const T& value) { _value = value; }

    const T& get_value() const { return _value; }

    void set_graph(Graph* g) {_g = g ;}

    const Graph* get_graph() const { return _g; }

    Variable operator+(const Variable& other) const
    {
        if (this->_g != other.get_graph()){
            std::cout << "ERROR: variables exist in different graphs" << std::endl;
            exit(1);
        }

        Variable result( this->_value + other.get_value(), this->_g);
        this->_g->add_variable(result);

        return result;
    }

    Variable operator-(const Variable& other) const
    {
      if (this->_g != other.get_graph()){
          std::cout << "ERROR: variables exist in different graphs" << std::endl;
          exit(1);
      }

      Variable result( this->_value - other.get_value(), this->_g);
      this->_g->add_variable(result);

      return result;
    }

    Variable operator*(const Variable& other) const
    {
      if (this->_g != other.get_graph()){
          std::cout << "ERROR: variables exist in different graphs" << std::endl;
          exit(1);
      }

      Variable result( this->_value * other.get_value(), this->_g);
      this->_g->add_variable(result);

      return result;
    }

    Variable operator/(const Variable& other) const
    {
      if (other.get_value() == 0)
          throw std::runtime_error("Division by 0");
      
      if (this->_g != other.get_graph()){
          std::cout << "ERROR: variables exist in different graphs" << std::endl;
          exit(1);
      }

      Variable result( this->_value / other.get_value() );
      this->_g->add_variable(result);
      
      return result;
    }

    bool operator==(const Variable& other) const
    {
        return this->_value == other.get_value();
    }

    bool operator!=(const Variable& other) const
    {
        return this->_value != other.get_value();
    }

    bool operator==(const T& other) const
    {
        return this->get_value() == other;
    }

    //TODO: implement more operators

    friend std::ostream& operator<<(std::ostream& os, Variable var){
      os << var.get_value();
      return os;
    }

  private:
    T _value;
    Graph* _g;
};

#endif // VARIABLE_H
