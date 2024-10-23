#include <iostream>
#include <set>
#include <string>
#include <stack>

#include "../Alphabet/alphabet.h"
#include "../State/state.h"
#include "../MyStack/my_stack.h"
#include "../Iteration/iteration.h"

#ifndef STACK_AUTOMATON_H
#define STACK_AUTOMATON_H

class StackAutomaton {
 public:
  StackAutomaton(std::string fileName);
  bool Accepts(std::string input);
  bool AcceptsRecursive(State* currentState, std::string remainingInput, MyStack stack);
  std::vector<Transition> GetTransitions(State* state, Symbol stringSymbol, Symbol stackSymbol);
  void Transites(State state, std::string& remainingInput, Symbol stringSymbol, Symbol stackSymbol,
                 State* toState, std::vector<Symbol> addToStack);
  Iteration* FindFirstValidIteration();
  void InitializeStates();
  ~StackAutomaton();  // Agrega un destructor para liberar la memoria
 private:
  std::set<State*> states_;  // Cambiado a punteros a State
  std::set<State> statesCopy_;
  Alphabet alphabet_;
  Alphabet stackAlphabet_;
  State* initialState_;  // Cambiado a puntero
  std::set<State*> acceptingStates_;  // Cambiado a punteros
  MyStack stack_;
  std::stack<Iteration> iterations_;
  int iterationCounter_;
  bool reset = false;
};

#endif
