#include "symbol.h"

std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
  os << symbol.GetSymbol();
  return os;
}