#include <iostream>
#include <type_traits>
#include "module_check.h"

class A {
public:
    void method(double d) const {
        std::cout<<d<<'\n';
    }
};

class B {
public:
    void method(int i) const {
        std::cout<<i<<'\n';
    }
};

module_check_t(perform_method_1, method);
module_check(perform_method_2, method, int);

class SmartClass {
public:
    template <typename T, typename = typename std::enable_if<module_check_perform_method_1<T, void, double>::value>::type>
    SmartClass(const T& object_with_arg_type_double, double value) {
        object_with_arg_type_double.method(value);
        std::cout<<"SmartClass init with object which can performs method(double)\n";
    }
};

class StupidClass {
public:
    template <typename T>
    StupidClass(const T& noob_object, double value) {
        noob_object.method(value);
    }
};

int main(int argc, const char * argv[]) {
    std::cout<<module_check_perform_method_1<A, void, double>::value<<'\n'; // true
    std::cout<<module_check_perform_method_1<A, void>::value<<'\n';         // false due to arg type does not match
    std::cout<<module_check_perform_method_1<B, void, int>::value<<'\n';    // true
    std::cout<<module_check_perform_method_1<B, void>::value<<'\n';         // false due to arg type does not match
    
    A a;
    SmartClass smart1(a, 2.33);
    SmartClass smart2(a, 233);      // 233 implicit cast to double
    StupidClass stupid1(a, 2.33);

    B b;
//    SmartClass smart3(b, 233);    // this line won't compile
//    SmartClass smart4(b, 2.33);   // this line won't compile
    StupidClass stupid2(b, 2.33); // 2.33 cast to int when method_1 called
    
    return 0;
}
