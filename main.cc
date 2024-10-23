#include <iostream>

#include "StackAutomaton/stack_automaton.h"

int main(int argc, char *argv[]) {
  std::string fileName = argv[1];
  StackAutomaton stackAutomaton(fileName);
  std::string input = argv[2];
  if (stackAutomaton.Accepts(input)) {
    std::cout << "La cadena es aceptada." << std::endl;
  } else {
    std::cout << "La cadena no es aceptada." << std::endl;
  }

  return 0;
}