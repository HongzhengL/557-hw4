#include <iomanip>
#include <iostream>

#include "MatMatMultiply.h"
#include "Timer.h"
#include "Utilities.h"

int main(int argc, char *argv[]) {
    float *Araw = static_cast<float *>(AlignedAllocate(MATRIX_SIZE * MATRIX_SIZE * sizeof(float), 64));
    float *Braw = static_cast<float *>(AlignedAllocate(MATRIX_SIZE * MATRIX_SIZE * sizeof(float), 64));
    float *Craw = static_cast<float *>(AlignedAllocate(MATRIX_SIZE * MATRIX_SIZE * sizeof(float), 64));

    using matrix_t = float(&)[MATRIX_SIZE][MATRIX_SIZE];

    matrix_t A = reinterpret_cast<matrix_t>(*Araw);
    matrix_t B = reinterpret_cast<matrix_t>(*Braw);
    matrix_t C = reinterpret_cast<matrix_t>(*Craw);

    InitializeMatrices(A, B);

    Timer timer;

    auto elapsed_time = 0.0;
    for (int test = 1; test <= 10; test++) {
        std::cout << "Running test iteration " << std::setw(2) << test << " ";
        timer.Start();
        MatMatMultiply(A, B, C);
        timer.Stop("Elapsed time : ");
        elapsed_time += timer.mElapsedTime.count();
        if (test == 10) {
            std::cout << "Average elapsed time : " << elapsed_time / 10.0 << "ms" << std::endl;
        }
    }

    return 0;
}
