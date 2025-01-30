#include <stdio.h>
#include <cstdlib>
#include <sstream>
using namespace std;

//             Product
//                 ^
//                 |
//     ---------------------------
//     |                         |
// ConcreteProductA        ConcreteProductB

//            Creator
//               ^
//               |
//       ConcreteCreatorA      ConcreteCreatorB


class product {
    public:
        virtual void produce() = 0;
        virtual ~product() = default;
};

class productA1 : public product {
    public:
        productA1() = default;
        void produce() override {
            printf("product A1 produce\n");
        }
};

class productA2 : public product {
    public:
        productA2() = default;
        void produce() override {
            printf("product A2 produce\n");
        }
};

class productB2 : public product {
    public:
        productB2() = default;
        void produce() override {
            printf("product B2 produce\n");
        }
};

class productB1 : public product {
    public:
        productB1() = default;
        void produce() override {
            printf("product B1 produce\n");
        }
};

class productC : public product {
    public:
        productC() = default;
        void produce() override {
            printf("product C produce\n");
        }
};

// Factory Method Interface
class product_factory {
    public:
        virtual product* createProduct(string type) = 0;
        virtual ~product_factory() = default;
};
// Concrete Factory
class product_factory_A : public product_factory {
    public:
        product* createProduct(string type) {
            product *prod = nullptr;
            if (type == "A1") {
                prod = new productA1();
            } else if (type == "A2") {
                prod = new productA2();
            } 
            return prod;
        }

};

class product_factory_B : public product_factory {
    public:
        product* createProduct(string type) {
            product *prod = nullptr;
            if (type == "B1") {
                prod = new productB1();
            } else if (type == "B2") {
                prod = new productB2();
            } 
            return prod;
        }

};

int main(){
    product_factory *factorA = new product_factory_A();
    product *prodA1 =  factorA->createProduct("A1");
    product *prodA2 =  factorA->createProduct("A2");

    product_factory *factorB = new product_factory_B();
    product *prodB1 =  factorB->createProduct("B1");
    product *prodB2 =  factorB->createProduct("B2");

    prodA1->produce();
    prodA2->produce();
    prodB1->produce();
    prodB2->produce();

    delete prodA1;
    delete prodA2;
    delete prodB1;
    delete prodB2;

    delete factorA;
    delete factorB;

    return 0;
}