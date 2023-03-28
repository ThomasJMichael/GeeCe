//
// Created by Jacob on 3/24/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "object.h"
#include "root_table.h"

void test_init_root_table() {
    printf("test_init_root_table\n");
    RootTable table;
    RootTable *result = init_root_table(&table, 10);

    // Check that the function returns a non-NULL pointer
    if (result == NULL) {
        printf("Error: init_root_table returned NULL\n");
        return;
    }

    // Check that the bucket_count is set correctly
    if (result->bucket_count != 10) {
        printf("Error: init_root_table did not set bucket_count correctly\n");
        return;
    }

    // Check that bucket_heads is a non-NULL pointer
    if (result->bucket_heads == NULL) {
        printf("Error: init_root_table did not allocate memory for bucket_heads\n");
        return;
    }

    // Check that all of the elements in bucket_heads are NULL
    for (size_t i = 0; i < result->bucket_count; i++) {
        if (result->bucket_heads[i] != NULL) {
            printf("Error: init_root_table did not set bucket_heads[%zu] to NULL\n", i);
            return;
        }
    }

    printf("test_init_root_table passed\n");
}


void test_add_to_root_table() {
    printf("test_add_to_root_table\n");
    RootTable *table = malloc(sizeof(RootTable));
    init_root_table(table, 16);

    // Create some objects to add to the root table
    Object *obj1 = new_object(1, free);
    Object *obj2 = new_object(1, free);
    Object *obj3 = new_object(1, free);

    // Add objects to the root table
    bool added = add_to_root_table(table, "1", obj1);
    assert(added);
    added = add_to_root_table(table, "2", obj2);
    assert(added);
    added = add_to_root_table(table, "3", obj3);
    assert(added);

    // Get the objects from the root table and verify they are correct
    Object *retrieved_object = get_from_root_table(table, "1");
    assert(retrieved_object == obj1);
    retrieved_object = get_from_root_table(table, "2");
    assert(retrieved_object == obj2);
    retrieved_object = get_from_root_table(table, "3");
    assert(retrieved_object == obj3);

    // Remove the objects from the root table
    bool removed = remove_from_root_table(table, "1");
    assert(removed);
    removed = remove_from_root_table(table, "2");
    assert(removed);
    removed = remove_from_root_table(table, "3");
    assert(removed);

    // Try to get the objects again and verify they are not found
    retrieved_object = get_from_root_table(table, "1");
    assert(retrieved_object == NULL);
    retrieved_object = get_from_root_table(table, "2");
    assert(retrieved_object == NULL);
    retrieved_object = get_from_root_table(table, "3");
    assert(retrieved_object == NULL);

    // Destroy the root table and objects
    destroy_root_table(table);
    destroy_object(obj1);
    destroy_object(obj2);
    destroy_object(obj3);
}


void test_remove_from_root_table() {
    printf("Running remove_from_root_table test...\n");
    RootTable *table = malloc(sizeof(RootTable));
    init_root_table(table, 8);

    // Create test objects
    Object *obj1 = new_object(1, free);
    Object *obj2 = new_object(1, free);
    Object *obj3 = new_object(1, free);

    // Add objects to table
    add_to_root_table(table, "obj1", obj1);
    add_to_root_table(table, "obj2", obj2);
    add_to_root_table(table, "obj3", obj3);

    // Remove object 2 from table
    bool removed = remove_from_root_table(table, "obj2");
    if (!removed) {
        printf("remove_from_root_table test failed: object was not removed from table\n");
        return;
    }

    // Verify that object 2 is no longer in the table
    Object *found = get_from_root_table(table, "obj2");
    if (found != NULL) {
        printf("remove_from_root_table test failed: object was found in table after removal\n");
        return;
    }

    // Destroy remaining objects and table
    destroy_root_table(table);

    printf("remove_from_root_table test passed.\n");
}


void test_get_from_root_table() {
    printf("test_get_from_root_table\n");
    // Initialize root table with initial capacity of 2
    RootTable *table = malloc(sizeof(RootTable));
    RootTable *root_table = init_root_table(table, 2);
    assert(root_table != NULL);

    // Create test objects and add to root table
    Object *obj1 = new_object(sizeof(Object), NULL);
    add_to_root_table(root_table, "key1", obj1);

    Object *obj2 = new_object(sizeof(Object), NULL);
    add_to_root_table(root_table, "key2", obj2);

    Object *obj3 = new_object(sizeof(Object), NULL);
    add_to_root_table(root_table, "key3", obj3);

    // Test that getting an existing key returns the correct object
    Object *result = get_from_root_table(root_table, "key2");
    assert(result == obj2);

    // Test that getting a non-existing key returns NULL
    result = get_from_root_table(root_table, "key4");
    assert(result == NULL);

    // Free the objects and destroy the root table
    clear_root_table(table);
    destroy_root_table(root_table);
}

void test_clear_root_table() {
    printf("test_clear_root_table\n");
    // Create a root table
    RootTable table;
    init_root_table(&table, 16);

    // Create some objects to store in the table
    Object *object1 = new_object(sizeof(int), NULL);
    Object *object2 = new_object(sizeof(double), NULL);
    Object *object3 = new_object(sizeof(char), NULL);

    // Add the objects to the table
    add_to_root_table(&table, "int", object1);
    add_to_root_table(&table, "double", object2);
    add_to_root_table(&table, "char", object3);

    // Clear the table
    bool success = clear_root_table(&table);

    // Check that the table was successfully cleared
    if (!success) {
        printf("test_clear_root_table FAILED: clear_root_table returned false\n");
        return;
    }

    // Check that the table is empty
    for (size_t i = 0; i < table.bucket_count; ++i) {
        Bucket *currentBucket = table.bucket_heads[i];
        while (currentBucket != NULL) {
            printf("test_clear_root_table FAILED: table was not cleared\n");
            return;
        }
    }

    clear_root_table(&table);

    printf("test_clear_root_table PASSED\n");
}



void test_destroy_root_table() {
    printf("test_destroy_root_table\n");
    RootTable *table = malloc(sizeof(RootTable));
    init_root_table(table, 10);

    // Add some entries to the table
    Object *object1 = new_object(10, NULL);
    Object *object2 = new_object(20, NULL);
    add_to_root_table(table, "key1", object1);
    add_to_root_table(table, "key2", object2);

    // Destroy the table and verify that it was successful
    bool result = destroy_root_table(table);
    if (!result) {
        printf("Failed to destroy root table.\n");
    }
}


void test_rehash_root_table() {
    printf("test_rehash_root_table\n");
    RootTable table;
    init_root_table(&table, 10);

    Object obj1;
    add_to_root_table(&table, "key1", &obj1);

    bool result = rehash_root_table(&table);

    if (result) {
        Object *obj = get_from_root_table(&table, "key1");
        if (obj != NULL) {
            printf("rehash_root_table test passed.\n");
        } else {
            printf("rehash_root_table test failed. Key not found in table after rehashing.\n");
        }
    } else {
        printf("rehash_root_table test failed.\n");
    }
}


int main(){
    test_add_to_root_table();
    test_clear_root_table();
    test_get_from_root_table();
    test_init_root_table();
    test_rehash_root_table();
    test_remove_from_root_table();
    test_destroy_root_table();
    return 0;
}
