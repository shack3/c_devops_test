#include "unity.h"
# include "coordinate_node.h"

// Test functions

void setUp(void) {
    // This function is run before each test
}

void tearDown(void) {
    // This function is run after each test
}

void test_coordinateNode_init(void) {
    tCoordinateNode *node = coordinateNode_init();
    TEST_ASSERT_NOT_NULL(node);
    
    tCoordinate coord = {1.234, 5.678};
    node->coordinate = coord;
    
    TEST_ASSERT_EQUAL_FLOAT(1.234, node->coordinate.latitude);
    TEST_ASSERT_EQUAL_FLOAT(5.678, node->coordinate.longitude);
    TEST_ASSERT_EQUAL_INT(0, node->numPersons);
    TEST_ASSERT_NULL(node->persons);
    TEST_ASSERT_NULL(node->next);
    coordinateNode_free(node);
}

void test_coordinateNode_add_and_find_person(void) {
    tCoordinate coord = {1.234, 5.678};
    tCoordinateNode *node = coordinateNode_init();
    node->coordinate = coord;

    coordinateNode_addPerson(node, "Alice");
    TEST_ASSERT_EQUAL_INT(1, coordinateNode_countPersons(node));
    TEST_ASSERT_EQUAL_INT(0, coordinateNode_findPerson(node, "Alice"));
    coordinateNode_free(node);
}

void test_coordinateNode_remove_person(void) {
    tCoordinate coord = {1.234, 5.678};
    tCoordinateNode *node = coordinateNode_init();
    node->coordinate = coord;

    coordinateNode_addPerson(node, "Alice");
    coordinateNode_removePerson(node, "Alice");
    TEST_ASSERT_EQUAL_INT(-1, coordinateNode_findPerson(node, "Alice"));
    coordinateNode_free(node);
}

void test_coordinateNode_countPersons(void) {
    tCoordinate coord = {1.234, 5.678};
    tCoordinateNode *node = coordinateNode_init();
    node->coordinate = coord;

    coordinateNode_addPerson(node, "Alice");
    coordinateNode_addPerson(node, "Bob");
    TEST_ASSERT_EQUAL_INT(2, coordinateNode_countPersons(node));
    coordinateNode_free(node);
}

void test_coordinateNode_equal(void) {
    tCoordinateNode *node1 = coordinateNode_init();
    tCoordinate coord1 = {1.234, 5.678};
    node1->coordinate = coord1;

    tCoordinateNode *node2 = coordinateNode_init();
    tCoordinate coord2 = {1.234, 5.678};
    node2->coordinate = coord2;

    TEST_ASSERT_EQUAL_INT(1, coordinateNode_equal(node1, node2));
    coordinateNode_free(node1);
    coordinateNode_free(node2);
}

void test_coordinateNode_hasCoordinate(void) {
    tCoordinate coord = {1.234, 5.678};
    tCoordinateNode *node = coordinateNode_init();
    node->coordinate = coord;

    TEST_ASSERT_EQUAL_INT(1, coordinateNode_hasCoordinate(node, coord));
    coordinateNode_free(node);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_coordinateNode_init);
    RUN_TEST(test_coordinateNode_add_and_find_person);
    RUN_TEST(test_coordinateNode_remove_person);
    RUN_TEST(test_coordinateNode_countPersons);
    RUN_TEST(test_coordinateNode_equal);
    RUN_TEST(test_coordinateNode_hasCoordinate);
    return UNITY_END();
}