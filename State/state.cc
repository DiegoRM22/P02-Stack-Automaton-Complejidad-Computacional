
#include "state.h"

std::ostream& operator<<(std::ostream& os, const State& state) {
  os << state.getIdentifier();
  os << "Transiciones: ";
  for (Transition transition : state.getTransitions()) {
    os << transition;
  }
  return os;
}