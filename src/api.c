#include "api.h"

const char* api_version() {
    return "1.0.0";
}

tApiError api_init(tApiData* data) {
    if (!data) {
        return E_MEMORY_ERROR;
    }

    population_init(&data->population);
    return E_SUCCESS;
}

void api_free(tApiData* data) {
    if (data) {
        population_free(&data->population);
    }
}

tApiError api_loadData(tApiData* data, const char* filename, bool reset) {
    if (!data) {
        return E_MEMORY_ERROR;
    }

    if (reset) {
        api_free(data);
        api_init(data);
    }

    CSVFile* csv = read_csv(filename, ',');
    if (!csv) {
        return E_FILE_NOT_FOUND;
    }

    if (csv->header_count != 7) {
        free_csv(csv);
        return E_INVALID_ENTRY_FORMAT;
    }

    for (int i = 0; i < csv->row_count; i++) {

        printf("Loading person %d\n", i);
        
        tPerson person;
        person.document = get_item_by_row_and_column_name(csv, i, "document");
        if (!person.document) {
            free_csv(csv);
            return E_INVALID_ENTRY_FORMAT;
        }

        person.name = get_item_by_row_and_column_name(csv, i, "name");
        if (!person.name) {
            free_csv(csv);
            return E_INVALID_ENTRY_FORMAT;
        }

        person.surname = get_item_by_row_and_column_name(csv, i, "surname");
        if (!person.surname) {
            free_csv(csv);
            return E_INVALID_ENTRY_FORMAT;
        }

        person.cp = get_item_by_row_and_column_name(csv, i, "cp");
        if (!person.cp) {
            free_csv(csv);
            return E_INVALID_ENTRY_FORMAT;
        }

        person.email = get_item_by_row_and_column_name(csv, i, "email");
        if (!person.email) {
            free_csv(csv);
            return E_INVALID_ENTRY_FORMAT;
        }

        person.address = get_item_by_row_and_column_name(csv, i, "address");
        if (!person.address) {
            free_csv(csv);
            return E_INVALID_ENTRY_FORMAT;
        }

        char* birthday = get_item_by_row_and_column_name(csv, i, "birthday");
        if (!birthday) {
            free_csv(csv);
            return E_INVALID_ENTRY_FORMAT;
        }
        sscanf(birthday, "%d/%d/%d", &(person.birthday.day), &(person.birthday.month), &(person.birthday.year));
       
        population_add(&data->population, person);
    }

    free_csv(csv);
    return E_SUCCESS;
}
    

