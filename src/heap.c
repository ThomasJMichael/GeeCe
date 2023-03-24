#include <stdio.h>
#include "heap.h"

Object *geece_malloc(size_t size, Destructor destructor){
    Object *obj = new_object(size, destructor);
    if (obj == NULL){
        fprintf(stderr, "Error: Failed to allocate memory for object.\n");
        exit(EXIT_FAILURE);
    }
    if (heap == NULL){
        heap = malloc(sizeof(Heap));
        heap->size = size;
        heap->objects[0] = *obj;
        heap->top = &heap->objects[0] + sizeof(Object);
        return obj;
    } else {
        heap->size = heap->size + size;
        heap->top = heap->top + sizeof(Object);
        return obj;
    }
}

void geece_release(Object *object){
    object->ref_count = object->ref_count - 1;
    if (get_refcount(object) == 0){
        destroy_object(object);
    }
}

size_t geece_size(Object *object){
    return object->size;
}

char *geece_data(Object *object){
    return object->data;
}

size_t geece_total_memory(){
    return heap->size;
}

size_t geece_available_memory(){
    if (heap == NULL){
        return 0;
    }
    size_t used_memory = heap->top - heap->objects;
    size_t available_memory = heap->size - used_memory;
    return available_memory;
}