/*
 * object.h
 *
 */
#ifndef GEECE_OBJECT_H
#define GEECE_OBJECT_H

#include "stdlib.h"
#include "root_table.h"
/*
 * Object struct
 *
 * This struct represents an object in memory that will be managed by the garbage collector.
 * It contains a reference count to keep track of the number of references to the object,
 * a size to store the size of the object, a destructor function pointer to handle object cleanup,
 * and a flexible array member to store the object data.
 */
typedef struct Object{
    bool marked;
    size_t ref_count;                   // Number of references to the object
    size_t size;                        // Size of the object
    void (*destructor)(void *);         // Destructor function pointer to handle object cleanup
    ObjectNode *references;             // A linked list of objects this object points to
    Object **referenced_ptrs;           //Array of pointers to the objects that are point to this object
    int referenced_ptrs_count;          //Count of objects point to this object.
} Object;

typedef void (*Destructor)(void *);

/*
 * new_object - Creates a new Object
 *
 * This function creates a new Object of the specified size with a destructor function.
 *
 * size: The size of the object to create
 * destructor: The destructor function pointer to handle object cleanup
 *
 * Returns: A pointer to the new Object
 */
Object *new_object(size_t size, Destructor destructor);

/*
 * destroy_object - Destroys an Object
 *
 * This function destroys an Object and frees its memory.
 *
 * object: The Object to destroy
 */
void destroy_object(Object *object);

/*
 * retain_object - Retains an Object
 *
 * This function increments the reference count of an Object.
 *
 * object: The Object to retain
 */
void retain_object(Object *object);

/*
 * get_refcount - Returns the reference count of an Object
 *
 * This function returns the reference count of an Object.
 *
 * object: The Object to get the reference count of
 *
 * Returns: The reference count of the Object
 */
size_t get_refcount(Object *object);

/*
 * object_get_size - Returns the size of an Object
 *
 * This function returns the size of an Object.
 *
 * object: The Object to get the size of
 *
 * Returns: The size of the Object
 */
size_t object_get_size(Object *object);

/*
 * object_get_data - Returns the data of an Object
 *
 * This function returns a pointer to the data of an Object.
 *
 * object: The Object to get the data of
 *
 * Returns: A pointer to the data of the Object
 */
Object **object_get_data(Object *object);

void clear_reference_ptrs(Object *object);

size_t object_get_references(const RootTable *table,const Object *object, Object ***out_references);

int object_get_reference_count_ptrs(RootTable *table, Object *object);

#endif /* GEECE_OBJECT_H */



