#include "include.hpp"
#include "quaternions.hpp"
#include "vector.hpp"
#include "math.hpp"

int main(int argc, const char * argv[]) {

    double arr[3][3];
    arr[0][0] = 1; arr[0][1] = -2; arr[0][2] = -3;
    arr[1][0] = -2; arr[1][1] = 1; arr[1][2] = -7;
    arr[2][0] = -3; arr[2][1] = -7; arr[2][2] = 1;
    
    double* sol = findEigenvalues(arr);
    //std::cout << sol[0] << ' ' << sol[1] << ' ' << sol[2];
    
    return 0;
}
