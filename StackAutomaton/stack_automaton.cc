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
        // Parsear la línea de estados
        while (line.size() > 0 && line.find(delimiter) != std::string::npos) {
          size_t pos = line.find(delimiter);
          std::string stateName = line.substr(0, pos);
          State* state = new State(stateName);  // Crear un puntero a State
          states_.insert(state);  // Insertar puntero en el set
          line.erase(0, pos + delimiter.length());
        }
        State* state = new State(line);  // Crear un puntero a State
        states_.insert(state);  // Insertar puntero en el set
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
        initialState_ = new State(line);  // Crear puntero al estado inicial
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
          std::string fromStateName = line.substr(0, pos);
          line.erase(0, pos + delimiter.length());

          pos = line.find(delimiter);
          char stringSymbol = line.substr(0, pos)[0];
          line.erase(0, pos + delimiter.length());

          pos = line.find(delimiter);
          char stackSymbol = line.substr(0, pos)[0];
          line.erase(0, pos + delimiter.length());

          pos = line.find(delimiter);
          std::string toStateName = line.substr(0, pos);
          line.erase(0, pos + delimiter.length());

          std::vector<Symbol> addToStack;
          // while (line.size() > 0 && line.find(delimiter) != std::string::npos) {
          //   std::cout << "Line: " << line << std::endl;
          //   pos = line.find(delimiter);
          //   char symbolName = line.substr(0, pos)[0];
          //   Symbol symbol(symbolName);
          //   addToStack.push_back(symbol);
          //   line.erase(0, pos + delimiter.length());
          // }
          for (char symbolName : line) {
            Symbol symbol(symbolName);
            addToStack.push_back(symbol);
          }

          Transition transition(fromStateName, toStateName, Symbol(stringSymbol), Symbol(stackSymbol), addToStack);
          
          // Usar punteros para buscar el estado y agregar la transición
          for (State* state : states_) {  // Usa punteros a State
            if (*state == State(fromStateName)) {  // Compara con un nuevo estado temporal
              state->AddTransition(transition);  // Modifica el estado original
              break;  // Salir después de agregar la transición
            }
          }
        }  
        break;
      }
    }
  }

  // Check parser results
  std::cout << "Estados: ";
  for (State* state : states_) {
    std::cout << state->getIdentifier() << " ";
  }
  std::cout << std::endl;

  std::cout << "Alfabeto: ";
  for (Symbol symbol : alphabet_.GetSymbols()) {
    std::cout << symbol.GetSymbol() << " ";
  }
  std::cout << std::endl;

  std::cout << "Alfabeto de la pila: ";
  for (Symbol symbol : stackAlphabet_.GetSymbols()) {
    std::cout << symbol.GetSymbol() << " ";
  }
  std::cout << std::endl;

  std::cout << "Estado inicial: " << initialState_->getIdentifier() << std::endl;

  std::cout << "Elemento de la pila inicial: " << stack_.Top() << std::endl;
}

// Destructor para liberar memoria de los estados
StackAutomaton::~StackAutomaton() {
  for (auto state : states_) {
    delete state;  // Liberar memoria de cada estado
  }
}
