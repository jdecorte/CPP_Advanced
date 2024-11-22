#include <iostream>
#include <string>
#include <iostream>
using namespace std;
 
/* Abstract base class */
// The abstract Coffee class defines the functionality of Coffee implemented by decorator
class Coffee
{
public:
  virtual double getCost() = 0; // returns the cost of the coffee
  virtual std::string getIngredients() = 0; // returns the ingredients of the coffee
  virtual ~Coffee() {};
};
 
/* SimpleCoffee class. */
// extension of a simple coffee without any extra ingredients
class SimpleCoffee : public Coffee
{
public:
  double getCost()  {
    return 1.0;
  }
 
  std::string getIngredients() {
    return "Coffee";
  }
};
 
/* Decorators */
// Decorator Milk that adds milk to coffee
class MilkDecorator : public Coffee
{
public: 
  MilkDecorator (Coffee& bCoffee) : basicCoffee(bCoffee) {}
 
  double getCost() { // providing methods defined in the abstract superclass
    return basicCoffee.getCost() + 0.5;
  }
 
  std::string getIngredients() {
    return basicCoffee.getIngredients() + ", " + "Milk";
  }
private:
  Coffee& basicCoffee;
};
 
// Decorator Sugar that adds sugar to coffee
class SugarDecorator : public Coffee
{
public:
  SugarDecorator (Coffee& bCoffee):basicCoffee(bCoffee) {}
 
  double getCost()
  {
    return basicCoffee.getCost() + 0.7;
  }
 
  std::string getIngredients()
  {
    return basicCoffee.getIngredients() + ", " + "Sugar";
  }
private:
  Coffee& basicCoffee;

};
 
/* Test program */
int main() 
{
  SimpleCoffee s;
  std::cout << "Cost: " << s.getCost() << "; Ingredients: " << s.getIngredients() << std::endl;

  MilkDecorator milk(s);
  std::cout << "Cost: " << milk.getCost() << "; Ingredients: " << milk.getIngredients() << std::endl;
 
  SugarDecorator sugar(s);
  std::cout << "Cost: " << sugar.getCost() << "; Ingredients: " << sugar.getIngredients() << std::endl;
 
  // Note that you can stack decorators:
  MilkDecorator milk_sugar(sugar);
  std::cout << "Cost: " << milk_sugar.getCost() << "; Ingredients: " << milk_sugar.getIngredients() << std::endl;
  
  return 0;
}
