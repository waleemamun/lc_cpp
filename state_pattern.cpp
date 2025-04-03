#include <iostream>
#include <memory>
#include <string>

// +--------------------+
// |      State         |  <--- Abstract Class (Interface)
// +--------------------+
// | + insertCard()     |
// | + processPayment() |
// | + ejectCard()      |
// +--------------------+
//            ^
//            |
//   +--------+--------+--------+--------+-------------------------------------+
//   |                 |                 |                                     |
// +---------------------------+   +---------------------------+   +---------------------------+
// |       IdleState           |   | PaymentProcessingState    |   | PaymentCompletedState     |
// +---------------------------+   +---------------------------+   +---------------------------+
// | + insertCard()            |   | + insertCard()            |   | + insertCard()            |
// | + processPayment()        |   | + processPayment()        |   | + processPayment()        |
// | + ejectCard()             |   | + ejectCard()             |   | + ejectCard()             |
// +---------------------------+   +---------------------------+   +---------------------------+

// +---------------------------+
// | ParkingPayMachine         |  <--- Context Class
// +---------------------------+
// | - currentState: State     |
// +---------------------------+
// | + setState(State)         |
// | + insertCard()            |
// | + processPayment()        |
// | + ejectCard()             |
// +---------------------------+

// Forward declaration of the Context class
class ParkingPayMachine;

// Abstract State class
// This class defines the interface for all concrete states
// contains all the actions that can be performed in the context
// and each action is represnted by a method
class State {
public:
    virtual ~State() = default;
    virtual void insertCard(ParkingPayMachine& machine) = 0;
    virtual void processPayment(ParkingPayMachine& machine) = 0;
    virtual void ejectCard(ParkingPayMachine& machine) = 0;
};

// Context class
class ParkingPayMachine {
private:
    std::shared_ptr<State> currentState;

public:
    ParkingPayMachine(std::shared_ptr<State> initialState) : currentState(initialState) {}

    void setState(std::shared_ptr<State> state) {
        currentState = state;
    }

    void insertCard() {
        currentState->insertCard(*this);
    }

    void processPayment() {
        currentState->processPayment(*this);
    }

    void ejectCard() {
        currentState->ejectCard(*this);
    }
};

// Concrete State: IdleState
class IdleState : public State {
public:
    void insertCard(ParkingPayMachine& machine) override {
        std::cout << "Card inserted. Transitioning to PaymentProcessingState.\n";
        machine.setState(std::make_shared<PaymentProcessingState>());
    }

    void processPayment(ParkingPayMachine& machine) override {
        std::cout << "No card inserted. Cannot process payment.\n";
    }

    void ejectCard(ParkingPayMachine& machine) override {
        std::cout << "No card to eject. Machine is idle.\n";
    }
};

// Concrete State: PaymentProcessingState
class PaymentProcessingState : public State {
public:
    void insertCard(ParkingPayMachine& machine) override {
        std::cout << "Card already inserted. Cannot insert another card.\n";
    }

    void processPayment(ParkingPayMachine& machine) override {
        std::cout << "Processing payment. Transitioning to PaymentCompletedState.\n";
        machine.setState(std::make_shared<PaymentCompletedState>());
    }

    void ejectCard(ParkingPayMachine& machine) override {
        std::cout << "Card ejected. Returning to IdleState.\n";
        machine.setState(std::make_shared<IdleState>());
    }
};

// Concrete State: PaymentCompletedState
class PaymentCompletedState : public State {
public:
    void insertCard(ParkingPayMachine& machine) override {
        std::cout << "Payment already completed. Please eject the card first.\n";
    }

    void processPayment(ParkingPayMachine& machine) override {
        std::cout << "Payment already completed. No further action required.\n";
    }

    void ejectCard(ParkingPayMachine& machine) override {
        std::cout << "Card ejected. Returning to IdleState.\n";
        machine.setState(std::make_shared<IdleState>());
    }
};

// Main function to demonstrate the State Pattern
int main() {
    auto idleState = std::make_shared<IdleState>();
    ParkingPayMachine machine(idleState);

    machine.insertCard();       // Transition to PaymentProcessingState
    machine.processPayment();   // Transition to PaymentCompletedState
    machine.ejectCard();        // Transition back to IdleState

    return 0;
}