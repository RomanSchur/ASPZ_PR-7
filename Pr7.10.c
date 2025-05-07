#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double function_1() {
    double res = (double)rand() / RAND_MAX; 
    return res;
}

double function_2(double n) {
    double res = n * function_1(); 
    return res;
}

int main() {
    int num_numbers = 4;
    double upper_limit = 5.0; 

    srand(time(NULL));

    printf("Випадкові числа в діапазоні [0.0, 1.0]:\n");
    for (int i = 0; i < num_numbers; i++) {
        printf("%.4f\n", function_1());
    }

    printf("\nВипадкові числа в діапазоні [0.0, %.1f]:\n", upper_limit);
    for (int i = 0; i < num_numbers; i++) {
        printf("%.4f\n", function_2(upper_limit));
    }
    return 0;
}