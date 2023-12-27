#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 1000 // Kích thước ma trận NxN

int main() {
    int **a, **b, **c;
    clock_t start, end;
    int i, j, k;
    double dif;

    // Cấp phát bộ nhớ cho ma trận A
    a = (int **)malloc(sizeof(int *) * N);
    for (i = 0; i < N; i++) {
        a[i] = (int *)malloc(sizeof(int) * N);
    }

    // Cấp phát bộ nhớ cho ma trận B
    b = (int **)malloc(sizeof(int *) * N);
    for (i = 0; i < N; i++) {
        b[i] = (int *)malloc(sizeof(int) * N);
    }

    // Cấp phát bộ nhớ cho ma trận tổng
    c = (int **)malloc(sizeof(int *) * N);
    for (i = 0; i < N; i++) {
        c[i] = (int *)malloc(sizeof(int) * N);
    }

    printf("Bat dau...\n");
    start = clock(); // Bắt đầu đo thời gian

    // Khởi tạo ma trận A
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = i + j;
        }
    }

    // Khởi tạo ma trận B
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            b[i][j] = i * j;
        }
    }

    // Khởi tạo ma trận tổng
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = 0;
        }
    }

    printf("Dang thuc hien khong dung openMP.....\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    end = clock(); // Kết thúc thời gian
    dif = ((double)(end - start)) / CLOCKS_PER_SEC; // Qui đổi thời gian ra giây
    printf("Complete. Total time: %f s.\n", dif);

    // Giải phóng bộ nhớ đã cấp phát
    for (i = 0; i < N; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}
