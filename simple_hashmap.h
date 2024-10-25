#pragma once

#define SIMHASH_KEY_TYPE unsigned int
#define SIMHASH_VALUE_TYPE int

struct simple_hashmap_node {
  SIMHASH_KEY_TYPE key;
  SIMHASH_VALUE_TYPE value;
};

struct simple_hashmap {
  struct simple_hashmap_node *nodes;
  int size;
  int capacity;
};

struct simple_hashmap *simple_hashmap_create(int capacity);
void simple_hashmap_destroy(struct simple_hashmap *map);

struct simple_hashmap_node *simple_hashmap_get(struct simple_hashmap *map,
                                               SIMHASH_KEY_TYPE key);
void simple_hashmap_insert(struct simple_hashmap *map, SIMHASH_KEY_TYPE key,
                           SIMHASH_VALUE_TYPE value);
void simple_hashmap_remove(struct simple_hashmap *map, SIMHASH_KEY_TYPE key);

static inline int simple_hashmap_full(struct simple_hashmap *map) {
  return map->size == map->capacity;
}

static inline int simple_hashmap_empty(struct simple_hashmap *map) {
  return map->size == 0;
}

static inline int simple_hashmap_size(struct simple_hashmap *map) {
  return map->size;
}