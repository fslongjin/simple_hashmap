#include "simple_hashmap.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_simple_hashmap_create() {
  struct simple_hashmap *map = simple_hashmap_create(10);
  assert(map != NULL);
  assert(map->capacity == 10);
  assert(map->size == 0);
  simple_hashmap_destroy(map);
  printf("test_simple_hashmap_create passed\n");
}

static void test_simple_hashmap_insert_and_get() {
  struct simple_hashmap *map = simple_hashmap_create(10);
  simple_hashmap_insert(map, 1, 42);
  struct simple_hashmap_node *node = simple_hashmap_get(map, 1);
  assert(node != NULL);
  assert(node->key == 1);
  assert(node->value == 42);
  simple_hashmap_destroy(map);
  printf("test_simple_hashmap_insert_and_get passed\n");
}

static void test_simple_hashmap_remove() {
  struct simple_hashmap *map = simple_hashmap_create(10);
  simple_hashmap_insert(map, 1, 42);
  simple_hashmap_remove(map, 1);
  struct simple_hashmap_node *node = simple_hashmap_get(map, 1);
  assert(node == NULL);
  simple_hashmap_destroy(map);
  printf("test_simple_hashmap_remove passed\n");
}

static void test_simple_hashmap_collision() {
  struct simple_hashmap *map = simple_hashmap_create(10);
  simple_hashmap_insert(map, 1, 42);
  simple_hashmap_insert(map, 11, 43); // 11 should collide with 1
  struct simple_hashmap_node *node1 = simple_hashmap_get(map, 1);
  struct simple_hashmap_node *node11 = simple_hashmap_get(map, 11);
  assert(node1 != NULL);
  assert(node11 != NULL);
  assert(node1->key == 1);
  assert(node1->value == 42);
  assert(node11->key == 11);
  assert(node11->value == 43);
  simple_hashmap_destroy(map);
  printf("test_simple_hashmap_collision passed\n");
}

static void test_simple_hashmap_full() {
  struct simple_hashmap *map = simple_hashmap_create(2);
  simple_hashmap_insert(map, 1, 42);
  simple_hashmap_insert(map, 2, 43);
  simple_hashmap_insert(map, 3, 44); // Should not be inserted
  struct simple_hashmap_node *node = simple_hashmap_get(map, 3);
  assert(node == NULL);
  simple_hashmap_destroy(map);
  printf("test_simple_hashmap_full passed\n");
}

static void test_simple_hashmap_insert_and_remove_multiple() {
  struct simple_hashmap *map = simple_hashmap_create(10);
  simple_hashmap_insert(map, 1, 42);
  simple_hashmap_insert(map, 2, 43);
  simple_hashmap_insert(map, 3, 44);

  struct simple_hashmap_node *node1 = simple_hashmap_get(map, 1);
  assert(node1 != NULL);
  assert(node1->key == 1);

  simple_hashmap_remove(map, 1);
  node1 = simple_hashmap_get(map, 1);
  assert(node1 == NULL);

  simple_hashmap_insert(map, 13, 53);
  struct simple_hashmap_node *node3 = simple_hashmap_get(map, 3);
  assert(node3 != NULL);
  assert(node3->key == 3);
  assert(node3->value == 44);
  simple_hashmap_remove(map, 3);
  node3 = simple_hashmap_get(map, 3);
  assert(node3 == NULL);
  struct simple_hashmap_node *node13 = simple_hashmap_get(map, 13);
  assert(node13 != NULL);
  assert(node13->key == 13);
  assert(node13->value == 53);
  simple_hashmap_destroy(map);
}

int main() {
  test_simple_hashmap_create();
  test_simple_hashmap_insert_and_get();
  test_simple_hashmap_remove();
  test_simple_hashmap_collision();
  test_simple_hashmap_full();
  test_simple_hashmap_insert_and_remove_multiple();
  printf("All tests passed!\n");
  return 0;
}
