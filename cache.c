#include "cache.h"

#include <stdio.h>
#include <stdlib.h>

static CacheEntry *cache = NULL;

static long cache_hits = 0;
static long cache_misses = 0;

static long age_counter = 0;
static long cache_capacity = 0;
static long cache_size = 0;

void cache_init(unsigned long long int size_of_cache) {
    cache_size = size_of_cache;
    cache = (CacheEntry *)malloc(cache_size * sizeof(CacheEntry));

    for (int ix = 0; ix < cache_size; ix++) {
        cache[ix].key = 0;
        cache[ix].value = 0;
        cache[ix].age = 0;
        cache[ix].frequency = 0;
    }
}
void cache_insert(unsigned long long key, long long int value,
                  int cache_policy) {
    int evict_index = find_cache_evict(cache_policy);
    cache[evict_index].key = key;
    cache[evict_index].value = value;

    if (cache_policy == LRU) {
        cache[evict_index].age = ++age_counter;
    } else if (cache_policy == LFU) {
        cache[evict_index].frequency = 1;
    }
}

long long int cache_lookup(unsigned long long int key) {
    for (int ix = 0; ix < cache_size; ix++) {
        if (cache[ix].key == key) {
            cache_hits++;
            cache[ix].frequency++;
            cache[ix].age = age_counter++;
            return cache[ix].value;
        }
    }
    cache_misses++;
    return 0;
}

int find_cache_evict(int cache_policy) {
    int evict_index = 0;

    if (cache_policy == LRU) {
        for (unsigned long i = 1; i < cache_size; i++) {
            if (cache[i].age < cache[evict_index].age) {
                evict_index = i;
            }
        }
    } else if (cache_policy == LFU) {
        for (unsigned long i = 1; i < cache_size; i++) {
            if (cache[i].frequency < cache[evict_index].frequency) {
                evict_index = i;
            }
        }
    }

    return evict_index;
}

unsigned long long int collatz_provider(unsigned long long int num) {
    unsigned long long int counter = 0;

    if (num == 1) return 0;

    while (num != 1) {
        if (num % 2 == 0) {
            num = num / 2;
        } else {
            num = 3 * num + 1;
        }
        counter++;
    }

    return counter;
}

unsigned long long int collatz(unsigned long long int num, int cache_policy,
                               unsigned long long int cache_size) {
    if (cache_policy == NONE) {
        return collatz_provider(num);
    }

    int value = cache_lookup(num);
    if (value == 0) {
        value = collatz_provider(num);
        cache_insert(num, value, cache_policy);
    }
    return value;
}

double cache_hit_rate() {
    return (double)cache_hits / (cache_hits + cache_misses) * 100;
}

void free_cache() { free(cache); }