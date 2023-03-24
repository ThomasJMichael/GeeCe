/*
 * object.h
 *
#ifndef GEECE_OBJECT_H
#define GEECE_OBJECT_H

/*
 * Object struct
 *
 * This struct represents an object in memory that will be managed by the garbage collector.
 * It contains a reference count to keep track of the number of references to the object,
 * a size to store the size of the object, a destructor function pointer to handle object cleanup,
 * and a flexible array member to store the object data.
 */
typedef struct Object {
    size_t ref_count;                   // Number of references to the object
    size_t size;                        // Size of the object
    void (*destructor)(void *);         // Destructor function pointer to handle object cleanup
    char data[];                        // Flexible array member to store the object data
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
 * get_size - Returns the size of an Object
 *
 * This function returns the size of an Object.
 *
 * object: The Object to get the size of
 *
 * Returns: The size of the Object
 */
size_t get_size(Object *object);

/*
 * get_data - Returns the data of an Object
 *
 * This function returns a pointer to the data of an Object.
 *
 * object: The Object to get the data of
 *
 * Returns: A pointer to the data of the Object
 */
char *get_data(Object *object);

#endif /* GEECE_OBJECT_H */



