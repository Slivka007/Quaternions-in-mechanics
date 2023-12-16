template <typename T = double>

class Vector {
private:
    T x_;
    T y_;
    T z_;
public:
    // Constructors
    Vector() {
        x_ = 0.0;
        y_ = 0.0;
        z_ = 0.0;
    }

    Vector(T x, T y, T z) {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    // return norm quaternion
    T abs() const {
        return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    T x() const { return x_; }
    T y() const { return y_; }
    T z() const { return z_; }

    template<typename T1 = T>
    Vector operator+(const Vector<T1>& other) {
        Vector sum;
        sum.x_ = x_ + other.x_;
        sum.y_ = y_ + other.y_;
        sum.z_ = z_ + other.z_;
        return sum;
    }


    template<typename T1>
    Vector operator*(double lambda) {
        Vector<T> result;
        result.x = x_ * lambda;
        result.y = y_ * lambda;
        result.z = z_ * lambda;
        return result;
    }


    template<typename T1, typename T2>
    double scalar_product(Vector<T1>& vector1, Vector<T2>& vector2) {
        return vector1.x_ * vector2.x_ + vector1.y_ * vector2.y_ + vector1.z_ * vector2.z_;
    }

    template<typename T1>
    Vector<T1> vector_product(Vector<T1>& vector1, Vector<T1>& vector2) {
        Vector<T1> result;
        result.x_ = vector1.y_ * vector2.z_ - vector1.z_ * vector2.y_;
        result.y_ = vector1.z_ * vector2.x_ - vector1.x_ * vector2.z_;
        result.z_ = vector1.x_ * vector2.y_ - vector1.y_ * vector2.x_;
        return result;
    }


    Vector<T> norm() {
        T xt = x_ / ((*this).abs());
        T yt = y_ / ((*this).abs());
        T zt = z_ / ((*this).abs());
        x_ = xt; y_ = yt; z_ = zt;
        return *this;
    }
};
