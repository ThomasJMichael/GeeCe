#ifndef GEECE_HEAP_H
#define GEECE_HEAP_H

#include "object.h"

typedef struct Heap{
    //Object **objects;
    int capacity;
    int size;
} Heap;

Heap *heap_create(int capacity);
void heap_destroy(Heap *heap);

//Object *heap_add_object(Heap *heap, size_t size, Destructor destructor);
void heap_remove_object(Heap *heap, Object *object);

#endif /* GEECE_HEAP_H */
