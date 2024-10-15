#include <iostream>

#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol {
 public:
  Symbol(char symbol) : symbol(symbol) {}
  char GetSymbol() const { return symbol; }
  void GetSymbol(char symbol) { this->symbol = symbol; }
 private:
  char symbol;
};

std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
  os << symbol.GetSymbol();
  return os;
}

#endif