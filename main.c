#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cache.h"

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("File: %s <int> <int> <int>\n", argv[0]);
    }

    unsigned long long int MIN = atoi(argv[2]);
    unsigned long long int MAX = atoi(argv[3]);
    unsigned int num_to_test = atoi(argv[1]);
    int cache_policy = atoi(argv[4]);
    unsigned long long int cache_size = atoi(argv[5]);
    cache_init(cache_size);

    srand(time(NULL));

    FILE *fp;
    fp = fopen("output.csv", "w");

    fprintf(fp, "Random Number\tTotal Steps\n");
    for (int ix = 0; ix < num_to_test; ix++) {
        unsigned long long int random_num = rand() % (MAX - MIN + 1) + MIN;
        unsigned long long int a =
            collatz(random_num, cache_policy, cache_size);
        fprintf(fp, " %lld\t\t\t\t%lld\n ", random_num, a);
    }

    fclose(fp);
    printf("Cache Hit Percentage: %.2f%%\n", cache_hit_rate());
    free_cache();

    return 0;
}