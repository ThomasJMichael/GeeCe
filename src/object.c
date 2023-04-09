/**
 * @file object.c
 * @brief Implementation of the Object class.
 * 
 * The Object class provides a basic reference-counted object that can be used to store a block of data
 * of a specified size. It includes functionality for creating, destroying, and retaining objects,
 * as well as getting the size and data stored within an object.
 */
#include "object.h"

#include <stdio.h>
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
    object->marked = false;
    object->ref_count++;
    object->size = sizeof(Object) * size;
    object->destructor = destructor;
    object->referenced_ptrs = NULL;
    object->referenced_ptrs_count = 0;
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

size_t get_refcount(Object *object){
    return object->ref_count;
}

/**
 * @brief Gets the size of an Object's data field.
 * 
 * This function gets the size of an Object's data field.
 * 
 * @param object A pointer to the Object whose size is being requested.
 * @return The size of the Object's data field in bytes.
 */
size_t object_get_size(Object *object){
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
Object **object_get_data(Object *object){
    if (object == NULL){
        return NULL;
    }
    return object->referenced_ptrs;
}

void clear_reference_ptrs(Object *object){
    if (object == NULL){
        return;
    }
    for (size_t i = 0; i < object->referenced_ptrs_count; ++i){
        Object *currentReference = object->referenced_ptrs[i];
        free(currentReference);
    }
    free(object->referenced_ptrs);
    object->referenced_ptrs = NULL;
    object->referenced_ptrs_count = 0;
}

size_t object_get_references(const RootTable *table, const Object *object, Object ***out_references) {
    if (object == NULL) {
        return 0;
    }
    if (out_references == NULL) {
        return object->referenced_ptrs_count;
    }
    *out_references = object->referenced_ptrs;
    return (object->referenced_ptrs != NULL) ? object->referenced_ptrs_count : 0;
}

int object_get_reference_count_ptrs(RootTable *table, Object *object){
    return object->referenced_ptrs_count;
}

