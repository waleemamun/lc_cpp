#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;


        //   +------------------+            +-------------------+
        //   |     Subject       |<>--------->|     Observer       |
        //   +------------------+            +-------------------+
        //   | +registerObserver()|           | +update()          |
        //   | +removeObserver()  |           +-------------------+
        //   | +notifyObservers() |                       
        //   +------------------+            
        //            |
        //   +----------------------+
        //   |    ConcreteSubject    |
        //   +----------------------+
        //   | - state: State        |
        //   | +getState(): State    |
        //   | +setState(State)      |
        //   +----------------------+
        //            ^
        //            |
        //   +----------------------+     +-----------------------+
        //   |    ConcreteObserver   |     |    ConcreteObserver    |
        //   +----------------------+     +-----------------------+
        //   | +update()             |     | +update()             |
        //   +----------------------+     +-----------------------+

class observer_interface {
    public:
        virtual void update(int x) = 0;
        virtual ~observer_interface() = default;  // Virtual destructor required for deleting with base pointer

};

class concrete_observerA : public observer_interface {
    private:
        int secret;
    public:
        void update (int x) override {
            secret = x;
            printf("Contrete observer A Got updates %d\n", secret);
        }
};

class concrete_observerB : public observer_interface {
    private:
        int secret;
    public:
        void update(int x) override {
            secret = x;
            printf("Contrete observer B Got updates %d\n", secret);
        }
};

class concrete_observerC : public observer_interface {
    private:
        int secret;
    public:
        void update(int x) override {
            secret = x;
            printf("Contrete observer C Got updates %d\n", secret);
        }
};

class subject_interface{
    protected:
        unordered_map<string ,observer_interface*> obs_map;
    public:
        virtual void update(int x) = 0;
        virtual void register_observer(string key, observer_interface* obs) = 0;
        virtual void unregister_observer(string key, observer_interface* obs) = 0;
        virtual ~subject_interface() = default;
};

class concrete_subject : public subject_interface {
    public:
        concrete_subject() = default;

        void update(int x) override{
            for (auto [k,v] : obs_map) {
                v->update(x);
            }
        }

        void register_observer(string key, observer_interface* obs) override{
            obs_map[key] = obs;
        }

        void unregister_observer(string key, observer_interface* obs) override{
            obs_map.erase(key);
        }
};

int main () {
    observer_interface *oa = new concrete_observerA();
    observer_interface *ob = new concrete_observerB();
    observer_interface *oc = new concrete_observerC();

    std::unique_ptr<concrete_subject> csb = std::make_unique<concrete_subject>();
    csb->register_observer("Observer A", oa);
    csb->register_observer("Observer B", ob);
    csb->register_observer("Observer C", oc);
    csb->update(10);

    csb->unregister_observer("Observer B", ob);
    csb->update(20);

    // delete all the memory in heap
    // Note the csb is not deleted manually as we have created an 
    // unique_ptr the delete will be done when it goes out of scope
    delete oa;
    oa = nullptr;
    delete ob;
    ob = nullptr;
    delete oc;
    oc = nullptr;
    return 0;
}

