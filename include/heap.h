#ifndef GEECE_HEAP_H
#define GEECE_HEAP_H

#include "object.h"

typedef struct{
    size_t size;
    Object *top; //Points to the next free spot in objects
    Object *objects;
} Heap;

/**
 * Pointer to the global heap instance. Initialized to NULL on program start and
 * allocated when `geece_malloc()` is called for the first time.
 */
Heap *heap = NULL;

/**
 * Allocates memory on the Geece heap.
 *
 * @param size The size of the object to be allocated.
 * @param destructor The destructor function for the object.
 * @return A pointer to the allocated object.
 * @throws An error message if memory allocation fails.
 */
Object *geece_malloc(size_t size, Destructor destructor);

/**
 * Decrements the reference count of an object and destroys it if the reference count reaches 0.
 *
 * @param object A pointer to the object to be released.
 */
void geece_release(Object *object);

/**
 * Returns the size of an object.
 *
 * @param object A pointer to the object to get the size of.
 * @return The size of the object.
 */
size_t geece_size(Object *object);

/**
 * Returns the data stored in an object.
 *
 * @param object A pointer to the object to get the data of.
 * @return The data stored in the object.
 */
Object **geece_data(Object *object);

/**
 * Returns the total amount of memory allocated on the Geece heap.
 *
 * @return The total amount of memory allocated on the Geece heap.
 */
size_t geece_total_memory();

/**
 * Returns the amount of available memory on the Geece heap.
 *
 * @return The amount of available memory on the Geece heap.
 */
size_t geece_available_memory();


#endif /* GEECE_HEAP_H */
