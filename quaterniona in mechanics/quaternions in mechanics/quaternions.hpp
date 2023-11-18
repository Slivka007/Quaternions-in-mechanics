#include <iostream>

template <typename T = double>
class Quaternion{
private:
    T a_, b_, c_, d_; // Coordinates of the quaternion
public:
    //Constructors
    Quaternion(){
        a_ = 0; b_ = 0; c_ = 0; d_ = 0;
    }
    Quaternion(T a, T b, T c, T d){
        a_ = a; b_ = b; c_ = c; d_ = d;
    }
    
    //Destructor
    ~Quaternion(){
        a_ = 0; b_ = 0; c_ = 0; d_ = 0;
    }
    
    //Copy constructor
    template <typename T1>
    Quaternion(const Quaternion<T1>& other){
        a_ = other.a_;
        b_ = other.b_;
        c_ = other.c_;
        d_ = other.d_;
    }
    
    //Move constructor, noexcept - для оптимизации при исполользовании стандартных контейнеров
    template <typename T1>
    Quaternion(Quaternion<T1>&& other) noexcept {
        a_ = other.a_;
        b_ = other.b_;
        c_ = other.c_;
        d_ = other.d_;
    }
    
    //Copy assignment operator
    template <typename T1>
    Quaternion& operator=(const Quaternion<T1>& other){
        a_ = other.a_;
        b_ = other.b_;
        c_ = other.c_;
        d_ = other.d_;
        return *this
    }
    
    //Move assignment operator
    template <typename T1>
    Quaternion& operator=(const Quaternion<T1>&& other){
        a_ = other.a_;
        b_ = other.b_;
        c_ = other.c_;
        d_ = other.d_;
        return *this
    }
    
};
