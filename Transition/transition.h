#include <iostream>
#include <stack>
#include <vector>

#include "../Symbol/symbol.h"


#ifndef TRANSITION_H
#define TRANSITION_H

class Transition {
 public:
  Transition(std::string fromState, std::string toState, Symbol stringSymbol, Symbol stackSymbol, std::vector<Symbol> addToStack)
      : fromState_(fromState), toState_(toState), stringSymbol_(stringSymbol), stackSymbol_(stackSymbol), addToStack_(addToStack) {}
  std::string GetFromState() const { return fromState_; }
  std::string GetToState() const { return toState_; }
  Symbol GetStringSymbol() const { return stringSymbol_; }
  Symbol GetStackSymbol() const { return stackSymbol_; }
  std::vector<Symbol> GetAddToStack() const { return addToStack_; }
  void SetFromState(std::string fromState) { fromState_ = fromState; }
  void SetToState(std::string toState) { toState_ = toState; }
  void SetStringSymbol(Symbol stringSymbol) { stringSymbol_ = stringSymbol; }
  void SetStackSymbol(Symbol stackSymbol) { stackSymbol_ = stackSymbol; }
  void SetAddToStack(std::vector<Symbol> addToStack) { addToStack_ = addToStack; }

  bool operator==(const Transition& other) const {
    return fromState_ == other.GetFromState() && toState_ == other.GetToState() && stringSymbol_ == other.GetStringSymbol() && stackSymbol_ == other.GetStackSymbol();
  }

 private:
  std::string fromState_;
  std::string toState_;
  Symbol stringSymbol_;
  Symbol stackSymbol_;
  std::vector<Symbol> addToStack_;
};

std::ostream& operator<<(std::ostream& os, const Transition& transition);

#endif