#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double calculate_time(void (*func)()) {
    clock_t start, end;
    double elapsed_time;

    start = clock();
    func();
    end = clock();

    elapsed_time = ((double) (end - start)) * 1000.0 / CLOCKS_PER_SEC; 
    return elapsed_time;
}

void func() {
    long long sum = 0;
    for (long long i = 0; i < 10000000; i++) {
        sum += i;
    }    
}

int main() {
    double time = calculate_time(func);
    printf("Час виконання: %.2f мс\n", time);
    return 0;
}