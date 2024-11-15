#ifndef STATE_H
#define STATE_H

#include <memory>
#include <iostream>

using namespace std;

class State;
class Open;
class Closed;
class Opening;
class Closing;
class Locked;

class Garage;

using StatePtr = std::shared_ptr<State>;
using OpenPtr = std::shared_ptr<Open>;
using ClosedPtr = std::shared_ptr<Closed>;
using OpeningPtr = std::shared_ptr<Opening>;
using ClosingPtr = std::shared_ptr<Closing>;
using LockedPtr = std::shared_ptr<Locked>;

class State : public std::enable_shared_from_this<State>
{
public:
    virtual void OpenClose(Garage&)=0;
    virtual void Lock(Garage&)=0;
protected:
    void beep() {cout << "beep" << endl;}
    void SetState (Garage& garage, StatePtr s);
};

class Open: public State
{
public:
    static OpenPtr& get();
    virtual void OpenClose(Garage&);
    virtual void Lock(Garage&);
private: 
    static OpenPtr instance;
};

class Closed: public State
{
public:
    static ClosedPtr get();
    virtual void OpenClose(Garage&);
    virtual void Lock(Garage&);
private:
    static ClosedPtr instance;
};

class Opening: public State
{
public:
    static OpeningPtr get();
    virtual void OpenClose(Garage&);
    virtual void Lock(Garage&);
private:
    static OpeningPtr instance;
};

class Closing: public State
{
public:
    static ClosingPtr get();
    virtual void OpenClose(Garage&);
    virtual void Lock(Garage&);
private:
    static ClosingPtr instance;
};

class Locked: public State
{
public:
    static LockedPtr get();
    virtual void OpenClose(Garage&);
    virtual void Lock(Garage&);
private:
    static LockedPtr instance;
};

#endif
