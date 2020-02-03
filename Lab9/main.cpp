#include <stdio.h>
#include <iostream>
#include <time.h>
using namespace std;
int main()
{
    int SIZE = 3 * 1024 * 1024 / sizeof(int); //размер кеша
    int C = 30;
    union ticks {
        unsigned long long t64;
        struct s32 { int th, tl; } t32;
    } start, end;
    for (int Frag = 1; Frag <= 32; ++Frag) { //количество фрагментов
        cout << Frag << " ";
        int N = Frag * SIZE; //размер массива
        int* ptrarray = new int[N];
        int bankCapacity = SIZE / Frag; //размер одного фрагмента
        for (int i = 0; i < bankCapacity; ++i) {
            for (int j = 0; j < Frag - 1; ++j) {
                ptrarray[j * SIZE + i] = (j + 1) * SIZE + i;
            }
            if (i == bankCapacity - 1) {
                ptrarray[(Frag - 1) * SIZE + i] = 0;
            }
            else {
                ptrarray[(Frag - 1) * SIZE + i] = i + 1;
            }
    }
        unsigned long long tic = 0;
        for (int j = 0; j < C; j++) {
            asm("rdtsc\n":"=a"(start.t32.th), "=d"(start.t32.tl));
            for (int k = 0, i = 0; i < N; i++) k = ptrarray[k];
            asm("rdtsc\n":"=a"(end.t32.th), "=d"(end.t32.tl));
            tic += (end.t64 - start.t64);
        }
        cout << tic / (N * C) <<endl;
        delete[] ptrarray;
    }
}