/*
 * Copyright (C) 2025 spekie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define ARRAY_SIZE 100000000
#define NUM_THREADS 4

void benchmark_integer_operations() {
    volatile int sum = 0;
    clock_t start = clock();
    
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += i;
    }
    
    clock_t end = clock();
    printf("Integer operations: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_floating_point_operations() {
    volatile double sum = 0.0;
    clock_t start = clock();
    
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += (double)i * 0.5;
    }
    
    clock_t end = clock();
    printf("Floating-point operations: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_memory_access() {
    volatile int *array = malloc(ARRAY_SIZE * sizeof(int));
    clock_t start = clock();
    
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i;
    }
    
    clock_t end = clock();
    printf("Memory access: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    free((void *)array);
}

void benchmark_cache_performance() {
    volatile int *array = malloc(ARRAY_SIZE * sizeof(int));
    clock_t start = clock();
    
    for (int i = 0; i < ARRAY_SIZE; i += 64) {
        array[i] = i;
    }
    
    clock_t end = clock();
    printf("Cache performance: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    free((void *)array);
}

void *thread_function(void *arg) {
    volatile int sum = 0;
    for (int i = 0; i < ARRAY_SIZE / NUM_THREADS; ++i) {
        sum += i;
    }
    return NULL;
}

void benchmark_multithreading() {
    pthread_t threads[NUM_THREADS];
    clock_t start = clock();
    
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }
    
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    clock_t end = clock();
    printf("Multithreading: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    printf("Benchmarking...\n");

    benchmark_integer_operations();
    benchmark_floating_point_operations();
    benchmark_memory_access();
    benchmark_cache_performance();
    benchmark_multithreading();

    printf("Complete.\n");

    return 0;
}

