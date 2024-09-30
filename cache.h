#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef CACHE_H
#define CACHE_H

#define NONE 0
#define LRU 1
#define LFU 2

typedef struct {
    unsigned long long int key;
    unsigned long long int value;
    int age;
    int frequency;
} CacheEntry;

unsigned long long int collatz_provider(unsigned long long int num);
unsigned long long int collatz(unsigned long long int num, int cache_policy,
                               unsigned long long int cache_size);

void cache_init(unsigned long long int size_of_cache);
void cache_insert(unsigned long long int key, long long int value,
                  int cache_policy);
void cache_free(void);
int find_cache_evict(int cache_policy);
long long int cache_lookup(unsigned long long int key);

double cache_hit_rate(void);

void free_cache(void);
#endif