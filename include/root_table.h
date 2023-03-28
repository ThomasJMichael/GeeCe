//
// Created by Jacob on 3/24/2023.
//

/**
 * @file root_table.h
 * @brief Defines a hash table data structure for holding the root set of objects in GeeCe's mark-and-sweep garbage collector.
 */

#ifndef GEECE_ROOT_TABLE_H
#define GEECE_ROOT_TABLE_H

#include <stdbool.h>
#include "object.h"

/**
 * @brief A structure representing a bucket in a hash table.
 */
typedef struct Bucket Bucket;

/**
 * @brief A structure representing a hash table for holding the root set of objects in GeeCe's mark-and-sweep garbage collector.
 */
typedef struct RootTable {
    Bucket **bucket_heads;
    size_t bucket_count; /**< The number of buckets in the hash table. */
} RootTable;

/**
 * @brief A structure representing a bucket in a hash table.
 */
struct Bucket {
    char *key; /**< A string key that identifies the object stored in the bucket. */
    Object *object; /**< A pointer to the object stored in the bucket. */
    Bucket *next; /**< A pointer to the next bucket in the hash table's linked list. */
};

/**
 * @brief Computes a hash value for an object.
 *
 * @param object The object to compute the hash value for.
 *
 * @return The computed hash value.
 */
unsigned int geece_hash(const char *key);

/**
 * @brief Initializes a RootTable structure with the given initial capacity.
 *
 * @param table The RootTable structure to initialize.
 * @param initial_capacity The initial capacity of the hash table.
 *
 * @return True if table was initialized successfully.
 */
RootTable *init_root_table(RootTable *table, size_t initial_capacity);

/**
 * @brief Adds an object to a RootTable.
 *
 * @param table The RootTable to add the object to.
 * @param key The key to associate with the object.
 * @param object The object to add to the RootTable.
 *
 * @return True if the object was successfully added, false otherwise.
 */
bool add_to_root_table(RootTable *table, char *key, Object *object);

/**
 * @brief Removes an object from a RootTable.
 *
 * @param table The RootTable to remove the object from.
 * @param key The key associated with the object.
 *
 * @return True if the object was successfully removed, false otherwise.
 */
bool remove_from_root_table(RootTable *table, char *key);

/**
 * @brief Gets an object from a RootTable by its key.
 *
 * @param table The RootTable to get the object from.
 * @param key The key associated with the object.
 *
 * @return A pointer to the object associated with the key, or NULL if the key is not found in the RootTable.
 */
Object *get_from_root_table(RootTable *table, char *key);

/**
 * @brief Removes all objects from a RootTable.
 *
 * @param table The RootTable to clear.
 *
 * @return True if the RootTable was successfully cleared, false otherwise.
 */
bool clear_root_table(RootTable *table);

/**
 * @brief Destroys a RootTable and frees all memory associated with it.
 *
 * @param table The RootTable to destroy.
 *
 * @return True if the RootTable was successfully destroyed, false otherwise.
 */
bool destroy_root_table(RootTable *table);

/**
 * @brief Rehashes a RootTable, increasing the number of buckets by a factor of 2.
 *
 * @param table The RootTable to rehash.
 */
bool rehash_root_table(RootTable *table);

#endif // GEECE_ROOT_TABLE_H

