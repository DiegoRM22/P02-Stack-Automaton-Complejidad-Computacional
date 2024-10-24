/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Complejidad Computacional P02
  *
  * @author Diego Rodríguez Martín
  * @since 24-10-2024
  * @brief Implementación del programa principal.
  *
*/

#include <iostream>

#include "StackAutomaton/stack_automaton.h"

int main(int argc, char *argv[]) {
  std::string fileName = argv[1];
  StackAutomaton stackAutomaton(fileName);
  std::string input = argv[2];
  if (argc > 3) {
    std::string mode = argv[3];
    if (mode == "--trace") {
      std::cout << "Modo de seguimiento activado." << std::endl;
      stackAutomaton.SetTraceMode(true);
    }
  }
  if (stackAutomaton.Accepts(input)) {
    std::cout << "La cadena es aceptada." << std::endl;
  } else {
    std::cout << "La cadena no es aceptada." << std::endl;
  }

  return 0;
}