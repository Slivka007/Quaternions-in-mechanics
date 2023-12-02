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
        return *this;
    }
    
    //Move assignment operator
    template <typename T1>
    Quaternion& operator=(const Quaternion<T1>&& other){
        a_ = other.a_;
        b_ = other.b_;
        c_ = other.c_;
        d_ = other.d_;
        return *this;
    }
    
    // give coord of quaternion
    T a() const { return a_; }
    T b() const { return b_; }
    T c() const { return c_; }
    T d() const { return d_; }
    
    // return real part of quaternion
    T real() const { return a_; }
    
    // return unreal part of quaternion
    Quaternion unreal () const { return Quaternion(0, b_, c_, d_); }
    
    // return list with coord quaternion
    std::array<T, 4> to_array() const {
        return {{a_, b_, c_, d_}};
      }

    // return norm quaternion in squared
    T norm_squared() const {
        return a_*a_ + b_*b_ + c_*c_ + d_*d_;
    }
    
    // return norm quaternion
    T abs() const {
        return std::sqrt(norm_squared());
    }
    
    // return norm of ureal part
    T unreal_norm_squared() const {
        return b_*b_ + c_*c_ + d_*d_;
    }
    
    // return true, if quaternion iz zero
    bool is_zero() const {
        return a_==0 && b_==0 && c_==0 && d_==0;
    }
    
    // return true if quaternion is real
    bool is_real() const {
        return b_==0 && c_==0 && d_==0;
    }
    
    // unary plus
    Quaternion operator+() const {
        return *this;
    }
    
    // unary minus
    Quaternion operator-() const {
        return {-a_, -b_, -c_, -d_};
    }
    
    // unary +=
    Quaternion operator+=(T x){
        a_ += x;
        return *this;
    }
    
    // unary -=
    Quaternion operator-=(T x){
        a_ -= x;
        return *this;
    }
    
    // scaling by a constant.
    Quaternion operator*=(T k){
        a_ *= k; b_ *= k; c_ *= k; d_ *= k;
        return *this;
    }
    
    // dividing by a constant.
    Quaternion operator/=(T k){
        a_ /= k; b_ /= k; c_ /= k; d_ /= k;
        return *this;
    }
    
    // unary +=
    template<typename T1>
    Quaternion operator+=(const std::complex<T1&> x){
        a_ += x.real();
        b_ += x.imag();
        return *this;
    }
    
    // unary -=
    template<typename T1>
    Quaternion operator-=(const std::complex<T1&> x){
        a_ -= x.real();
        b_ -= x.imag();
        return *this;
    }
    
    
    // unary *=
    template<typename T1>
    Quaternion operator*=(const std::complex<T1&> x){
        T at = a_ * x.real() - b_ * x.imag();
        T bt = a_ * x.imag() + b_ * x.real();
        T ct = c_ * x.real() + d_ * x.imag();
        T dt = -c_ * x.imag() + d_ * x.real();
        a_ = at; b_ = bt; c_ = ct; d_ = dt;
        return *this;
    }
    
    // unary +=
    template<typename T1>
    Quaternion operator+=(const Quaternion<T1>& x){
        a_ += x.a_;
        b_ += x.b_;
        c_ += x.c_;
        d_ += x.d_;
        return *this;
    }
    
    // unary -=
    template<typename T1>
    Quaternion operator-=(const Quaternion<T1>& x){
        a_ -= x.a_;
        b_ -= x.b_;
        c_ -= x.c_;
        d_ -= x.d_;
        return *this;
    }
    
    template<typename T1>
    Quaternion operator*=(const Quaternion<T1>& x){
        a_ = a_ * x.a_ - b_ * x.b_ - c_ * x.c_ - d_ * x.d_;
        b_ = a_ * x.b_ + b_ * x.a_ + c_ * x.d_ - d_ * x.c_;
        c_ = a_ * x.c_ - b_ * x.d_ + c_ * x.a_ + d_ * x.b_;
        d_ = a_ * x.d_ + b_ * x.c_ - c_ * x.b + d_ * x.a_;
        return *this;
    }
    
    
    // binary +
    Quaternion operator+(T x){
        a_ += x;
        return *this;
    }
    
    // binary -
    Quaternion operator-(T x){
        a_ -= x;
        return *this;
    }
    
    // scaling by a constant.
    Quaternion operator*(T k){
        a_ *= k; b_ *= k; c_ *= k; d_ *= k;
        return *this;
    }
    
    // dividing by a constant.
    Quaternion operator/(T k){
        a_ /= k; b_ /= k; c_ /= k; d_ /= k;
        return *this;
    }
    
    // binary +
    template<typename T1>
    Quaternion operator+(const std::complex<T1&> x){
        a_ += x.real();
        b_ += x.imag();
        return *this;
    }
    
    // binary -
    template<typename T1>
    Quaternion operator-(const std::complex<T1&> x){
        a_ -= x.real();
        b_ -= x.imag();
        return *this;
    }
    
    
    // binary *
    template<typename T1>
    Quaternion operator*(const std::complex<T1&> x){
        T at = a_ * x.real() - b_ * x.imag();
        T bt = a_ * x.imag() + b_ * x.real();
        T ct = c_ * x.real() + d_ * x.imag();
        T dt = -c_ * x.imag() + d_ * x.real();
        a_ = at; b_ = bt; c_ = ct; d_ = dt;
        return *this;
    }
    
    // binary +
    template<typename T1>
    Quaternion operator+(const Quaternion<T1>& x){
        a_ += x.a_;
        b_ += x.b_;
        c_ += x.c_;
        d_ += x.d_;
        return *this;
    }
    
    // binary -
    template<typename T1>
    Quaternion operator-(const Quaternion<T1>& x){
        a_ -= x.a_;
        b_ -= x.b_;
        c_ -= x.c_;
        d_ -= x.d_;
        return *this;
    }
    
    // binary *
    template<typename T1>
    Quaternion operator*(const Quaternion<T1>& x){
        a_ = a_ * x.a_ - b_ * x.b_ - c_ * x.c_ - d_ * x.d_;
        b_ = a_ * x.b_ + b_ * x.a_ + c_ * x.d_ - d_ * x.c_;
        c_ = a_ * x.c_ - b_ * x.d_ + c_ * x.a_ + d_ * x.b_;
        d_ = a_ * x.d_ + b_ * x.c_ - c_ * x.b_ + d_ * x.a_;
        return *this;
    }
    
    
};
