#include "include/object.h"

#include "stdlib.h"

Object *new_object(size_t size, Destuctor destructor){
    Object *object = malloc(sizeof(object) * size);
    if (object == NULL){
        return NULL;
    }
    object->

}