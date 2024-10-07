#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

// define node for the set
typedef struct Node {
    char *key;
    void *item;
    struct Node *next;
} Node;

// define set struct
struct set {
    Node *head;
};

// make new set
set_t *set_new(void) {
    set_t *new_set = malloc(sizeof(set_t));
    if (new_set == NULL) {
        perror("Error creating set");
        exit(EXIT_FAILURE);
    }
    new_set->head = NULL;
    return new_set;
}

// insert item into the set
bool set_insert(set_t *set, const char *key, void *item) {
    if (set == NULL || key == NULL || item == NULL) {
        return false;
    }

    // check if key already exists in the set
    Node *current = set->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return false; // Key already exists
        }
        current = current->next;
    }

    // make a new node
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Error inserting into set");
        exit(EXIT_FAILURE);
    }
    new_node->key = strdup(key);
    new_node->item = item;
    new_node->next = set->head;
    set->head = new_node;

    return true;
}

// find and return the item associated with the given key
void *set_find(set_t *set, const char *key) {
    if (set == NULL || key == NULL) {
        return NULL;
    }

    Node *current = set->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->item; // key found
        }
        current = current->next;
    }

    return NULL; // key not found
}

// print the set
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (set == NULL || fp == NULL || itemprint == NULL) {
        return;
    }

    Node *current = set->head;
    while (current != NULL) {
        itemprint(fp, current->key, current->item);
        current = current->next;
    }
}

// iterate over all items in the set
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (set == NULL || itemfunc == NULL) {
        return;
    }

    Node *current = set->head;
    while (current != NULL) {
        itemfunc(arg, current->key, current->item);
        current = current->next;
    }
}

// delete the set
void set_delete(set_t *set, void (*itemdelete)(void *item)) {
    if (set == NULL) {
        return;
    }

    Node *current = set->head;
    while (current != NULL) {
        Node *next = current->next;
        if (itemdelete != NULL) {
            itemdelete(current->item);
        }
        free(current->key);
        free(current);
        current = next;
    }

    free(set);
}
