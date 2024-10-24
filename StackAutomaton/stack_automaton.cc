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

#include <fstream>
#include <regex>

#include "stack_automaton.h"

/**
 * Constructor que inicializa el autómata con el archivo de configuración.
 * @param fileName Nombre del archivo de configuración.
 */
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

/**
 * Inicializa los estados copiando el conjunto original.
 */
void StackAutomaton::InitializeStates() {
  for (State* state : states_) {
    statesCopy_.insert(*state);
  }
}

/**
 * Método principal para verificar si la cadena es aceptada.
 * @param input Cadena a evaluar.
 * @return true si la cadena es aceptada, false en caso contrario.
 */
bool StackAutomaton::Accepts(std::string input) {
  iterationCounter_ = 0;
  // Print statesCopy to check
  State currentState;
  for (State state : statesCopy_) {
    if (state == *initialState_) {
      currentState = state;
      break;
    }
  }
  if (traceModeOn_)  std::cout << "I\t Est\t Cad\t Pila\t Transiciones" << std::endl;
  if (AcceptsRecursive(currentState, input, stack_)) {
    return true;
  }
  return false;
}

/**
 * Método recursivo para evaluar la cadena.
 * @param currentState Estado actual.
 * @param remainingInput Cadena restante.
 * @param stack Pila actual.
 * @return true si la cadena es aceptada, false en caso contrario.
 */
bool StackAutomaton::AcceptsRecursive(State currentState, std::string remainingInput, MyStack stack) {
  // Caso base: si la pila está vacía y no queda más entrada, la cadena es aceptada.
  if (stack.IsEmpty() && remainingInput.size() == 0) {
    return true;
  } else if (stack.IsEmpty() && remainingInput.size() > 0) {
    return false;
  }

  // Copias de la cadena, pila y estado para retroceder si es necesario
  std::string remainingInputCopy = remainingInput;
  MyStack stackCopy = stack;
  State currentStateCopy = currentState;
  ++iterationCounter_;
  //std::cin.get();  // Pausa para seguimiento
  // Si la cadena no está vacía, tomamos el símbolo actual; si está vacía, usamos epsilon ('.')
  Symbol currentSymbol = remainingInput.empty() ? Symbol('.') : Symbol(remainingInput[0]);
  // Obtenemos las transiciones válidas desde el estado actual
  std::vector<Transition> transitions = GetTransitions(currentState, currentSymbol, stack.Top());
  // Si no hay transiciones válidas, la recursión termina sin éxito
  if (transitions.size() == 0) {
    if (traceModeOn_) {
      std::cout << iterationCounter_ << "\t" << currentState.getIdentifier() << "\t" << remainingInput << "\t" << stack << "\t";
      std::cout << "No hay transiciones" << std::endl;
    }
    return false;
  }
  int counter = 1;
  // Probar todas las transiciones válidas
  for (Transition transition : transitions) {
    if (traceModeOn_) {
      std::cout << iterationCounter_ << "\t" << currentState.getIdentifier() << "\t" << remainingInput << "\t" << stack << "\t";
      // Traza las transiciones posibles
      for (Transition transition : transitions) {
        std::cout << transition << ", ";
      }
      std::cout << "\tTransicion elegida: " << transition << std::endl;
    }
    // Buscar el estado de destino
    State toState;
    for (State state : statesCopy_) {
      if (state == State(transition.GetToState())) {
        toState = state;
        break;
      }
    }
    // Preparar la nueva pila y la cadena después de aplicar la transición
    std::string newRemainingInput = remainingInput;
    MyStack newStack = stack;
    Transites(currentState, toState, newRemainingInput, transition.GetStringSymbol(), stack.Top(), transition.GetAddToStack(), newStack);
    // Llamada recursiva
    if (AcceptsRecursive(toState, newRemainingInput, newStack)) {
      return true;  // Si alguna rama acepta, terminamos la búsqueda
    }
    ++counter;
    // Si no, se continúa probando las siguientes transiciones
  }
  // Si ninguna transición lleva a la aceptación, devolvemos false
  return false;
}

/**
 * Obtener las transiciones válidas desde el estado actual.
 * @param state Estado actual.
 * @param stringSymbol Símbolo actual de la cadena.
 * @param stackSymbol Símbolo actual de la pila.
 * @return Vector de transiciones válidas.
 */
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

/**
 * Ejecuta la transición.
 * @param state Estado actual.
 * @param toState Estado de destino.
 * @param remainingInput Cadena restante.
 * @param stringSymbol Símbolo actual de la cadena.
 * @param stackSymbol Símbolo actual de la pila.
 * @param addToStack Símbolos a añadir a la pila.
 * @param stack Pila actual.
 */
void StackAutomaton::Transites(State& state, State toState, std::string& remainingInput, Symbol stringSymbol, Symbol stackSymbol,
std::vector<Symbol> addToStack, MyStack& stack) {
  state = toState;
  if (stringSymbol.GetSymbol() != '.') {
    remainingInput.erase(0, 1);
  }
  if (stackSymbol.GetSymbol() != '.') {
    stack.Pop();
  }
  for (int i = addToStack.size() - 1; i >= 0; --i) {
    if (addToStack[i].GetSymbol() != '.') {
      stack.Push(addToStack[i].GetSymbol());
    }
  }
}

/**
 * Destructor para liberar memoria.
 */
StackAutomaton::~StackAutomaton() {
  for (auto state : states_) {
    delete state;  // Liberar memoria de cada estado
  }
}
