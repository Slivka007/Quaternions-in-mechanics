void simulation(){
    double I_x, I_y, I_z, I_xy, I_xz, I_yz;
    std::cout << "Введите осевые моменты инерции твёрдого тела:" << std::endl << "I_x=";
    std::cin >> I_x;
    std::cout << "I_y=";
    std::cin >> I_y;
    std::cout << "I_z=";
    std::cin >> I_z;
    std::cout << "Введите центробежные моменты инерции твёрдого тела:" << std::endl << "I_xy=";
    std::cin >> I_xy;
    std::cout << "I_xz=";
    std::cin >> I_xz;
    std::cout << "I_yz=";
    std::cin >> I_yz;
    Matrix<double> inertial; // тензор инерции твёрдого тела
    double I[3][3];
    I[0][0] =  I_x;   I[0][1] = -I_xy; I[0][2] = -I_xz;
    I[1][0] = -I_xy;  I[1][1] =  I_y;  I[1][2] = -I_yz;
    I[2][0] = -I_xz;  I[2][1] = -I_yz; I[2][2] =  I_z;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            inertial.data_[i][j] = I[i][j];
        }
    }
    double I_diag[3]; // диагональные элементы матрицы
    double OwnBasis[3][3];
    inertial.jacobiEigenSolver(I_diag, OwnBasis);
    double A, B, C;
    A = I_diag[0];
    B = I_diag[1];
    C = I_diag[2];
    std::cout << "Элементы диагонализированного тензора инреции: " << A << ' ' << B << ' ' << C << std::endl;

    
    double phi_0, psi_0, theta_0, p_0, q_0, r_0;
    std::cout << "Введите начальные углы Эйлера твёрдого тела [рад]:" << std::endl << "phi_0=";
    std::cin >> phi_0;
    std::cout << "theta_0=";
    std::cin >> theta_0;
    std::cout << "psi_0=";
    std::cin >> psi_0;
    std::cout << "Введите начальные компоненты вектора угловой скорости тела [с^{-1}]:" << std::endl << "p_0=";
    std::cin >> p_0;
    std::cout << "q_0=";
    std::cin >> q_0;
    std::cout << "r_0=";
    std::cin >> r_0;
    // Начальные условия: углы ориентации и угловые скорости
    RigidBody body;
    body.state = {phi_0, theta_0, psi_0, p_0, q_0, r_0}; // Произвольные начальные условия

    // Тензор инерции: [Ixx, Iyy, Izz]
    body.inertia = {A, B, C};

    // Размер шага интегрирования и общая длительность интегрирования
    double dt = 0.01;
    double duration = 10.0;

    // Интегрирование и вывод результатов
    body.rungeKuttaIntegrate(body, dt, duration);
}
