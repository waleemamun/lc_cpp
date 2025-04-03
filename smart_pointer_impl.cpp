#include <iostream>
#include <memory>
using namespace std;

template<typename T>
class SharedPointer {
private:
    T* ptr;            // Pointer to the managed object
    int* ref_count;     // Pointer to the reference count

public:
    // Constructor
    explicit SharedPointer(T* p = nullptr) : ptr(p), ref_count(new int(1)) {
        if (ptr == nullptr) {
            *ref_count = 0;
        }
        std::cout << "Constructor: ref_count = " << *ref_count << std::endl;
    }

    // Copy Constructor
    SharedPointer(const SharedPointer<T>& other) {
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ptr != nullptr) {
            ++(*ref_count);  // Increase the reference count
        }
        std::cout << "Copy Constructor: ref_count = " << *ref_count << std::endl;
    }

    // Move Constructor
    SharedPointer(SharedPointer<T>&& other) noexcept {
        ptr = other.ptr;
        ref_count = other.ref_count;
        other.ptr = nullptr;          // Reset other
        other.ref_count = nullptr;
        std::cout << "Move Constructor: ref_count = " << (*ref_count) << std::endl;
    }

    // Destructor
    ~SharedPointer() {
        release();
    }

    // Copy Assignment Operator
    SharedPointer<T>& operator=(const SharedPointer<T>& other) {
        if (this != &other) {        // Avoid self-assignment
            release();               // Release the old object
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ptr != nullptr) {
                ++(*ref_count);      // Increase the reference count
            }
            std::cout << "Copy Assignment: ref_count = " << *ref_count << std::endl;
        }
        return *this;
    }

    // Move Assignment Operator
    SharedPointer<T>& operator=(SharedPointer<T>&& other) noexcept {
        if (this != &other) {
            release();                // Release the old object
            ptr = other.ptr;          // Take ownership of other's pointer
            ref_count = other.ref_count;

            other.ptr = nullptr;      // Reset the other pointer
            other.ref_count = nullptr;

            std::cout << "Move Assignment: ref_count = " << (ref_count ? *ref_count : 0) << std::endl;
        }
        return *this;
    }
    // Equality operator
    bool operator==(const SharedPointer<T>& other) const {
        return ptr == other.ptr;
    }
    bool operator==(const T* other) const {
        return ptr == other;
    }
    // Inequality operator
    bool operator!=(const SharedPointer<T>& other) const {
        return ptr != other.ptr;
    }
    bool operator!=(const T* other) const {
        return ptr != other;
    }

    // Dereference operator
    T& operator*() const {
        return *ptr;
    }

    // Arrow operator
    T* operator->() const {
        return ptr;
    }

    // Get the current reference count
    int getRefCount() const {
        return (ref_count) ? *ref_count : 0;
    }

private:
    // Release the object (decrease ref count and delete if necessary)
    void release() {
        if (ptr) {
            --(*ref_count);  // Decrease the reference count
            std::cout << "Release: ref_count = " << *ref_count << std::endl;

            // If reference count reaches zero, delete the managed object
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
                ptr = nullptr;
                ref_count = nullptr;
                std::cout << "Object destroyed" << std::endl;
            }
        }
    }
};


// Example usage
class DummyClass {
public:
    int data;
    DummyClass(int d) : data(d) { std::cout << "DummyClass Constructor with data: " << data << "\n"; }
    DummyClass() : data(10) { std::cout << "DummyClass Constructor\n"; }
    ~DummyClass() { std::cout << "DummyClass Destructor\n"; }
};

unique_ptr<DummyClass> createDummy(int data) {
    unique_ptr<DummyClass> ptr = std::make_unique<DummyClass>(data);
    // Warning will be generated :moving a local object in a return statement prevents copy elision
    // c17 and later allow copy elision which makes this std::move unnecessary
    return std::move(ptr); 
}
unique_ptr<DummyClass> createDummyV2(int data) {
    unique_ptr<DummyClass> ptr = std::make_unique<DummyClass>(data);
    return ptr;
}


int main() {
    SharedPointer<DummyClass> sp1(new DummyClass());  // sp1 manages DummyClass object
    //scope of sp2 starts
    {
        SharedPointer<DummyClass> sp2 = sp1;       // sp2 shares ownership
        std::cout << "Reference Count: after sp2 creation " << sp2.getRefCount() << std::endl;  // Output: 2
    }
    // sp2 goes out of scope, ref_count decreases
    std::cout << "Reference Count after sp2 goes out of scope: " << sp1.getRefCount() << std::endl;  // Output: 1
    SharedPointer<DummyClass> sp3 = std::move(sp1);  // Move ownership to sp3
    std::cout << "Reference Count after move to sp3: " << sp3.getRefCount() << std::endl;  // Output: 1
    if (sp1 == nullptr) {
        std::cout << "sp1 is null after move" << std::endl;  // sp1 is now null
    }
    unique_ptr<DummyClass> dummy = createDummy(101);
    std::cout << "DummyClass data: " << dummy->data << "\n";  // Output: 101
    unique_ptr<DummyClass> dummy2 = createDummyV2(102);  
    std::cout << "DummyClass data: " << dummy2->data << "\n";  // Output: 101
    return 0;
}
