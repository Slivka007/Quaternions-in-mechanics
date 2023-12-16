// Класс матриц 3 на 3
template <typename T=double>
class Matrix{
public:
     double data_[3][3];
    // Функция для поиска максимального элемента в матрице
    void findMaxElement(int& row, int& col) {
        double maxElement = 0.0;
        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                if (std::abs(data_[i][j]) > maxElement) {
                    maxElement = std::abs(data_[i][j]);
                    row = i;
                    col = j;
                }
            }
        }
    }
     
    // Функция для создания матрицы вращения
    void createRotationMatrix(int p, int q, double theta) {
        for (int i = 0; i < 3; ++i) {
            if (i != p && i != q) {
                double temp = data_[i][p];
                data_[i][p] = temp * std::cos(theta) - data_[i][q] * std::sin(theta);
                data_[i][q] = temp * std::sin(theta) + data_[i][q] * std::cos(theta);
            }
        }
     
        for (int j = 0; j < 3; ++j) {
            if (j != p && j != q) {
                double temp = data_[p][j];
                data_[p][j] = temp * std::cos(theta) - data_[q][j] * std::sin(theta);
                data_[q][j] = temp * std::sin(theta) + data_[q][j] * std::cos(theta);
            }
        }
     
        double temp = data_[p][p];
        data_[p][p] = temp * std::cos(theta) * std::cos(theta) -
            2.0 * data_[p][q] * std::cos(theta) * std::sin(theta) +
        data_[q][q] * std::sin(theta) * std::sin(theta);
        data_[q][q] = temp * std::sin(theta) * std::sin(theta) +
            2.0 * data_[p][q] * std::cos(theta) * std::sin(theta) +
        data_[q][q] * std::cos(theta) * std::cos(theta);
     
        data_[p][q] = data_[q][p] = 0.0;
    }
     
    // Функция для вычисления собственных векторов методом Якоби
    void jacobiEigenSolver(double eigenvalues[3], double eigenvectors[3][3]) {
        const int maxIterations = 50;
        const double epsilon = 1e-10;
     
        // Инициализация собственных векторов как единичной матрицы
        for (int i = 0; i < 3; ++i) {
            eigenvalues[i] = data_[i][i];
            for (int j = 0; j < 3; ++j) {
                eigenvectors[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
     
        int iteration = 0;
        while (iteration < maxIterations) {
            int p, q;
            findMaxElement(p, q);
     
            if (std::abs(data_[p][q]) < epsilon) {
                break;
            }
     
            double theta = 0.5 * std::atan2(2.0 * data_[p][q], data_[q][q] - data_[p][p]);
            createRotationMatrix(p, q, theta);
     
            // Обновление собственных векторов
            for (int i = 0; i < 3; ++i) {
                double temp = eigenvectors[i][p];
                eigenvectors[i][p] = temp * std::cos(theta) - eigenvectors[i][q] * std::sin(theta);
                eigenvectors[i][q] = temp * std::sin(theta) + eigenvectors[i][q] * std::cos(theta);
            }
     
            ++iteration;
        }
     
        // Запись собственных значений после преобразований
        for (int i = 0; i < 3; ++i) {
            eigenvalues[i] = data_[i][i];
        }
    }
    
};

double* findEigenvalues(double data_[3][3]){
     /* Поиск собственных значний симметричной матрицы*/
     double Ix  =  data_[0][0];
     double Ixy = -data_[0][1];
     double Ixz = -data_[0][2];
     double Iy  =  data_[1][1];
     double Iyz = -data_[1][2];
     double Iz  =  data_[2][2];

     // ax^3+bx^2+cx+d=0
     double a = -1.0;
     double b = Ix + Iy + Iz;
     double c = Ixy*Ixy + Ixz*Ixz + Iyz*Iyz - Ix*Iy - Ix*Iz - Iy*Iz;
     double d = -Ixz*Ixz*Iy - Ixy*Ixy*Iz - Iyz*Iyz*Ix - 2*Ixy*Ixz*Iyz + Ix*Iy*Iz;
     // Cardano formula
     double p = (3*a*c-b*b)/(3*a*a);
     double q = (2*b*b*b-9*a*b*c+27*a*a*d)/(27*a*a*a);
     double Q = p*p*p/27 + q*q/4; // Q < 0 => we have 3 real solutions


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
         //std::cout << A << ' ' << B << ' ' << C << std::endl;
         return arr;

     }
 }
