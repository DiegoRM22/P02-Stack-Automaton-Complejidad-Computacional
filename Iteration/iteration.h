#include <iostream>
#include <vector>

#include "../State/state.h"
#include "../MyStack/my_stack.h"
#include "../Transition/transition.h"

#ifndef ITERATION_H
#define ITERATION_H

class Iteration {
 public:
    Iteration(int identifier, State* currentState, std::string remainingInput, MyStack stack, std::vector<Transition> remainingTransitions)
        : identifier_(identifier), currentState_(currentState), remainingInput_(remainingInput), stack_(stack), remainingTransitions_(remainingTransitions) {}
    int getIdentifier() const { return identifier_; }
    State* getCurrentState() const { return currentState_; }
    std::string getRemainingInput() const { return remainingInput_; }
    MyStack getStack() const { return stack_; }
    std::vector<Transition> getRemainingTransitions() const { return remainingTransitions_; }
    void setIdentifier(int identifier) { identifier_ = identifier; }
    void setCurrentState(State* currentState) { currentState_ = currentState; }
    void setRemainingInput(std::string remainingInput) { remainingInput_ = remainingInput; }
    void setStack(MyStack stack) { stack_ = stack; }
    void setRemainingTransitions(std::vector<Transition> remainingTransitions) { remainingTransitions_ = remainingTransitions; }
    void Print() const {
        std::cout << identifier_ << "\t" << currentState_->getIdentifier() << "\t" << remainingInput_ << "\t" << stack_ << "\t";
        for (Transition transition : remainingTransitions_) {
            std::cout << transition << ", ";
        }
        std::cout << std::endl;
    }
    void RemoveTransition(Transition transition) {
        for (int i = 0; i < remainingTransitions_.size(); ++i) {
            if (remainingTransitions_[i] == transition) {
                remainingTransitions_.erase(remainingTransitions_.begin() + i);
                break;
            }
        }
    }
    ~Iteration() {}
 private:
  int identifier_;
  State* currentState_;
  std::string remainingInput_;
  MyStack stack_;
  std::vector<Transition> remainingTransitions_;
};


#endif