 // Функция для поиска максимального элемента в матрице
void findMaxElement(const double matrix[3][3], int& row, int& col) {
    double maxElement = 0.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            if (std::abs(matrix[i][j]) > maxElement) {
                maxElement = std::abs(matrix[i][j]);
                row = i;
                col = j;
            }
        }
    }
}
 
// Функция для создания матрицы вращения
void createRotationMatrix(double matrix[3][3], int p, int q, double theta) {
    for (int i = 0; i < 3; ++i) {
        if (i != p && i != q) {
            double temp = matrix[i][p];
            matrix[i][p] = temp * std::cos(theta) - matrix[i][q] * std::sin(theta);
            matrix[i][q] = temp * std::sin(theta) + matrix[i][q] * std::cos(theta);
        }
    }
 
    for (int j = 0; j < 3; ++j) {
        if (j != p && j != q) {
            double temp = matrix[p][j];
            matrix[p][j] = temp * std::cos(theta) - matrix[q][j] * std::sin(theta);
            matrix[q][j] = temp * std::sin(theta) + matrix[q][j] * std::cos(theta);
        }
    }
 
    double temp = matrix[p][p];
    matrix[p][p] = temp * std::cos(theta) * std::cos(theta) -
        2.0 * matrix[p][q] * std::cos(theta) * std::sin(theta) +
        matrix[q][q] * std::sin(theta) * std::sin(theta);
    matrix[q][q] = temp * std::sin(theta) * std::sin(theta) +
        2.0 * matrix[p][q] * std::cos(theta) * std::sin(theta) +
        matrix[q][q] * std::cos(theta) * std::cos(theta);
 
    matrix[p][q] = matrix[q][p] = 0.0;
}
 
// Функция для вычисления собственных векторов методом Якоби
void jacobiEigenSolver(double matrix[3][3], double eigenvalues[3], double eigenvectors[3][3]) {
    const int maxIterations = 50;
    const double epsilon = 1e-10;
 
    // Инициализация собственных векторов как единичной матрицы
    for (int i = 0; i < 3; ++i) {
        eigenvalues[i] = matrix[i][i];
        for (int j = 0; j < 3; ++j) {
            eigenvectors[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
 
    int iteration = 0;
    while (iteration < maxIterations) {
        int p, q;
        findMaxElement(matrix, p, q);
 
        if (std::abs(matrix[p][q]) < epsilon) {
            break;
        }
 
        double theta = 0.5 * std::atan2(2.0 * matrix[p][q], matrix[q][q] - matrix[p][p]);
        createRotationMatrix(matrix, p, q, theta);
 
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
        eigenvalues[i] = matrix[i][i];
    }
}
 

 

