#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "set.h"

// define the hashtable struct
struct hashtable {
    int num_slots;
    set_t **sets;
};

// make new hashtable
hashtable_t *hashtable_new(const int num_slots) {
    hashtable_t *new_hashtable = malloc(sizeof(hashtable_t));
    if (new_hashtable == NULL) {
        perror("Error creating hashtable");
        exit(EXIT_FAILURE);
    }

    new_hashtable->num_slots = num_slots;
    new_hashtable->sets = malloc(num_slots * sizeof(set_t *));
    if (new_hashtable->sets == NULL) {
        perror("Error creating sets in hashtable");
        exit(EXIT_FAILURE);
    }

    // initialize each set
    for (int i = 0; i < num_slots; i++) {
        new_hashtable->sets[i] = set_new();
    }

    return new_hashtable;
}

// insert item into the hashtable
bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht == NULL || key == NULL || item == NULL) {
        return false;
    }

    // hash the key to determine the set
    int hash_value = hash_string(key) % ht->num_slots;

    // Insert into the corresponding set
    return set_insert(ht->sets[hash_value], key, item);
}

// find and return the item associated with the given key
void *hashtable_find(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    // hash the key to determine the set
    int hash_value = hash_string(key) % ht->num_slots;

    // find in the corresponding set
    return set_find(ht->sets[hash_value], key);
}

// print hashtable
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (ht == NULL || fp == NULL || itemprint == NULL) {
        return;
    }

    // print each set in hashtable
    for (int i = 0; i < ht->num_slots; i++) {
        set_print(ht->sets[i], fp, itemprint);
    }
}

// iterate over all items in the hashtable
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht == NULL || itemfunc == NULL) {
        return;
    }

    // iterate over each set in the hashtable
    for (int i = 0; i < ht->num_slots; i++) {
        set_iterate(ht->sets[i], arg, itemfunc);
    }
}

// delete the hashtable
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
    if (ht == NULL) {
        return;
    }

    // delete each set in the hashtable
    for (int i = 0; i < ht->num_slots; i++) {
        set_delete(ht->sets[i], itemdelete);
    }

    free(ht->sets);
    free(ht);
}

// hash function for strings
unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != 0) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}