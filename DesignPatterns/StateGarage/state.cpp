#include "state.h"
#include "garage.h"

OpenPtr Open::instance = nullptr;
ClosedPtr Closed::instance = nullptr;
OpeningPtr Opening::instance = nullptr;
ClosingPtr Closing::instance = nullptr;
LockedPtr Locked::instance = nullptr;

void State::SetState(Garage& garage, StatePtr s)
{
    garage.SetState0(shared_from_this());
    garage.SetState(s);
}

OpenPtr& Open::get()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<Open>();
    }
    std::cout << "Open" << std::endl;
    return instance;
}

void Open::OpenClose(Garage& g)
{
    SetState(g,Closed::get());
}

void Open::Lock(Garage& g)
{
    beep();
}

ClosedPtr Closed::get()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<Closed>();
    }
    std::cout << "Closed" << std::endl;
    return instance;
}

void Closed::OpenClose(Garage& g)
{
    SetState(g,Open::get());
}

void Closed::Lock(Garage& g)
{
    beep();
}

OpeningPtr Opening::get()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<Opening>();
    }
    std::cout << "Opening" << std::endl;
    return instance;
}

void Opening::OpenClose(Garage& g)
{
    SetState(g,Closed::get());
}

void Opening::Lock(Garage& g)
{
    SetState(g,Locked::get());
}

ClosingPtr Closing::get()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<Closing>();
    }
    std::cout << "Closing" << std::endl;
    return instance;
}

void Closing::OpenClose(Garage& g)
{
    SetState(g,Open::get());
}

void Closing::Lock(Garage& g)
{
    SetState(g,Locked::get());
}

LockedPtr Locked::get()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<Locked>();
    }
    std::cout << "Locked" << std::endl; 
    return instance;
}

void Locked::OpenClose(Garage& g)
{
    if (g.State0() == Opening::get())
    {
        SetState(g,Open::get());
    }
    else if (g.State0() == Closing::get())
    {
        SetState(g,Closed::get());
    }
    else
    {
        beep();
    }
}

void Locked::Lock(Garage& g)
{
    beep();
}




