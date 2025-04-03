#include <iostream>

class Base {
public:
    Base() { std::cout << "Base constructed\n"; }
    virtual ~Base() { std::cout << "Base destroyed\n"; }
protected:
    virtual void print() {
        std::cout << "Base print\n";
    }
    
};

class Derived1 : public Base {
public:
    Derived1() { std::cout << "Derived1 constructed\n"; }
    ~Derived1() override { std::cout << "Derived1 destroyed\n"; }
    void public_print() {
        print(); // Calls the protected print method
    }
protected:
    virtual void print() override {
        std::cout << "Derived1 print\n";
    }
};

class Derived2 : public Derived1 {
public:
    Derived2() { std::cout << "Derived2 constructed\n"; }
    ~Derived2() override { std::cout << "Derived2 destroyed\n"; }
protected:
    virtual void print() override {
        std::cout << "Derived2 print\n";
    }
};

class Derived3 : public Derived2 {
public:
    Derived3() { std::cout << "Derived3 constructed\n"; }
    ~Derived3() override { std::cout << "Derived3 destroyed\n"; }
protected:
    virtual void print() override {
        std::cout << "Derived3 print\n";
    }
};

int main() {
    std::cout << "Creating Derived3 object:\n";
    Derived3 obj;
    //obj.print(); // This will not work because print is protected
    obj.public_print(); // This will work because public_print is public
    std::cout << "Exiting main, Derived3 object will be destroyed:\n";
    return 0;
}
