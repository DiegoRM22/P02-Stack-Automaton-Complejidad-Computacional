#include <fstream>

#include "stack_automaton.h"

StackAutomaton::StackAutomaton(std::string fileName) {
  std::ifstream file(fileName);
  std::string line;
  while (std::getline(file, line)) {
  }
}