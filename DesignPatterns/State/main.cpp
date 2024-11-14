#include <iostream>
#include <memory>
#include "context.h"


// Main function to demonstrate the state pattern
int main() {
    // Create context with initial state A
    Context context(ConcreteStateA::get());
    
    // Request handling, which will change states
    context.request(); // State A handles request and changes to State B
    context.request(); // State B handles request and changes to State A
    context.setState(ConcreteStateB::get()); // Set state to B
    context.request(); // State A handles request and changes to State B
    context.request(); // State B handles request and changes to State A
    
    return 0;
}