#include <iostream>
#include <vector>

#include "../Transition/transition.h"

#ifndef STATE_H
#define STATE_H

class State {
 public:
  State() {}
  State(std::string identifier, bool isAccepting = false) : identifier_(identifier), isAccepting_(isAccepting) {}

  std::string getIdentifier() const { return identifier_; }
  bool isAccepting() const { return isAccepting_; }
  std::vector<Transition> getTransitions() const { return transitions_; }
  void setIdentifier(std::string identifier) { identifier_ = identifier; }

  bool operator==(const State &state) const {
    return identifier_ == state.identifier_;
  }

  bool operator<(const State &state) const {
    return identifier_ < state.identifier_;
  }

  bool operator>(const State &state) const {
    return identifier_ > state.identifier_;
  }

  void AddTransition(Transition transition) {
    std::cout << "Adding transition: " << transition << std::endl;
    transitions_.push_back(transition);
  }
  
 private:
  std::string identifier_;
  bool isAccepting_;
  std::vector<Transition> transitions_;
};

std::ostream& operator<<(std::ostream& os, const State& state);

#endif