#pragma once
#include "state.h"

// Context class that maintains an instance of a ConcreteState subclass
class Context {
private:
    StatePtr state; // Current state of the context
public:
    Context(StatePtr initialState) : state(initialState) {}
    void setState(StatePtr newState) 
    { 
        state = newState; 
        std::cout << "State changed to " << state->name << std::endl;
    }
    void request() { state->handle(*this); }
};