#include "object.h"
#include "root_table.h"

void geece_mark(Object *object);

void geece_ptr_scanner(Object *object, void (*mark_function)(Object *obj));