#include <stdio.h>
#include <cstdlib>
#include <sstream>
using namespace std;


// Component
//   ^                 ^             
//   |                 |             
// ConcreteComponent   Decorator
//                       ^   
//                       |
//                ConcreteDecorator

class component{
    public:
        virtual string cost() = 0;
        virtual ~component() = default; 
};

class concrete_component : public component {
    public:
        string cost() override {
            return "1 1 2";
        }
};

class decorator : public component {
    protected:
        component *comp;
    public:
        decorator(component *c) : comp(c) {}
        string cost() override {
            return comp->cost();
        }
};

class concrete_decoratorA : public decorator {
    public:
        concrete_decoratorA(component *c) : decorator(c) {} 
        string cost() override {
            return comp->cost() + " 3";
        }
};

class concrete_decoratorB : public decorator {
    public:
        concrete_decoratorB(component *c) : decorator(c) {} 
        string cost() override {
            return comp->cost() + " 5";
        }
};

class concrete_decoratorC : public decorator {
    public:
        concrete_decoratorC(component *c) : decorator(c) {} 
        string cost() override {
            return comp->cost() + " 8";
        }
};

int main(){
    component *cmp = new concrete_component();
    component *decA = new concrete_decoratorA(cmp);
    component *decB = new concrete_decoratorB(decA);
    component *decC = new concrete_decoratorC(decB);
    string output = decC->cost();
    printf("output after decoration:-> %s :: \n",output.c_str());
    delete decC;
    return 0;
}
