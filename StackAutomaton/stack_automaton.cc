#include <fstream>
#include <regex>

#include "stack_automaton.h"

StackAutomaton::StackAutomaton(std::string fileName) {
  std::ifstream file(fileName);
  std::string line;
  std::regex commentLineRegexp("\\s*#.*");
  
  while (std::getline(file, line)) {
    if (std::regex_match(line, commentLineRegexp)) {
      std::cout << "Comment line. Skipping..." << std::endl;
      continue;
    } else {
      std::cout << "Processing line: " << line << std::endl;
    }
  }
}