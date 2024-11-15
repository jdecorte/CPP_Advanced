#ifndef GARAGE_H
#define GARAGE_H

#include <iostream>
#include "state.h"

using namespace std;

class Garage
{
public:
    Garage() {state = Closed::get();}
    void OpenClose() {state->OpenClose(*this);}
    void Lock() {state->Lock(*this);}
    StatePtr State() {return state;}
    void SetState(StatePtr s) {state = s;}

    StatePtr State0() {return state0;}
    void SetState0(StatePtr t0) {state0 = t0;}

private:
    StatePtr state = nullptr;
    StatePtr state0 = nullptr;  // previous state
};

#endif // GARAGE_H
