#include <unity.h>
#include "mylib.h"

void setUp(void) {
    // Set up before each test
}

void tearDown(void) {
    // Clean up after each test
}

void test_add(void) {
    TEST_ASSERT_EQUAL(5, add(2, 3));
    TEST_ASSERT_EQUAL(0, add(-1, 1));
    TEST_ASSERT_EQUAL(-3, add(-1, -1));
}

void test_subtract(void) {
    TEST_ASSERT_EQUAL(1, subtract(3, 2));
    TEST_ASSERT_EQUAL(2, subtract(1, -1));
    TEST_ASSERT_EQUAL(0, subtract(-1, -1));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_add);
    RUN_TEST(test_subtract);

    return UNITY_END();
}
