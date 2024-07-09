#include <stdlib.h>
#include "unity.h"
#include "temporal_node.h"
#include "coordinate_node.h"
#include "date.h"

void setUp(void) {
    // This function is run before each test
}

void tearDown(void) {
    // This function is run after each test
}

void test_temporalNode_init(void) {
    tDate date = {1, 1, 2023};
    tTime time = {0, 0};
    tDateTime dateTime = {date, time};

    tTemporalNode *node = temporalNode_init(dateTime);
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL_INT(1, node->date.date.day);
    TEST_ASSERT_EQUAL_INT(1, node->date.date.month);
    TEST_ASSERT_EQUAL_INT(2023, node->date.date.year);
    TEST_ASSERT_EQUAL_INT(0, node->date.time.hour);
    TEST_ASSERT_EQUAL_INT(0, node->date.time.minutes);
    TEST_ASSERT_NULL(node->coordinateNode);
    TEST_ASSERT_NULL(node->next);
    temporalNode_free(node);
}

void test_temporalNode_addPersonCoordinate(void) {
    tDate date = {1, 1, 2023};
    tTime time = {0, 0};
    tDateTime dateTime = {date, time};
    tCoordinate coord = {1.234, 5.678};
    tTemporalNode *node = temporalNode_init(dateTime);
    temporalNode_addPersonCoordinate(node, coord, "Alice");
    temporalNode_addPersonCoordinate(node, coord, "Bob");
    TEST_ASSERT_NOT_NULL(node->coordinateNode);
    TEST_ASSERT_EQUAL_FLOAT(1.234, node->coordinateNode->coordinate.latitude);
    TEST_ASSERT_EQUAL_FLOAT(5.678, node->coordinateNode->coordinate.longitude);
    TEST_ASSERT_EQUAL_INT(2, coordinateNode_countPersons(node->coordinateNode));
    temporalNode_free(node);
}

void test_temporalNode_removePerson(void) {
    tDate date = {1, 1, 2023};
    tTime time = {0, 0};
    tDateTime dateTime = {date, time};
    tCoordinate coord = {1.234, 5.678};
    tTemporalNode *node = temporalNode_init(dateTime);
    temporalNode_addPersonCoordinate(node, coord, "Alice");
    temporalNode_removePerson(node, "Alice");
    TEST_ASSERT_EQUAL_INT(0, coordinateNode_countPersons(node->coordinateNode));
    temporalNode_free(node);
}

void test_temporalNode_findPersonsContatcs(void) {
    tDate date = {1, 1, 2023};
    tTime time = {0, 0};
    tDateTime dateTime = {date, time};
    tCoordinate coord = {1.234, 5.678};
    tTemporalNode *node = temporalNode_init(dateTime);
    temporalNode_addPersonCoordinate(node, coord, "Alice");
    temporalNode_addPersonCoordinate(node, coord, "Bob");
    tListDocuments contacts = temporalNode_findPersonsContatcs(node, "Alice");
    TEST_ASSERT_EQUAL_INT(1, contacts.numDocuments);
    TEST_ASSERT_EQUAL_STRING("Bob", contacts.documents[0]);
    free(contacts.documents);
    temporalNode_free(node);
}

void test_temporalNode_countPersons(void) {
    tDate date = {1, 1, 2023};
    tTime time = {0, 0};
    tDateTime dateTime = {date, time};
    tCoordinate coord = {1.234, 5.678};
    tTemporalNode *node = temporalNode_init(dateTime);
    temporalNode_addPersonCoordinate(node, coord, "Alice");
    temporalNode_addPersonCoordinate(node, coord, "Bob");
    TEST_ASSERT_EQUAL_INT(2, temporalNode_countPersons(node));
    temporalNode_free(node);
}

void test_temporalNode_cmpDate(void) {
    tDate date1 = {1, 1, 2023};
    tTime time = {0, 0};
    tDateTime dateTime1 = {date1, time};

    tDate date2 = {2, 1, 2023};
    tDateTime dateTime2 = {date2, time};

    tTemporalNode *node = temporalNode_init(dateTime1);
    TEST_ASSERT_EQUAL_INT(0, temporalNode_cmpDate(node, dateTime1));
    TEST_ASSERT_EQUAL_INT(-1, temporalNode_cmpDate(node, dateTime2));
    temporalNode_free(node);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_temporalNode_init);
    RUN_TEST(test_temporalNode_addPersonCoordinate);
    RUN_TEST(test_temporalNode_removePerson);
    RUN_TEST(test_temporalNode_findPersonsContatcs);
    RUN_TEST(test_temporalNode_countPersons);
    RUN_TEST(test_temporalNode_cmpDate);
    return UNITY_END();
}