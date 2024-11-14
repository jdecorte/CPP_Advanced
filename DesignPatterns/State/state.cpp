#include "state.h"
#include "context.h"
#include <iostream>

ConcreteStateAPtr ConcreteStateA::instance = nullptr; // Initialize the static instance variable
ConcreteStateBPtr ConcreteStateB::instance = nullptr; // Initialize the static instance variable

ConcreteStateAPtr ConcreteStateA::get() 
{
    if (instance == nullptr) // Check if the instance is null
    {
        instance = std::make_shared<ConcreteStateA>(); // Create a new instance if null
        instance->name = 'A';
    }
    return instance;
}

void ConcreteStateA::handle(Context& context) // handle method to handle requests
{
    std::cout << "State A handling request and changing to State B" << std::endl;
    context.setState(ConcreteStateB::get());
}

ConcreteStateBPtr ConcreteStateB::get() 
{
    if (instance == nullptr) // Check if the instance is null
    {
        instance = std::make_shared<ConcreteStateB>(); // Create a new instance if null
        instance->name = 'B';
    }
    return instance;
}

void ConcreteStateB::handle(Context& context)
{
    std::cout << "State B handling request and changing to State A" << std::endl;
    context.setState(ConcreteStateA::get());
}