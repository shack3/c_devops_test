#include "unity.h"
#include "csv.h"

void setUp(void) {
    // This is run before EACH test
}

void tearDown(void) {
    // This is run after EACH test
}

void test_read_csv_file(void) {
    CSVFile *csv = read_csv("example.csv", ',');
    TEST_ASSERT_NOT_NULL(csv);

    TEST_ASSERT_EQUAL(2, csv->row_count);
    TEST_ASSERT_EQUAL(7, csv->header_count);
    TEST_ASSERT_EQUAL(0, get_column_index(csv, "name"));
    TEST_ASSERT_EQUAL(1, get_column_index(csv, "surname"));
    TEST_ASSERT_EQUAL(4, get_column_index(csv, "document"));
    
    free_csv(csv);
}

void test_get_item_by_row_and_column_name(void) {
    CSVFile *csv = read_csv("example.csv", ',');
    TEST_ASSERT_NOT_NULL(csv);
    
    TEST_ASSERT_EQUAL_STRING("angel", get_item_by_row_and_column_name(csv, 0, "name"));
    TEST_ASSERT_EQUAL_STRING("panizo", get_item_by_row_and_column_name(csv, 0, "surname"));
    TEST_ASSERT_EQUAL_STRING("98001567", get_item_by_row_and_column_name(csv, 0, "document"));

    TEST_ASSERT_EQUAL_STRING("harry", get_item_by_row_and_column_name(csv, 1, "name"));
    TEST_ASSERT_EQUAL_STRING("potter", get_item_by_row_and_column_name(csv, 1, "surname"));
    TEST_ASSERT_EQUAL_STRING("49001567", get_item_by_row_and_column_name(csv, 1, "document"));
    
    free_csv(csv);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_read_csv_file);
    RUN_TEST(test_get_item_by_row_and_column_name);
    return UNITY_END();
}
