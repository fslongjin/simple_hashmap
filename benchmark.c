#include "simple_hashmap.h"
#include <stdio.h>
#include <time.h>

#define NUM_OPERATIONS 10000000
#define HASHMAP_CAPACITY NUM_OPERATIONS
#define NUM_ROUND 10

double benchmark_insert(struct simple_hashmap *map) {
  clock_t start, end;
  double cpu_time_used;

  start = clock();
  for (int i = 0; i < NUM_OPERATIONS; i++) {
    simple_hashmap_insert(map, i, i);
  }
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  return NUM_OPERATIONS / cpu_time_used;
}

double benchmark_get(struct simple_hashmap *map) {
  clock_t start, end;
  double cpu_time_used;

  start = clock();
  for (int i = 0; i < NUM_OPERATIONS; i++) {
    simple_hashmap_get(map, i);
  }
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  return NUM_OPERATIONS / cpu_time_used;
}

double benchmark_remove(struct simple_hashmap *map) {
  clock_t start, end;
  double cpu_time_used;

  start = clock();
  for (int i = 0; i < NUM_OPERATIONS; i++) {
    simple_hashmap_remove(map, i);
  }
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  return NUM_OPERATIONS / cpu_time_used;
}

int main() {
  struct simple_hashmap *map = simple_hashmap_create(HASHMAP_CAPACITY);

  double insert_throughput = 0;
  double get_throughput = 0;
  double remove_throughput = 0;
  for (int i = 0; i < NUM_ROUND; i++) {
    insert_throughput += benchmark_insert(map);
    get_throughput += benchmark_get(map);
    remove_throughput += benchmark_remove(map);
  }

  printf("Insert throughput: %.2f ops/sec\n", insert_throughput / NUM_ROUND);
  printf("Get throughput: %.2f ops/sec\n", get_throughput / NUM_ROUND);
  printf("Remove throughput: %.2f ops/sec\n", remove_throughput / NUM_ROUND);

  simple_hashmap_destroy(map);

  return 0;
}
