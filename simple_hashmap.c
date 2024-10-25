#include "simple_hashmap.h"
#include <stdio.h>
#include <stdlib.h>

#define KEY_DELETED (SIMHASH_KEY_TYPE)(-1)

// Hash function
static unsigned int hash(SIMHASH_KEY_TYPE key, int capacity) {
  return key % capacity;
}

static unsigned int next_index(unsigned int index, int capacity) {
  // Linear probing
  return (index + 1) % capacity;
}

// Create a new hashmap
struct simple_hashmap *simple_hashmap_create(int capacity) {
  struct simple_hashmap *map =
      (struct simple_hashmap *)malloc(sizeof(struct simple_hashmap));
  if (map == NULL) {
    return NULL; // Allocation failed
  }
  map->nodes = (struct simple_hashmap_node *)calloc(
      capacity, sizeof(struct simple_hashmap_node));
  if (map->nodes == NULL) {
    free(map);
    return NULL; // Allocation failed
  }

  // Initialize all nodes to be "empty"
  for (int i = 0; i < capacity; i++) {
    map->nodes[i].key = KEY_DELETED;
  }
  map->size = 0;
  map->capacity = capacity;
  return map;
}

void simple_hashmap_destroy(struct simple_hashmap *map) {
  if (!map)
    return;
  if (map->nodes)
    free(map->nodes);
  free(map);
}

// Get a node from the hashmap
struct simple_hashmap_node *simple_hashmap_get(struct simple_hashmap *map,
                                               SIMHASH_KEY_TYPE key) {
  if (map == NULL || map->nodes == NULL) {
    return NULL;
  }

  unsigned int index = hash(key, map->capacity);
  for (int i = 0; i < map->capacity; i++) {
    if (map->nodes[index].key == key) {
      return &map->nodes[index];
    }

    index = next_index(index, map->capacity);
  }
  return NULL; // Key not found
}

// Insert a key-value pair into the hashmap
void simple_hashmap_insert(struct simple_hashmap *map, SIMHASH_KEY_TYPE key,
                           SIMHASH_VALUE_TYPE value) {
  if (map == NULL || map->nodes == NULL || map->size >= map->capacity) {
    return; // Map is full or invalid
  }

  unsigned int index = hash(key, map->capacity);
  while (map->nodes[index].key != KEY_DELETED && map->nodes[index].key != key) {
    index = next_index(index, map->capacity);
  }

  if (map->nodes[index].key == KEY_DELETED) {
    map->size++;
  }
  map->nodes[index].key = key;
  map->nodes[index].value = value;
}

// Remove a key-value pair from the hashmap
void simple_hashmap_remove(struct simple_hashmap *map, SIMHASH_KEY_TYPE key) {
  if (map == NULL || map->nodes == NULL) {
    return;
  }

  unsigned int index = hash(key, map->capacity);
  for (int i = 0; i < map->capacity; i++) {
    if (map->nodes[index].key == key) {
      map->nodes[index].key = KEY_DELETED;
      map->size--;
      return;
    }
    index = next_index(index, map->capacity);
  }
}
