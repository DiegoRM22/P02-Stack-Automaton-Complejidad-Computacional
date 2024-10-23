#include "my_stack.h"

void MyStack::Print() const {
  std::stack<Symbol> stack = stack_;
  while (!stack.empty()) {
    std::cout << stack.top();
    stack.pop();
  }
}

std::ostream& operator<<(std::ostream& os, const MyStack& stack) {
  stack.Print();
  return os;
}