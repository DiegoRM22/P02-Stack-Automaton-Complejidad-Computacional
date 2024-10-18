#include "my_stack.h"

void MyStack::Print() const {
  std::stack<char> stack = stack_;
  while (!stack.empty()) {
    std::cout << stack.top();
    stack.pop();
  }
  std::cout << std::endl;
}