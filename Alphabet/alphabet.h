#include <iostream>
#include <set>

#include "../Symbol/symbol.h"

#ifndef ALPHABET_H
#define ALPHABET_H

class Alphabet {
 public:
  Alphabet() {}
  Alphabet(std::set<Symbol> symbols) : symbols_(symbols) {}
  std::set<Symbol> GetSymbols() const { return symbols_; }
  void AddSymbol(Symbol symbol) { symbols_.insert(symbol); }
 private:
  std::set<Symbol> symbols_;
};

#endif