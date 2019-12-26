#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void Randomize (int* Array, int N)
{
    int j;
    for (int i = N-1; i > 0; i--)
    {
        j = rand() % i;
        swap (Array[i], Array[j]);
    }
}


int main() {
    srand(time(0));
    int K = 10;
    int index = 0;
    union ticks
    {
        unsigned long long t64;
        struct s32 {int th, tl;} t32;
    } start, end;

    for (int i = 1; i <=10; i++)
    {
        int N = 50*256;
        int* ArrayF = (int*)malloc(N * sizeof(int));
        int* ArrayB = (int*)malloc(N * sizeof(int));
        int* ArrayR = (int*)malloc(N * sizeof(int));

        for (int k = 0; k < N; k++)
        {
            ArrayF[k] = (k + 1) % N;
            ArrayB[k] = k-1;
            ArrayR[k] = k;
        }

        ArrayB[0] = N - 1;
        Randomize(ArrayR, N);

        for (int j = 0; j < N*K; j++) index = ArrayF[index];
        for (int j = 0; j < N*K; j++) index = ArrayB[index];
        for (int j = 0; j < N*K; j++) index = ArrayR[index];

        delete[] ArrayF;
        delete[] ArrayB;
        delete[] ArrayR;
    }

    for (double S = 1; S <= 32 * 1024; S *= 1.5)
    {
        int N = S * 256;
        cout << S << "KB" << endl;
        int* ArrayF = (int*)malloc(N * sizeof(int));
        int* ArrayB = (int*)malloc(N * sizeof(int));
        int* ArrayR = (int*)malloc(N * sizeof(int));

        for (int k = 0; k < N; k++)
        {
            ArrayF[k] = (k + 1) % N;
            ArrayB[k] = k-1;
            ArrayR[k] = k;
        }

        ArrayB[0] = N - 1;
        Randomize(ArrayR, N);


        for (int j = 0; j < N*K; j++) index = ArrayF[index]; // Разовый прогон
        index = 0;

        asm("rdtsc\n":"=a"(start.t32.th), "=d"(start.t32.tl));
        for (int j = 0; j < N*K; j++) index = ArrayF[index];
        asm("rdtsc\n":"=a"(end.t32.th), "=d"(end.t32.tl));

        cout << (end.t64 - start.t64) / (N * K) << "         ";


        for (int j = 0; j < N*K; j++) index = ArrayB[index]; // Разовый прогон
        index = 0;

        asm("rdtsc\n":"=a"(start.t32.th), "=d"(start.t32.tl));
        for (int j = 0; j < N*K; j++) index = ArrayB[index];
        asm("rdtsc\n":"=a"(end.t32.th), "=d"(end.t32.tl));

        cout << (end.t64 - start.t64) / (N * K) << "         ";


        for (int j = 0; j < N*K; j++) index = ArrayR[index]; // Разовый прогон
        index = 0;

        asm("rdtsc\n":"=a"(start.t32.th), "=d"(start.t32.tl));
        for (int j = 0; j < N*K; j++) index = ArrayR[index];
        asm("rdtsc\n":"=a"(end.t32.th), "=d"(end.t32.tl));

        cout << (end.t64 - start.t64) / (N * K) << endl << endl;

        delete[] ArrayF;
        delete[] ArrayB;
        delete[] ArrayR;

    }

    return 0;
}