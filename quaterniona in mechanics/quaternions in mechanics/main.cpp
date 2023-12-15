#include "include.hpp"
#include "quaternions.hpp"
#include "vector.hpp"
#include "math.hpp"
#include "RigidBody.hpp"

int main() {
    // Начальные условия: углы ориентации и угловые скорости
    RigidBody body;
    body.state = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6}; // Произвольные начальные условия

    // Тензор инерции: [Ixx, Iyy, Izz]
    body.inertia = {1.0, 2.0, 3.0}; // Произвольные значения

    // Размер шага интегрирования и общая длительность интегрирования
    double dt = 0.01;
    double duration = 10.0;

    // Интегрирование и вывод результатов
    body.rungeKuttaIntegrate(body, dt, duration);

    return 0;
}
