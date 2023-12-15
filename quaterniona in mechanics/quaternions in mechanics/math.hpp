// Класс матриц 3 на 3
template <typename T>
class Matrix{
private:
    std::vector<T> data_[3][3];
public:
    // Копирующий конструктор
    Matrix(const Matrix& other) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                data_[i][j] = other.data_[i][j];
            }
        }
    }
    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    data_[i][j] = other.data_[i][j];
                }
            }
        }
        return *this;
    }
    // Деструктор
    ~Matrix(){}
    
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
            findMaxElement(data_, p, q);
     
            if (std::abs(data_[p][q]) < epsilon) {
                break;
            }
     
            double theta = 0.5 * std::atan2(2.0 * data_[p][q], data_[q][q] - data_[p][p]);
            createRotationMatrix(data_, p, q, theta);
     
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
