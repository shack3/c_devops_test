#include <stdio.h>
#include "api.h"

int main() {
    printf("Initializing API\n");

    const char *filename = "example.csv";
    char delimiter = ',';
    tApiError error;

    tApiData data;
    error = api_init(&data);
    if (error != E_SUCCESS) {
        printf("Error initializing API: %i\n", error);
        return 1;
    }
    
    printf("Loading csv file\n");
    error = api_loadData(&data, filename, true);
    if (error != E_SUCCESS) {
        printf("Error loading data: %i\n", error);
        return 1;
    }

    printf("Printing Population\n");
    population_print(data.population);

    printf("Freeing data\n");
    api_free(&data);
    
    return 0;
}
