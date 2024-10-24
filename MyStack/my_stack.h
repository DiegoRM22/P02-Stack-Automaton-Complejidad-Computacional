/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Complejidad Computacional P02
  *
  * @author Diego Rodríguez Martín
  * @since 24-10-2024
  * @brief Implementación de la clase MyStack.
  *
*/

#include <iostream>
#include <stack>

#include "../Symbol/symbol.h"

#ifndef MY_STACK_H
#define MY_STACK_H

class MyStack {
 public:
  MyStack() {}
  void Push(Symbol c) { stack_.push(c); }
  void Pop() { stack_.pop(); }
  Symbol Top() const { return stack_.top(); }
  bool IsEmpty() const { return stack_.empty(); }
  void Print() const;
 private:
  std::stack<Symbol> stack_;
};

std::ostream& operator<<(std::ostream& os, const MyStack& stack);

#endif