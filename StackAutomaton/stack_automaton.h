#include <iostream>
#include <set>
#include <string>
#include "../Alphabet/alphabet.h"
#include "../State/state.h"
#include "../MyStack/my_stack.h"

#ifndef STACK_AUTOMATON_H
#define STACK_AUTOMATON_H

class StackAutomaton {
 public:
  StackAutomaton(std::string fileName);
  ~StackAutomaton();  // Agrega un destructor para liberar la memoria
 private:
  std::set<State*> states_;  // Cambiado a punteros a State
  Alphabet alphabet_;
  Alphabet stackAlphabet_;
  State* initialState_;  // Cambiado a puntero
  std::set<State*> acceptingStates_;  // Cambiado a punteros
  MyStack stack_;
};

#endif
