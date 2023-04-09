#include "object.h"
#include "mark_and_sweep.h"

void geece_mark(Object *object){
}

void geece_ptr_scanner(Object *object, void (*mark_function)(Object *obj)){
    if (object == NULL){
        return;
    }
    if (object->marked == true){
        return;
    }
    object->marked = true;

}