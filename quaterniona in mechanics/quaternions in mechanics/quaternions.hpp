template <typename T = double>
class Quaternion {
private:
    T a_, b_, c_, d_; // Coordinates of the quaternion
public:
    //Constructors
    Quaternion() {
        a_ = 0.0; b_ = 0.0; c_ = 0.0; d_ = 0.0;
    }
    Quaternion(T a, T b, T c, T d) {
        a_ = a; b_ = b; c_ = c; d_ = d;
    }
    
    // give coord of quaternion
    T a() const { return a_; }
    T b() const { return b_; }
    T c() const { return c_; }
    T d() const { return d_; }

    /*
    // return list with coord quaternion
    std::array<T, 4> to_array() const {
        return { {a_, b_, c_, d_} };
    }
    */
    // return norm quaternion in squared
    T norm_squared() const {
        return a_ * a_ + b_ * b_ + c_ * c_ + d_ * d_;
    }

    // return norm quaternion
    T abs() const {
        return std::sqrt(norm_squared());
    }

    // return norm of unreal part
    T unreal_norm_squared() const {
        return b_ * b_ + c_ * c_ + d_ * d_;
    }

    // return true, if quaternion iz zero
    bool is_zero() const {
        return a_ == 0 && b_ == 0 && c_ == 0 && d_ == 0;
    }

    // return true if quaternion is real
    bool is_real() const {
        return b_ == 0 && c_ == 0 && d_ == 0;
    }

    // unary plus
    Quaternion operator+() const {
        return *this;
    }

    // unary minus
    Quaternion operator-() const {
        return Quaternion(-a_, -b_, -c_, -d_);
    }

    
    // scaling by a constant.
    Quaternion operator*=(T k) {
        a_ *= k; b_ *= k; c_ *= k; d_ *= k;
        return *this;
    }

    // dividing by a constant.
    Quaternion operator/=(T k) {
        a_ /= k; b_ /= k; c_ /= k; d_ /= k;
        return *this;
    }


    // unary +=
    template<typename T1>
    Quaternion operator+=(const Quaternion<T1>& x) {
        a_ += x.a();
        b_ += x.b();
        c_ += x.c();
        d_ += x.d();
        return *this;
    }

    // unary -=
    template<typename T1>
    Quaternion operator-=(const Quaternion<T1>& x) {
        a_ -= x.a_;
        b_ -= x.b_;
        c_ -= x.c_;
        d_ -= x.d_;
        return *this;
    }


    // binary +
    template<typename T1>
    Quaternion operator+(const Quaternion<T1>& x) {
        a_ += x.a_;
        b_ += x.b_;
        c_ += x.c_;
        d_ += x.d_;
        return *this;
    }

    // binary -
    template<typename T1>
    Quaternion operator-(const Quaternion<T1>& x) {
        a_ -= x.a_;
        b_ -= x.b_;
        c_ -= x.c_;
        d_ -= x.d_;
        return *this;
    }
    
    // binary *
    template<typename T1>
    Quaternion operator*(const Quaternion<T1>& x) {
        T at = a_ * x.a_ - b_ * x.b_ - c_ * x.c_ - d_ * x.d_;
        T bt = a_ * x.b_ + b_ * x.a_ + c_ * x.d_ - d_ * x.c_;
        T ct = a_ * x.c_ - b_ * x.d_ + c_ * x.a_ + d_ * x.b_;
        T dt = a_ * x.d_ + b_ * x.c_ - c_ * x.b_ + d_ * x.a_;
        a_ = at; b_ = bt; c_ = ct; d_ = dt;
        return *this;
    }

    //return conjugated quaternion
    Quaternion conjugate() const { return Quaternion(a_,-b_,-c_,-d_);

};

// Создание кватерниона поворота вокруг оси (x, y, z) на угол angle в радианах
static Quaternion rotationQuaternion(T angle, T x, T y, T z) {
    T sin_half_angle = std::sin(angle / 2.0);
    return Quaternion(std::cos(angle / 2.0), x * sin_half_angle, y * sin_half_angle, z * sin_half_angle);
}

// Поворот вектора (vx, vy, vz) при помощи кватерниона rotation
static void rotateVector(T& vx, T& vy, T& vz, Quaternion& rotation) {
    Quaternion vec_quat(0, vx, vy, vz);
    Quaternion result = rotation * vec_quat * rotation.conjugate();

    vx = result.b();
    vy = result.c();
    vz = result.d();
}
};
