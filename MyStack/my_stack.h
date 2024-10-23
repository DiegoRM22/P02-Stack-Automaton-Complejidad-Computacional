
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