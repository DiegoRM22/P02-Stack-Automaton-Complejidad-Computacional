#include <iostream>

#include "../Alphabet/alphabet.h"
#include "../State/state.h"
#include "../MyStack/my_stack.h"


#ifndef STACK_AUTOMATON_H
#define STACK_AUTOMATON_H

class StackAutomaton {
 public:
  StackAutomaton(std::string fileName);
 private:
  std::set<State> states_;
  Alphabet alphabet_;
  Alphabet stackAlphabet_;
  State initialState_;
  std::set<State> acceptingStates_;
  MyStack stack_;
};

#endif