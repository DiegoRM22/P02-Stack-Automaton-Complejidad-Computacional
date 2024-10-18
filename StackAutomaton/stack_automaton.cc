#include <fstream>
#include <regex>

#include "stack_automaton.h"

StackAutomaton::StackAutomaton(std::string fileName) {
  std::ifstream file(fileName);
  std::string line;
  std::regex commentLineRegexp("\\s*#.*");
  int counter = 0;
  std::string delimiter = " ";
  while (std::getline(file, line)) {
    if (std::regex_match(line, commentLineRegexp)) {
      std::cout << "Comment line. Skipping..." << std::endl;
      continue;
    }
    ++counter;
    switch (counter) {
      case 1: {
        // Parsear la linea de estados
        while (line.size() > 0 && line.find(delimiter) != std::string::npos) {
          size_t pos = line.find(delimiter);
          std::string stateName = line.substr(0, pos);
          State state(stateName);
          states_.insert(state);
          line.erase(0, pos + delimiter.length());
        }
        State state(line);
        states_.insert(state);
        break;
      }
      case 2: {
        // Parsear el alfabeto
        while (line.size() > 0 && line.find(delimiter) != std::string::npos) {
          size_t pos = line.find(delimiter);
          char symbolName = line.substr(0, pos)[0];
          Symbol symbol(symbolName);
          alphabet_.AddSymbol(symbol);
          line.erase(0, pos + delimiter.length());
        }
        Symbol symbol(line[0]);
        alphabet_.AddSymbol(symbol);
        break;
      }
      case 3: {
        // Parsear el alfabeto de la pila
        while (line.size() > 0 && line.find(delimiter) != std::string::npos) {
          size_t pos = line.find(delimiter);
          char symbolName = line.substr(0, pos)[0];
          Symbol symbol(symbolName);
          stackAlphabet_.AddSymbol(symbol);
          line.erase(0, pos + delimiter.length());
        }
        Symbol symbol(line[0]);
        stackAlphabet_.AddSymbol(symbol);
        break;
      }
      case 4: {
        // Parsear el estado inicial
        initialState_ = State(line);
        break;
      }
      case 5: {
        // Parsear el elemento de la pila inicial
        stack_.Push(line[0]);
        break;
      }
      default: {
        // Parsear las transiciones.
        while (line.size() > 0 && line.find(delimiter) != std::string::npos) {
          size_t pos = line.find(delimiter);
          std::string fromState = line.substr(0, pos);
          line.erase(0, pos + delimiter.length());

          pos = line.find(delimiter);
          char stringSymbol = line.substr(0, pos)[0];
          line.erase(0, pos + delimiter.length());

          pos = line.find(delimiter);
          char stackSymbol = line.substr(0, pos)[0];
          line.erase(0, pos + delimiter.length());

          pos = line.find(delimiter);
          std::string toState = line.substr(0, pos);
          line.erase(0, pos + delimiter.length());

          std::vector<Symbol> addToStack;
          while (line.size() > 0 && line.find(delimiter) != std::string::npos) {
            pos = line.find(delimiter);
            char symbolName = line.substr(0, pos)[0];
            Symbol symbol(symbolName);
            addToStack.push_back(symbol);
            line.erase(0, pos + delimiter.length());
          }
          Symbol symbol(line[0]);
          addToStack.push_back(symbol);

          Transition transition(fromState, toState, Symbol(stringSymbol), Symbol(stackSymbol), addToStack);
          for (State state : states_) {
            if (state == fromState) {
              std::cout << "Adding transition: " << transition << " to state: " << state << std::endl;
              state.AddTransition(transition);
            }
          }
        }
        // for (State state : states_) {
        //   std::cout << state << std::endl;
        // }
        break;
      }

    }
  }
}