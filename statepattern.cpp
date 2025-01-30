#include <iostream>
#include <memory>


// The State design pattern is used to allow an object to change its behavior when its internal state changes. 
// This pattern is particularly useful when an object has multiple states and must change its behavior based on the state it is in.
// Let’s create a simple example to demonstrate the State pattern with state transitions.

// Scenario: Vending Machine
// Imagine a vending machine with three states:

// NoCoinInsertedState: No coin is inserted, and the machine is idle.
// CoinInsertedState: A coin has been inserted, and the machine is ready to dispense an item.
// ItemDispensedState: An item has been dispensed, and the machine is ready to go back to idle.
// The vending machine transitions between these states based on specific actions: inserting a coin, selecting an item, and dispensing an item.

//            +--------------------+
//            |     State          |  (Abstract Base Class)
//            +--------------------+
//            | +insertCoin()      |
//            | +selectItem()      |
//            | +dispenseItem()    |
//            +--------------------+
//                     ▲
//       ┌────────────┼─────────────┐
//       │            │             │
// +----------------+ +------------------+ +-------------------+
// | NoCoinInserted | | CoinInsertedState | | ItemDispensedState |
// +----------------+ +------------------+ +-------------------+
// | +insertCoin()  | | +insertCoin()     | | +insertCoin()     |
// | +selectItem()  | | +selectItem()     | | +selectItem()     |
// | +dispenseItem()| | +dispenseItem()   | | +dispenseItem()   |
// +----------------+ +------------------+ +-------------------+
//                     ▲
//                     │
//        +------------------------+
//        |     VendingMachine     |  (Context)
//        +------------------------+
//        | - state: shared_ptr<State> |
//        +------------------------+
//        | +setState(State*)      |
//        | +insertCoin()          |
//        | +selectItem()          |
//        | +dispenseItem()        |
//        +------------------------+


// Forward declare the VendingMachine class
class VendingMachine;

// Base state class aka state interface 
class State {
public:
    virtual void insertCoin(VendingMachine& machine) = 0;
    virtual void selectItem(VendingMachine& machine) = 0;
    virtual void dispenseItem(VendingMachine& machine) = 0;
    virtual ~State() = default;
};

// Concrete State classes
class NoCoinInsertedState : public State {
public:
    void insertCoin(VendingMachine& machine) override;
    void selectItem(VendingMachine& machine) override;
    void dispenseItem(VendingMachine& machine) override;
};

class CoinInsertedState : public State {
public:
    void insertCoin(VendingMachine& machine) override;
    void selectItem(VendingMachine& machine) override;
    void dispenseItem(VendingMachine& machine) override;
};

class ItemDispensedState : public State {
public:
    void insertCoin(VendingMachine& machine) override;
    void selectItem(VendingMachine& machine) override;
    void dispenseItem(VendingMachine& machine) override;
};

// Context class
class VendingMachine {
    std::shared_ptr<State> state;
public:
    VendingMachine() : state(std::make_shared<NoCoinInsertedState>()) {}
    
    void setState(std::shared_ptr<State> newState) {
        state = newState;
    }

    void insertCoin() {
        state->insertCoin(*this);
    }

    void selectItem() {
        state->selectItem(*this);
    }

    void dispenseItem() {
        state->dispenseItem(*this);
    }
};

// Implement state behavior and transitions
void NoCoinInsertedState::insertCoin(VendingMachine& machine) {
    std::cout << "Coin inserted.\n";
    machine.setState(std::make_shared<CoinInsertedState>());
}

void NoCoinInsertedState::selectItem(VendingMachine&) {
    std::cout << "Insert coin first.\n";
}

void NoCoinInsertedState::dispenseItem(VendingMachine&) {
    std::cout << "Insert coin first.\n";
}

void CoinInsertedState::insertCoin(VendingMachine&) {
    std::cout << "Coin already inserted.\n";
}

void CoinInsertedState::selectItem(VendingMachine& machine) {
    std::cout << "Item selected.\n";
    machine.setState(std::make_shared<ItemDispensedState>());
}

void CoinInsertedState::dispenseItem(VendingMachine&) {
    std::cout << "Select an item first.\n";
}

void ItemDispensedState::insertCoin(VendingMachine&) {
    std::cout << "Please take your item first.\n";
}

void ItemDispensedState::selectItem(VendingMachine&) {
    std::cout << "Please take your item first.\n";
}

void ItemDispensedState::dispenseItem(VendingMachine& machine) {
    std::cout << "Item dispensed.\n";
    machine.setState(std::make_shared<NoCoinInsertedState>());
}

int main() {
    VendingMachine vendingMachine;
    
    vendingMachine.selectItem();       // Insert coin first.
    vendingMachine.insertCoin();       // Coin inserted.
    vendingMachine.selectItem();       // Item selected.
    vendingMachine.insertCoin();       // Please take your item first.
    vendingMachine.dispenseItem();     // Item dispensed.
    vendingMachine.insertCoin();       // Coin inserted.
    
    return 0;
}
