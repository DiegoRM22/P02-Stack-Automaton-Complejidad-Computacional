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
  StackAutomaton(std::string fileName);  // Constructor que inicializa el autómata con el archivo de configuración
  bool Accepts(std::string input);  // Método principal para verificar si la cadena es aceptada
  bool AcceptsRecursive(State currentState, std::string remainingInput, MyStack stack);  // Método recursivo para evaluar la cadena
  std::vector<Transition> GetTransitions(State state, Symbol stringSymbol, Symbol stackSymbol);  // Obtener las transiciones válidas desde el estado actual
  void Transites(State& state, State toState, std::string& remainingInput, Symbol stringSymbol, Symbol stackSymbol, std::vector<Symbol> addToStack, MyStack& stack);  // Ejecuta la transición
  Iteration* FindFirstValidIteration();  // Encuentra la primera iteración válida para retroceder en el autómata
  void InitializeStates();  // Inicializa los estados copiando el conjunto original
  ~StackAutomaton();  // Destructor para liberar memoria

 private:
  std::set<State*> states_;  // Conjunto de punteros a estados
  std::set<State> statesCopy_;  // Copia de los estados para manipulación
  Alphabet alphabet_;  // Alfabeto del autómata
  Alphabet stackAlphabet_;  // Alfabeto de la pila
  State* initialState_;  // Puntero al estado inicial
  std::set<State*> acceptingStates_;  // Conjunto de punteros a los estados de aceptación
  MyStack stack_;  // Pila del autómata
  std::stack<Iteration> iterations_;  // Pila de iteraciones para retroceder en caso de fallo
  int iterationCounter_;  // Contador de iteraciones para seguimiento
  bool reset = false;  // Bandera para reiniciar la evaluación de transiciones
};

#endif
