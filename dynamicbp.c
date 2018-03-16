#include "stdio.h"
#include "time.h"

double getTime() {
    double result = 0;
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    result += (double) time.tv_sec;
    result += (double) time.tv_nsec / 1000000000;
    return result;
}

double testPadrao(int padrao, int max) {
    int sum;
    double timbef, timaft;
    timbef = getTime();
    for (int i = 0; i < max; i++)
        if ((i & padrao) == 0)
            sum++;
    timaft = getTime();
    return timaft - timbef;
}



int main() {
    double timbef, timaft;
    int max = 1000000000;
    int sum = 0;

    printf("Experimento em Dynamic Branch Prediction\n");
    printf("Diferentes padrões de if repetidos\n");
   
    printf("Padrão all True - ");
    printf("%lfs \n", testPadrao(0x80000000, max));

    printf("Padrão all False - ");
    printf("%lfs \n", testPadrao(0xffffffff, max));

    printf("Padrão TF - ");
    printf("%lfs \n", testPadrao(1, max));

    printf("Padrão TFFF - ");
    printf("%lfs \n", testPadrao(3, max));

    printf("Padrão TTFF - ");
    printf("%lfs \n", testPadrao(2, max));
   
    return 0;
}
