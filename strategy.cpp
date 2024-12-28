#include <stdio.h>
#include <cstdlib>
#include <sstream>
using namespace std;

class strategy_interface {
    public: 
        virtual void execute() = 0;
        virtual ~strategy_interface() = default;
};

class concrte_strategyA : public strategy_interface {
    public:
        concrte_strategyA() = default;
        void execute() {
            printf("concrete strategy -> 'A'\n");
        }
};

class concrte_strategyB : public strategy_interface {
    public:
        concrte_strategyB() = default;
        void execute() {
            printf("concrete strategy -> 'B' \n");
        }
};

class subject_interface {
    protected:
        strategy_interface *st;
    public:
        virtual void set_strategy(strategy_interface *st) = 0;
        virtual void execute() = 0;
        virtual ~subject_interface() = default;
};

class concrete_subject : public subject_interface {
    private:
        int val;
        string info;
    public:
        concrete_subject() = default;
        concrete_subject(strategy_interface *st, int v, string i) : val(v), info(i) {this->st = st;}
        void set_strategy(strategy_interface *st) {
            this->st = st;
        }
        void execute() {
            printf("my value = %d\n", val);
            st->execute();
        }
        void non_virt_func() {
            printf("I am non-virtual func of %s\n",info.c_str());
        }
};

int main(){
    // strategy pattern where we can use different features(strategy) 
    // without impacting the subject code
    unique_ptr<strategy_interface> sta = std::make_unique<concrte_strategyA>();
    unique_ptr<strategy_interface> stb = std::make_unique<concrte_strategyB>();
    subject_interface *sbj_a  = new concrete_subject(sta.get(), 1, "Subject A");
    subject_interface *sbj_b  = new concrete_subject(stb.get(), 2, "Subject B");
    sbj_a->execute();
    sbj_b->execute();

    // not part of stratefy pattern
    // but here we are dynamic downcasting the polymorhic base class to derived class
    concrete_subject* cn_sbj = dynamic_cast<concrete_subject*>(sbj_a);
    if (cn_sbj)
        cn_sbj->non_virt_func();
    else {
        printf("Failed to do dynamic cast as the downcast is not based type\n");
    }
    // note how we only need to delete sbj_a and sbj_b but not the sta and stb
    // because sta and stb are unique+ptr
    delete sbj_a;
    delete sbj_b;
    sbj_a = nullptr;
    sbj_b = nullptr;
    return 0;
}
