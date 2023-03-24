/**
 * @file object.c
 * @brief Implementation of the Object class.
 * 
 * The Object class provides a basic reference-counted object that can be used to store a block of data
 * of a specified size. It includes functionality for creating, destroying, and retaining objects,
 * as well as getting the size and data stored within an object.
 */

#include <stdio.h>
#include "object.h"
#include <stdlib.h>

/**
 * @brief Creates a new Object with the specified size and destructor.
 * 
 * This function creates a new Object with the specified size and destructor. The Object's data field
 * is initialized to 0 using calloc.
 * 
 * @param size The size of the Object's data field in bytes.
 * @param destructor A pointer to the destructor function for the Object.
 * @return A pointer to the newly created Object.
 */
Object *new_object(size_t size, Destructor destructor){
    Object *object = calloc(1, sizeof(Object) + size);
    if (object == NULL){
        fprintf(stderr, "Error: Failed to allocate memory for object.\n");
        exit(EXIT_FAILURE);
    }
    object->ref_count++;
    object->size = sizeof(Object) * size;
    object->destructor = destructor;
    return object;
}

/**
 * @brief Destroys an Object and frees the memory allocated for it.
 * 
 * This function destroys an Object and frees the memory allocated for it. It calls the destructor
 * function for the Object if it exists.
 * 
 * @param object A pointer to the Object to be destroyed.
 */
void destroy_object(Object *object){
    object->destructor(object);
}

/**
 * @brief Increases the reference count of an Object.
 * 
 * This function increases the reference count of an Object by 1.
 * 
 * @param object A pointer to the Object to be retained.
 */
void retain_object(Object *object){
    object->ref_count++;
}

/**
 * @brief Gets the size of an Object's data field.
 * 
 * This function gets the size of an Object's data field.
 * 
 * @param object A pointer to the Object whose size is being requested.
 * @return The size of the Object's data field in bytes.
 */
size_t get_size(Object *object){
    return object->size;
}

/**
 * @brief Gets a pointer to an Object's data field.
 * 
 * This function gets a pointer to an Object's data field.
 * 
 * @param object A pointer to the Object whose data field is being requested.
 * @return A pointer to the Object's data field.
 */
char *get_data(Object *object){
    return object->data;
}
