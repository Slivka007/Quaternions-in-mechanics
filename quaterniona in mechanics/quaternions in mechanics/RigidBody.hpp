// Структура, представляющая твердое тело
struct RigidBody {
public:
    std::vector<double> state;    // Состояние: [углы Эйлера, угловые скорости]
    std::vector<double> inertia;  // Тензор инерции в главных осях: [Ixx, Iyy, Izz]
 
    // Метод Рунге-Кутты четвертого порядка
    void rungeKuttaIntegrate(RigidBody& body, double dt, double duration) {
        for (double t = 0; t < duration; t += dt) {
            // Вывод текущего состояния
            std::cout << t << "\t";
            for (double val : body.state) {
                std::cout << val << "\t";
            }
            std::cout << std::endl;
 
            // Расчет коэффициентов метода Рунге-Кутты
            std::vector<double> k1(6), k2(6), k3(6), k4(6);
            std::vector<double> tempState(6);
 
            // Первый шаг
            eulerDynamics(body, k1, t);
 
            // Второй шаг
            for (int i = 0; i < 6; ++i) {
                tempState[i] = body.state[i] + k1[i] * dt / 2.0;
            }
            eulerDynamics({ tempState, body.inertia }, k2, t + dt / 2.0);
 
            // Третий шаг
            for (int i = 0; i < 6; ++i) {
                tempState[i] = body.state[i] + k2[i] * dt / 2.0;
            }
            eulerDynamics({ tempState, body.inertia }, k3, t + dt / 2.0);
 
            // Четвертый шаг
            for (int i = 0; i < 6; ++i) {
                tempState[i] = body.state[i] + k3[i] * dt;
            }
            eulerDynamics({ tempState, body.inertia }, k4, t + dt);
 
            // Интегрирование
            for (int i = 0; i < 6; ++i) { 
                body.state[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) * dt / 6.0;
            }
        }
    }
private:
    // Функция, представляющая динамические уравнения Эйлера для твердого тела
    void eulerDynamics(const RigidBody& body, std::vector<double>& deriv, double /*time*/) {
        // Извлечение параметров тела
        double Ixx = body.inertia[0];
        double Iyy = body.inertia[1];
        double Izz = body.inertia[2];
 
        // Извлечение текущих углов ориентации и угловых скоростей
        double phi = body.state[0];
        double theta = body.state[1];
        double psi = body.state[2];
        double p = body.state[3];
        double q = body.state[4];
        double r = body.state[5];
 
        // Динамические уравнения Эйлера для твердого тела
        deriv[0] = r - (q * sin(phi) + q * cos(phi)) / tan(theta);
        deriv[1] = p * cos(phi) - q * sin(phi);
        deriv[2] = (p * sin(phi) + q * cos(phi)) / sin(theta);
        deriv[3] = (Iyy - Izz) * q * r / Ixx;
        deriv[4] = (Izz - Ixx) * p * r / Iyy;
        deriv[5] = (Ixx - Iyy) * p * q / Izz;
    }
 
};
