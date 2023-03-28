//
// Created by Jacob on 3/24/2023.
//

#include <stdio.h>
#include <string.h>
#include "object.h"
#include "root_table.h"

// FNV-1a algorithm
unsigned int geece_hash(const char *key) {
    unsigned int hash = 2166136261;

    for (int i = 0; key[i] != '\0'; ++i) {
        hash ^= key[i];
        hash *= 16777619;
    }

    return hash;
}


RootTable *init_root_table(RootTable *table, size_t initial_capacity) {
    if (table == NULL) {
        fprintf(stderr, "Out of memory.");
        return NULL;
    }

    table->bucket_count = initial_capacity;

    // Allocate memory for bucket_heads array and initialize to NULL
    table->bucket_heads = calloc(initial_capacity, sizeof(Bucket*));
    if (table->bucket_heads == NULL) {
        fprintf(stderr, "Out of memory.");
        return NULL;
    }

    return table;
}


bool add_to_root_table(RootTable *table, char *key, Object *object){
    if (table == NULL){
        fprintf(stderr, "Root table not initialized.");
        return false;
    }
    if (key == NULL) {
        fprintf(stderr, "Key is NULL.");
        return false;
    }
    unsigned int index = geece_hash(key) % table->bucket_count;
    Bucket *currentBucketHead = table->bucket_heads[index];

    // Check if key already exists
    Bucket *currentBucket = currentBucketHead;
    while (currentBucket != NULL) {
        if (currentBucket->key != NULL && strcmp(currentBucket->key, key) == 0) {
            currentBucket->object = object;
            return true;
        }
        currentBucket = currentBucket->next;
    }

    // Key does not exist, find the next available bucket
    currentBucket = currentBucketHead;
    while (currentBucket != NULL) {
        if (currentBucket->key == NULL) {
            // Add the new bucket to the table
            currentBucket->key = key;
            currentBucket->object = object;
            return true;
        }
        currentBucket = currentBucket->next;
    }

    Bucket *newBucket = malloc(sizeof(Bucket));
    if (newBucket == NULL){
        fprintf(stderr, "Out of memory.");
        return false;
    }
    newBucket->key = key;
    newBucket->object = object;
    newBucket->next = currentBucket;
    table->bucket_heads[index] = newBucket;
    return true;
}

bool remove_from_root_table(RootTable *table, char *key){
    if (table == NULL){
        fprintf(stderr, "Root table not initialized.");
        return false;
    }
    for (size_t i = 0; i < table->bucket_count; ++i){
        Bucket *currentBucket = table->bucket_heads[i];
        Bucket *previousBucket = currentBucket;
        while (currentBucket != NULL){
            if (currentBucket->key != NULL && strcmp(currentBucket->key, key) == 0){
                if (previousBucket == currentBucket){
                    table->bucket_heads[i] = currentBucket->next;
                } else {
                    previousBucket->next = currentBucket->next;
                }
                free(currentBucket);
                table->bucket_count--;
                return true;
            }
            previousBucket = currentBucket;
            currentBucket = currentBucket->next;
        }
    }
    printf("Key '%s' not found in table.\n", key);
    return false;
}

Object *get_from_root_table(RootTable *table, char *key){
    if (table == NULL){
        fprintf(stderr, "Root table not initialized.");
        return NULL;
    }
    if (key == NULL){
        fprintf(stderr, "Key is NULL.");
        return NULL;
    }
    for (size_t i = 0; i < table->bucket_count; ++i){
        Bucket *currentBucketHead = table->bucket_heads[i];
        while (currentBucketHead != NULL){
            if (currentBucketHead->key != NULL && strcmp(currentBucketHead->key, key) == 0){
                return currentBucketHead->object;
            }
            currentBucketHead = currentBucketHead ->next;
        }
    }
    printf("Key '%s' not found in table.\n", key);
    return NULL;
}

bool clear_root_table(RootTable *table) {
    if (table == NULL) {
        fprintf(stderr, "Root table not initialized.");
        return false;
    }
    for (size_t i = 0; i < table->bucket_count; ++i) {
        Bucket *currentBucket = table->bucket_heads[i];
        while (currentBucket != NULL) {
            Bucket *tempBucket = currentBucket;
            currentBucket = currentBucket->next;
            free(tempBucket);
        }
        table->bucket_heads[i] = NULL;
    }
    table->bucket_count = 0;
    return true;
}

bool destroy_root_table(RootTable *table){
    if (table == NULL) {
        fprintf(stderr, "Root table not initialized.");
        return false;
    }
    clear_root_table(table);
    free(table->bucket_heads);
    free(table);
    return true;
}

bool rehash_root_table(RootTable *table) {
    if (table == NULL) {
        fprintf(stderr, "Root table not initialized.");
        return false;
    }

    size_t new_capacity = table->bucket_count * 2;

    RootTable new_table;
    if (init_root_table(&new_table, new_capacity) == NULL) {
        fprintf(stderr, "Out of memory.");
        return false;
    }

    // Copy over all of the key-value pairs from the old table to the new table
    for (size_t i = 0; i < table->bucket_count; ++i) {
        Bucket *currentBucketHead = table->bucket_heads[i];
        Bucket *currentBucket = currentBucketHead;

        while (currentBucket != NULL) {
            if (currentBucket->key != NULL) {
                add_to_root_table(&new_table, currentBucket->key, currentBucket->object);
            }
            currentBucket = currentBucket->next;
        }
    }

    // Free the memory used by the old table
    clear_root_table(table);

    // Allocate a new memory block for bucket_heads
    Bucket **new_bucket_heads = malloc(new_table.bucket_count * sizeof(Bucket*));
    if (new_bucket_heads == NULL) {
        fprintf(stderr, "Out of memory.");
        return false;
    }

// Copy the contents of new_table.bucket_heads to the new memory block
    memcpy(new_bucket_heads, new_table.bucket_heads, new_table.bucket_count * sizeof(Bucket*));

// Free the memory used by the new table
    free(new_table.bucket_heads);

// Update the table's bucket count and bucket_heads to those of the new table
    table->bucket_count = new_table.bucket_count;
    table->bucket_heads = new_bucket_heads;

    return true;

}







