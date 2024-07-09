#ifndef CSV_H
#define CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store a single CSV row
typedef struct {
    char **fields;
    int field_count;
} CSVRow;

// Structure to store the entire CSV data
typedef struct {
    char **headers;
    int header_count;
    CSVRow *rows;
    int row_count;
} CSVFile;

// Function prototypes
CSVFile* read_csv(const char *filename, char delimiter);
void free_csv(CSVFile *csv);
char* get_item_by_row_and_column_name(CSVFile *csv, int row, const char *column);
int get_column_index(CSVFile *csv, const char *column);
int get_column_count(CSVFile *csv);
int get_row_count(CSVFile *csv);

#endif // CSV_H
