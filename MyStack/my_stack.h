
#include <iostream>
#include <stack>

#ifndef MY_STACK_H
#define MY_STACK_H

class MyStack {
 public:
  MyStack() {}
  void Push(char c) { stack_.push(c); }
  void Pop() { stack_.pop(); }
  char Top() const { return stack_.top(); }
  bool Empty() const { return stack_.empty(); }
  void Print() const;
 private:
  std::stack<char> stack_;

};

#endif