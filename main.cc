#include <iostream>

#include "StackAutomaton/stack_automaton.h"

int main(int argc, char *argv[]) {
  std::string fileName = argv[1];
  StackAutomaton stackAutomaton(fileName);

  return 0;
}