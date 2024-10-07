#include <stdio.h>
#include <stdlib.h>
#include "bag.h"

typedef struct node {
    void *item;
    struct node *next;
} node_t;

struct bag {
    node_t *head;
};

// create new bag
bag_t *bag_new(void) {
    bag_t *new_bag = malloc(sizeof(bag_t));
    if (new_bag == NULL) {
        perror("Error creating bag");
        exit(EXIT_FAILURE);
    }
    new_bag->head = NULL;
    return new_bag;
}

// insert an item into the bag
void bag_insert(bag_t *bag, void *item) {
    if (bag == NULL) {
        return;
    }

    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Error inserting into bag");
        exit(EXIT_FAILURE);
    }
    new_node->item = item;
    new_node->next = bag->head;
    bag->head = new_node;
}

// check if bag is empty
bool bag_is_empty(const bag_t *bag) {
    return (bag == NULL || bag->head == NULL);
}

// extract an item from the bag
void *bag_extract(bag_t *bag) {
    if (bag_is_empty(bag)) {
        return NULL;
    }

    // remove the first node from the bag
    node_t *current = bag->head;
    bag->head = current->next;
    void *item = current->item;
    free(current);

    return item;
}

// delete bag and its contents
void bag_delete(bag_t *bag, void (*itemdelete)(void *item)) {
    if (bag == NULL) {
        return;
    }

    // delete each node in the bag
    while (!bag_is_empty(bag)) {
        node_t *current = bag->head;
        bag->head = current->next;
        if (itemdelete != NULL) {
            itemdelete(current->item);
        }
        free(current);
    }

    free(bag);
}
