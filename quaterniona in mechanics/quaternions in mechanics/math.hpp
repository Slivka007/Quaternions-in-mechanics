double* findEigenvalues(double matrix[3][3]){
    /* we look for the eigenvalues of a 3 by 3 matrix. They are real, since the inertia tensor is symmetric */
    double Ix  =  matrix[0][0];
    double Ixy = -matrix[0][1];
    double Ixz = -matrix[0][2];
    double Iy  =  matrix[1][1];
    double Iyz = -matrix[1][2];
    double Iz  =  matrix[2][2];
    
    // ax^3+bx^2+cx+d=0
    double a = -1.0;
    double b = Ix + Iy + Iz;
    double c = Ixy*Ixy + Ixz*Ixz + Iyz*Iyz - Ix*Iy - Ix*Iz - Iy*Iz;
    double d = -Ixz*Ixz*Iy - Ixy*Ixy*Iz - Iyz*Iyz*Ix - 2*Ixy*Ixz*Iyz + Ix*Iy*Iz;
    std::cout << a << ' ' << b << ' ' << c << ' ' << d << std::endl;
    // Cardano formula
    double p = (3*a*c-b*b)/(3*a*a);
    double q = (2*b*b*b-9*a*b*c+27*a*a*d)/(27*a*a*a);
    double Q = p*p*p/27 + q*q/4; // Q < 0 => we have 3 real solutions
    
    std::cout << p << ' ' << q << ' ' << Q << std::endl;
    
    if (Q == 0 && p == 0 && q == 0){
        double A = -b/(3*a);
        double B = A;
        double C = A;
        double* arr = new double[3];
        arr[0] = A; arr[1] = B; arr[2] = C;
        return arr;
    }
    else{
        std::complex<double> alpha3(-q/2, std::sqrt(-Q)); // alpha^3
        std::complex<double> beta3(-q/2, -std::sqrt(-Q)); // beta^3
        
        double alpha_abs = std::pow((std::abs(alpha3)), 1/3.0);
        double beta_abs = std::pow((std::abs(beta3)), 1/3.0);
        double alpha_phi = std::arg(alpha3) / 3.0;
        double beta_phi = std::arg(beta3) / 3.0;
        
        std::complex<double> alpha = std::polar(alpha_abs, alpha_phi);
        std::complex<double> beta = std::polar(beta_abs, beta_phi);
        
        std::complex<double> i(0, 1);
        double A = std::real(alpha + beta)- b/(3*a);
        double B = std::real(-(alpha+beta)*0.5 + std::sqrt(3)*i*(alpha-beta)*0.5) - b/(3*a);
        double C = std::real(-(alpha+beta)*0.5 - std::sqrt(3)*i*(alpha-beta)*0.5) - b/(3*a);
        double* arr = new double[3];
        arr[0] = A; arr[1] = B; arr[2] = C;
        std::cout << A << ' ' << B << ' ' << C << std::endl;
        return arr;
        
    }
}


