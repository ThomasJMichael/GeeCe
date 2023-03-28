//
// Created by Jacob on 3/24/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "object.h"
#include "root_table.h"

void test_add_to_root_table_collisions() {
    printf("Testing add_to_root_table() with collisions...\n");

    RootTable table;
    init_root_table(&table, 4);

    Object *object1 = new_object(sizeof("value1"), NULL);
    strncpy(object1->data, "value1", sizeof("value1"));
    Object *object2 = new_object(sizeof("value2"), NULL);
    strncpy(object2->data, "value2", sizeof("value2"));
    Object *object3 = new_object(sizeof("value3"), NULL);
    strncpy(object3->data, "value3", sizeof("value3"));
    Object *object4 = new_object(sizeof("value4"), NULL);
    strncpy(object4->data, "value4", sizeof("value4"));

    add_to_root_table(&table, "key1", object1);
    add_to_root_table(&table, "key2", object2);
    add_to_root_table(&table, "key3", object3);
    add_to_root_table(&table, "key4", object4);

    Object *result = get_from_root_table(&table, "key1");
    if (strcmp(result->data, object1->data) != 0){
        printf("get_from_root_table() failed. Expected: %s, Actual: %s\n", object1->data, result->data);
        return;
    }

    result = get_from_root_table(&table, "key2");
    if (strcmp(result->data, object2->data) != 0){
        printf("get_from_root_table() failed. Expected: %s, Actual: %s\n", object2->data, result->data);
        return;
    }

    result = get_from_root_table(&table, "key3");
    if (strcmp(result->data, object3->data) != 0){
        printf("get_from_root_table() failed. Expected: %s, Actual: %s\n", object3->data, result->data);
        return;
    }

    result = get_from_root_table(&table, "key4");
    if (strcmp(result->data, object4->data) != 0){
        printf("get_from_root_table() failed. Expected: %s, Actual: %s\n", object4->data, result->data);
        return;
    }

    printf("All tests passed!\n");
}


int main(){

    test_add_to_root_table_collisions();

    RootTable table;
    init_root_table(&table, 4);

    Object *object1 = new_object(sizeof("value1"), NULL);
    strncpy(object1->data, "value1", sizeof("value1"));
    Object *object2 = new_object(sizeof("value2"), NULL);
    strncpy(object2->data, "value2", sizeof("value2"));
    Object *object3 = new_object(sizeof("value3"), NULL);
    strncpy(object3->data, "value3", sizeof("value3"));
    Object *object4 = new_object(sizeof("value4"), NULL);
    strncpy(object4->data, "value4", sizeof("value4"));

    add_to_root_table(&table, "key1", object1);
    add_to_root_table(&table, "key2", object2);

    // Test get_from_root_table()
    Object *result = get_from_root_table(&table, "key1");
    if (strcmp(result->data, object1->data) != 0){
        printf("get_from_root_table() failed. Expected: %p, Actual: %p\n", (void*)&object1, (void*)result);
        return 1;
    }

    // Test remove_from_root_table()
    remove_from_root_table(&table, "key2");
    result = get_from_root_table(&table, "key2");
    if (result != NULL){
        printf("remove_from_root_table() failed\n");
        return 1;
    }

    // Test rehash_root_table()
    add_to_root_table(&table, "key3", object3);
    rehash_root_table(&table);
    result = get_from_root_table(&table, "key1");
    if (strcmp(result->data, object1->data) != 0){
        printf("rehash_root_table() 1 failed\n");
        return 1;
    }
    result = get_from_root_table(&table, "key3");
    if (strcmp(result->data, object3->data) != 0){
        printf("rehash_root_table() 2 failed\n");
        return 1;
    }

    destroy_root_table(&table);
    return 0;
}
