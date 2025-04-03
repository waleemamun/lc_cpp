#include <iostream>
#include <vector>

class Base {
public:
    int a;
    int b;
    int c;
    Base(int a, int b, int c) : a(a), b(b), c(c) {
        std::cout << "Base constructed with a: " << a << ", b: " << b << ", c: " << c << "\n";
    }
    int print_myself() {
        std::cout << "Printing Base object state:\n";
        std::cout << "Base: a: " << a << ", b: " << b << ", c: " << c << "\n";
        return 0;
    }
    void declare_myself() {
        std::cout << "I am Base\n";
    }
    Base() { std::cout << "Base constructed\n"; }
    virtual ~Base() { std::cout << "Base destroyed\n"; }
};

class Derived1 : public Base {
public:
    int d;
    Derived1(int a, int b, int c, int d) : Base(a, b, c), d(d) {
        std::cout << "Derived1 constructed with d: " << d << "\n";
    }
    int print_myself() {
        std::cout << "Printing Derived1 object state:\n";
        std::cout << "Derived1: a: " << a << ", b: " << b << ", c: " << c << ", d: " << d << "\n";
        return 0;
    }
    ~Derived1() override { std::cout << "Derived1 destroyed\n"; }
};

int main() {
    std::cout << "Creating Derived1 object:\n";
    Derived1 obj(1, 2, 3, 4);
    obj.print_myself(); // This will call Derived1 print_myself asi it is hidding Base print_myself
    obj.declare_myself();
    std::cout << "Calling Base's print_myself explicitly:\n";
    obj.Base::print_myself(); // Call Base's print_myself explicitly 

    std::cout << "Creating Base pointer to Derived1 object:\n";
    Base* basePtr = new Derived1(5, 6, 7, 8);
    basePtr->print_myself(); // This will call Base print_myself
                             // because Base::print_myself is not virtual
    basePtr->declare_myself();
    delete basePtr; // This will call Derived1 destructor first, then Base destructor
    // Note: If you don't delete the basePtr, it will cause a memory leak.
    std::cout << "Exiting main, Derived1 object will be destroyed:\n";
    return 0;
}