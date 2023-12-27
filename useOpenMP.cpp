#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main(int argc, char* argv[])
{
    int** a, ** b, ** c;
    int i, j, k;

    // Cấp phát bộ nhớ cho ma trận a, b, c
    a = (int**)malloc(sizeof(int*) * N);
    b = (int**)malloc(sizeof(int*) * N);
    c = (int**)malloc(sizeof(int*) * N);

    for (i = 0; i < N; i++)
    {
        // Cấp phát bộ nhớ cho từng hàng của ma trận a, b, c
        a[i] = (int*)malloc(sizeof(int) * N);
        b[i] = (int*)malloc(sizeof(int) * N);
        c[i] = (int*)malloc(sizeof(int) * N);
    }

    printf("Bat dau | Su dung openMP...\n");
    double start = omp_get_wtime(); // Bắt đầu đo thời gian

    omp_set_num_threads(16); // Thiết lập số lượng luồng cần sử dụng

    // Bắt đầu phần song song với OpenMP
#pragma omp parallel shared(a, b, c) private(i, j, k)
    {
#pragma omp for schedule(static)
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                // Khởi tạo ma trận a và b
                a[i][j] = i + j;
                b[i][j] = i * j;
                c[i][j] = 0; // Khởi tạo ma trận c với giá trị 0
            }
        }

        printf("Thread %d dang chay...\n", omp_get_thread_num()); // Hiển thị thông tin về thread đang chạy

#pragma omp for schedule(static)
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                for (k = 0; k < N; k++)
                {
                    // Nhân ma trận a và b và tính toán ma trận c
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    double end = omp_get_wtime(); // Kết thúc đo thời gian
    double dif = end - start; // Tính thời gian thực hiện
    printf("Done. Total time: %f s.\n", dif); // Hiển thị tổng thời gian

    // Giải phóng bộ nhớ đã cấp phát
    for (i = 0; i < N; i++)
    {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}
