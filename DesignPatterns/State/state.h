#pragma once
#include <memory> // Include memory header for shared pointer
#include <iostream>

class State; // Forward declaration of Context class to avoid circular dependency
class ConcreteStateA; // Forward declaration of State class to avoid circular dependency
class ConcreteStateB; // Forward declaration of State class to avoid circular dependency

class Context; // Forward declaration of Context class to avoid circular dependency

using StatePtr = std::shared_ptr<State>; // Typedef for shared pointer to State class
using ConcreteStateAPtr = std::shared_ptr<ConcreteStateA>; 
using ConcreteStateBPtr = std::shared_ptr<ConcreteStateB>;

class Context; // Forward declaration of Context class to avoid circular dependency

class State {
public:
    virtual ~State() = default; // Virtual destructor for polymorphic behavior
    virtual void handle(Context& context) = 0;
    char name; // Name of the state (A or B)
protected:
    State() = default; // Default constructor
};

// Concrete state class A
class ConcreteStateA : public State {
public:
    static ConcreteStateAPtr get(); // method to get the singleton instance of the class
    virtual void handle(Context& context) override; // handle method to handle requests
private:
    static ConcreteStateAPtr instance; // Static instance of the class
};

// Concrete state class B
class ConcreteStateB : public State {
public:
    static ConcreteStateBPtr get();
    virtual void handle(Context& context) override;
private:
    static ConcreteStateBPtr instance; // Static instance of the class
};

