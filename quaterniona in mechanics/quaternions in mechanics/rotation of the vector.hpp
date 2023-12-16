void rotation(){
    // Задаем вектор, который будем вращать
    double vx, vy, vz;
    std::cout << "Введите координаты вектора, который будете вращать:" << std::endl << "v_x=";
    std::cin >> vx;
    std::cout << "v_y=";
    std::cin >> vy;
    std::cout << "v_z=";
    std::cin >> vz;
    Vector<> vector(vx, vy, vz);
    vector = vector.norm();
    // Задаём вектор, вокруг которого будем вращать
    double axisX, axisY, axisZ;
    std::cout << "Введите координаты вектора, который будете вращать:" << std::endl << "axisX=";
    std::cin >> axisX;
    std::cout << "axisY=";
    std::cin >> axisY;
    std::cout << "axisZ=";
    std::cin >> axisZ;
    
    Vector<> axis(axisX, axisY, axisZ);
    axis = axis.norm();

    // Угол вращения в радианах
    double angle = M_PI / 2.0;

    // Создаем кватернион поворота
    Quaternion<> rotation = Quaternion<>::rotationQuaternion(angle, axis.x(), axis.y(), axis.z());

    // Поворачиваем вектор
    Quaternion<>::rotateVector(vx, vy, vz, rotation);

    // Выводим результат
    std::cout << "Координаты повернутого вектора: (" << vx << ", " << vy << ", " << vz << ")\n";
}
