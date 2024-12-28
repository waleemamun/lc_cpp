#include <iostream>

class Base {
public:
    Base() { std::cout << "Base constructed\n"; }
    virtual ~Base() { std::cout << "Base destroyed\n"; }
};

class Derived1 : public Base {
public:
    Derived1() { std::cout << "Derived1 constructed\n"; }
    ~Derived1() override { std::cout << "Derived1 destroyed\n"; }
};

class Derived2 : public Derived1 {
public:
    Derived2() { std::cout << "Derived2 constructed\n"; }
    ~Derived2() override { std::cout << "Derived2 destroyed\n"; }
};

class Derived3 : public Derived2 {
public:
    Derived3() { std::cout << "Derived3 constructed\n"; }
    ~Derived3() override { std::cout << "Derived3 destroyed\n"; }
};

int main() {
    std::cout << "Creating Derived3 object:\n";
    Derived3 obj;
    std::cout << "Exiting main, Derived3 object will be destroyed:\n";
    return 0;
}
