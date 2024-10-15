#include <iostream>
#include <vector>

#include "../Transition/transition.h"

#ifndef STATE_H
#define STATE_H

class State {
 public:
 private:
  std::string identifier_;
  bool isAccepting_;
  std::vector<Transition> transitions_;
};

#endif