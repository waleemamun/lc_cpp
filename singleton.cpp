#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

class singleton {
    private:
        static singleton* instance;
        singleton() {
            printf("Singleton created\n");
        }
        singleton(const singleton&) = delete;
        singleton& operator=(const singleton&) = delete;
        static once_flag init_flag;
        static std::mutex mtx;

    public:
        static singleton* get_instance(){
            std::call_once(init_flag, [](){
                instance = new singleton();
            });
            return instance;
        }
};

singleton* singleton::instance = nullptr;
std::once_flag singleton::init_flag;
std::mutex singleton::mtx;

int main(){
    singleton *s1 = singleton::get_instance();
    singleton *s2 = singleton::get_instance();
    if (s1 == s2) {
        printf("Same object\n");
    }
    return 0;
}