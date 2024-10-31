#include <iostream>
#include <list>

using namespace std;

template<typename T> struct Observer
{
    // The first parameter is a reference to the object whose field actually changed, and the
    // second is the name of the field. The name is passed as a string, which
    // does hurt the refactorability of our code (what if the field name changes?).
    virtual void field_changed(T& source, const string& field_name) = 0;
};

template <typename T> struct Observable
{
    void notify(T& source, const string& name) 
    { 
        // ...
    }
    void subscribe(Observer<T>* f) 
    { 
        // subscribe an observer
        // ... 
    }
    void unsubscribe(Observer<T>* f) 
    { 
        // unsubscribe an observer
        // ...
    }
private:
    list<Observer<T>*> observers;
};

struct Person : Observable<Person>
// CRTP: Curiously Recurring Template Pattern
// Person is the derived class, and Observable is the base class.
// The base class is parameterized by the derived class.
// This allows the base class to refer to the derived class.
// The derived class must provide itself as a template argument to the base class.
{
    void set_age(const int age)
    {
        if (this->age == age) return;
        this->age = age;
        notify(*this, "age");
    }
    int get_age() const { return age; }
private:
    int age;
};

// write to console whenever a person's age changes
struct ConsolePersonObserver : Observer<Person>
{
    void field_changed(Person& source,const string& field_name) override
    {
        cout << "Person's " << field_name << " has changed to " << source.get_age() << ".\n";
    }
};

int main()
{
    // Test the observer pattern
    // ...
    return 0;
}