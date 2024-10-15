#include "transition.h"

std::ostream& operator<<(std::ostream& os, const Transition& transition) {
  os << transition.GetFromState() << " " << transition.GetStringSymbol() << " " << transition.GetStackSymbol() << " " << transition.GetToState() << " ";
  for (Symbol symbol : transition.GetAddToStack()) {
    os << symbol;
  }
  return os;
}