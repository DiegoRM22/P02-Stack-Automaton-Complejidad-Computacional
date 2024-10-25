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
#include <string>
#include "StackAutomaton/stack_automaton.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Uso: " << argv[0] << " <archivo_automata> <cadena1> [<cadena2> ...] [--trace]" << std::endl;
    return 1;
  }

  std::string fileName = argv[1];
  StackAutomaton stackAutomaton(fileName);
  bool traceMode = false;

  // Verifica si el último argumento es "--trace" y ajusta el modo de seguimiento
  if (std::string(argv[argc - 1]) == "--trace") {
    traceMode = true;
    stackAutomaton.SetTraceMode(true);
    argc--; // Reduce el conteo total de argumentos para ignorar "--trace" en las cadenas
  }

  // Itera sobre todas las cadenas proporcionadas como argumentos
  for (int i = 2; i < argc; ++i) {
    std::string input = argv[i];
    std::cout << "Analizando la cadena: " << input << std::endl;
    if (stackAutomaton.Accepts(input)) {
      std::cout << "La cadena " << input << " es aceptada." << std::endl;
    } else {
      std::cout << "La cadena " << input << " no es aceptada." << std::endl;
    }
  }

  return 0;
}