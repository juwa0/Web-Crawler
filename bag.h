#ifndef BAG_H
#define BAG_H

#include <stdbool.h>

typedef struct bag bag_t;

bag_t *bag_new(void);

void bag_insert(bag_t *bag, void *item);

bool bag_is_empty(const bag_t *bag);

void *bag_extract(bag_t *bag);

void bag_delete(bag_t *bag, void (*itemdelete)(void *item));

#endif // BAG_H
