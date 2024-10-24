/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Complejidad Computacional P02
  *
  * @author Diego Rodríguez Martín
  * @since 24-10-2024
  * @brief Implementación de la clase StackAutomaton.
  *
*/

#include <iostream>
#include <set>
#include <string>
#include <stack>

#include "../Alphabet/alphabet.h"
#include "../State/state.h"
#include "../MyStack/my_stack.h"

#ifndef STACK_AUTOMATON_H
#define STACK_AUTOMATON_H

class StackAutomaton {
 public:
  StackAutomaton(std::string fileName);  // Constructor que inicializa el autómata con el archivo de configuración
  bool Accepts(std::string input);  // Método principal para verificar si la cadena es aceptada
  bool AcceptsRecursive(State currentState, std::string remainingInput, MyStack stack);  // Método recursivo para evaluar la cadena
  std::vector<Transition> GetTransitions(State state, Symbol stringSymbol, Symbol stackSymbol);  // Obtener las transiciones válidas desde el estado actual
  void Transites(State& state, State toState, std::string& remainingInput, Symbol stringSymbol, Symbol stackSymbol, std::vector<Symbol> addToStack, MyStack& stack);  // Ejecuta la transición
  void InitializeStates();  // Inicializa los estados copiando el conjunto original
  void SetTraceMode(bool traceModeOn) { traceModeOn_ = traceModeOn; }  // Activa o desactiva el modo de seguimiento
  bool CheckInitialState(State initialState);  // Comprueba si el estado inicial es válido
  bool CheckInitialStackSymbol(Symbol initialStackSymbol);  // Comprueba si el símbolo inicial de la pila es válido
  bool CheckTransition(Transition transition);  // Comprueba si la transición es válida
  bool CheckState(State state);  // Comprueba si el estado es válido
  bool CheckStackSymbol(Symbol stackSymbol);  // Comprueba si el símbolo de la pila es válido
  ~StackAutomaton();  // Destructor para liberar memoria

 private:
  std::set<State*> states_;  // Conjunto de punteros a estados
  std::set<State> statesCopy_;  // Copia de los estados para manipulación
  Alphabet alphabet_;  // Alfabeto del autómata
  Alphabet stackAlphabet_;  // Alfabeto de la pila
  State* initialState_;  // Puntero al estado inicial
  std::set<State*> acceptingStates_;  // Conjunto de punteros a los estados de aceptación
  MyStack stack_;  // Pila del autómata
  int iterationCounter_;  // Contador de iteraciones para seguimiento
  bool traceModeOn_ = false;  // Modo de seguimiento  
};

#endif
