#include "include.hpp"
#include "quaternions.hpp"
#include "vector.hpp"

int main(int argc, const char * argv[]) {
    Quaternion<double> a(1, 2, 3, 4);
    Quaternion<double> b(5, 6, 7, 8);
    Quaternion<double> c;
    c = a + b;
    std::cout << c.a() << ' ' << c.b() << ' ' << c.c() << ' ' << c.d() << std::endl;
    c = a * b;
    std::cout << c.a() << ' ' << c.b() << ' ' << c.c() << ' ' << c.d() << std::endl;
    
    Vector<int> f1(1, 2, 3);
    Vector<int> f2(1, 2, 3);
    Vector<int> f3;
    f3 = f1 + f2;
    
    return 0;
}
