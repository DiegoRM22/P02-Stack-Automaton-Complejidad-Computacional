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
  for (State* state : states_) {
    if (*state == *initialState_) {
      initialState_ = state;
      break;
    }
  }
  InitializeStates();
}

// bool StackAutomaton::Accepts(std::string input) {
//   State* currentState = initialState_;  // Usar puntero al estado actual
//   std::cout << "State \t" << "Cadena \t" << "Pila" << std::endl;
//   std::string remainingInput = input;
//   int counter = 1;
//   std::cout << "I\t Est\t Cad\t Pila\t Transiciones" << std::endl;

//   while (!stack_.IsEmpty()) {
//     std::cin.get();

//     std::cout << counter << "\t" << currentState->getIdentifier() << "\t" << remainingInput << "\t" << stack_ << "\t";

//     Symbol currentSymbol = Symbol(remainingInput[0]);
//     std::vector<Transition> transitions;
//     Symbol epsilon = Symbol('.');
//     for (Transition transition : currentState->getTransitions()) {
//       if (((transition.GetStringSymbol() == currentSymbol) || (transition.GetStringSymbol() == epsilon)) && 
//          (((transition.GetStackSymbol() == stack_.Top()) || (transition.GetStackSymbol() == epsilon)))) {
//         transitions.push_back(transition);
//       }
//     }
//     // Print the transitions validated
//     for (Transition transition : transitions) {
//       std::cout << transition << ", ";
//     }
//     std::cout << std::endl;
    
//     // Elegimos la primera transición válida
    
//     std::cout << "TAMAÑO TRANSICIONES: " << transitions.size() << std::endl;
//     if (transitions.size() == 0) {
//       Iteration* firstValidIteration = FindFirstValidIteration();
//       std::cout << "Funciono" << std::endl;
//       // currentTransition = firstValidIteration.getRemainingTransitions()[0];
//       transitions = firstValidIteration->getRemainingTransitions();
//       State* toState = nullptr;
//       Transition currentTransition = transitions[0];
//       for (State* state : states_) {
//         if (*state == State(currentTransition.GetToState())) {
//           toState = state;
//           break;
//         }
//       }
//       std::cout << "Funciono" << std::endl;

//       currentState = toState;
//       remainingInput = firstValidIteration->getRemainingInput();
      
//       stack_ = firstValidIteration->getStack();
//       std::cout << "Nueva iteración: " << std::endl;
//       firstValidIteration->Print();
//       Transites(currentState, remainingInput, currentSymbol, stack_.Top(),
//                 firstValidIteration->getCurrentState(), firstValidIteration->getRemainingTransitions()[0].GetAddToStack());
//       // Eliminar la transición usada
//       transitions.erase(transitions.begin());
//       // firstValidIteration->RemoveTransition(currentTransition);
//       ++counter;
//       continue;
      
//     }
//     Transition currentTransition = transitions[0];
//     State* toState = nullptr;

//     for (State* state : states_) {
//       if (*state == State(currentTransition.GetToState())) {
//         toState = state;
//         break;
//       }
//     }
//     transitions.erase(transitions.begin());
//     Iteration iteration(counter, currentState, remainingInput, stack_, transitions);
//     currentState = toState;
//     Transites(currentState, remainingInput, currentTransition.GetStringSymbol(), stack_.Top(),
//               toState, currentTransition.GetAddToStack());
//     // Eliminar la transición usada
//     iterations_.push(iteration);
//     ++counter;


//   }
//   return false;
// }

void StackAutomaton::InitializeStates() {
  for (State* state : states_) {
    statesCopy_.insert(*state);
  }
}

bool StackAutomaton::Accepts(std::string input) {
  iterationCounter_ = 0;
  // Print statesCopy to check
  for (State state : statesCopy_) {
    std::cout << state << std::endl;
  }
  State currentState;
  for (State state : statesCopy_) {
    if (state == *initialState_) {
      currentState = state;
      break;
    }
  }
  std::cout << "I\t Est\t Cad\t Pila\t Transiciones" << std::endl;
  if (AcceptsRecursive(currentState, input, stack_)) {
    return true;
  }
  return false;
}

bool StackAutomaton::AcceptsRecursive(State currentState, std::string remainingInput, MyStack stack) {
  ++iterationCounter_;
  MyStack stackCopy = stack;
  std::string remainingInputCopy = remainingInput;
  State currentStateCopy = currentState;
  std::cin.get();
  std::cout << iterationCounter_ << "\t" << currentState.getIdentifier() << "\t" << remainingInput << "\t" << stack << "\t";
  Symbol currentSymbol = Symbol(remainingInput[0]);
  std::vector<Transition> transitions = GetTransitions(currentState, currentSymbol, stack.Top());
  for (Transition transition : transitions) {
    std::cout << transition << ", ";
  }
  std::cout << std::endl;
  std::cout << "Numero de transiciones: " << transitions.size() << std::endl;
  int counter = 0;
  if (transitions.size() == 0) {
    std::cout << "No hay transiciones" << std::endl;
    return false;
  }
  for (Transition transition : transitions) {
    if (reset) {
      std::cout << "Reset, poniendo " << currentState.getIdentifier() << " a " << currentStateCopy.getIdentifier() << std::endl;
      currentState = currentStateCopy;
      stack = stackCopy;
      remainingInput = remainingInputCopy;
      reset = false;
    }
    std::cout << "Esta es la transición numero: " << counter << std::endl;
    State toState;
    for (State state : statesCopy_) {
      if (state == State(transition.GetToState())) {
        toState = state;
        break;
      }
    }
    
    // Transitar aqui
    stack.Pop();
    // Add to stack
    if (transition.GetAddToStack().size() > 0) {
      for (int i = transition.GetAddToStack().size() - 1; i >= 0; --i) {
        stack.Push(transition.GetAddToStack()[i]);
      }
    }
    if (transition.GetStringSymbol().GetSymbol() != '.') {
      remainingInput.erase(0, 1);
    }

    
    if (remainingInput.size() == 0 && stack.IsEmpty()) {
      return true;
    }
    if (AcceptsRecursive(toState, remainingInput, stack)) {
      return true;
    } else {
      stack = stackCopy;
      remainingInput = remainingInputCopy;
      reset = true;
    }
    ++counter;
  }
  return false;
}

std::vector<Transition> StackAutomaton::GetTransitions(State state, Symbol stringSymbol, Symbol stackSymbol) {
  std::vector<Transition> transitions;
  Symbol epsilon = Symbol('.');
  for (Transition transition : state.getTransitions()) {
    if (((transition.GetStringSymbol() == stringSymbol) || (transition.GetStringSymbol() == epsilon)) && 
        (((transition.GetStackSymbol() == stackSymbol) || (transition.GetStackSymbol() == epsilon))) ) {
      transitions.push_back(transition);
    }
  }
  return transitions;
}


  






void StackAutomaton::Transites(State state, std::string& remainingInput, Symbol stringSymbol, Symbol stackSymbol,
                               State* toState, std::vector<Symbol> addToStack) {
  if (stringSymbol.GetSymbol() != '.' && stringSymbol.GetSymbol() == remainingInput[0]) {
    std::cout << "Eliminando " << stringSymbol.GetSymbol() << " de " << remainingInput << std::endl;
    remainingInput.erase(0, 1);
  }
  if (stackSymbol.GetSymbol() != '.') {
    stack_.Pop();
  }
  if (addToStack[0].GetSymbol() != '.') {
    for (int i = addToStack.size() - 1; i >= 0; --i) {
      stack_.Push(addToStack[i]);
    }
  }
  state = *toState; 
}

Iteration* StackAutomaton::FindFirstValidIteration() {
  std::stack<Iteration> copy = iterations_;
  while (!copy.empty()) {
    Iteration iteration = copy.top();
    copy.pop();
    if (iteration.getRemainingTransitions().size() > 0) {
      return &iteration;
    }
  }
}

// Destructor para liberar memoria de los estados
StackAutomaton::~StackAutomaton() {
  for (auto state : states_) {
    delete state;  // Liberar memoria de cada estado
  }
}
