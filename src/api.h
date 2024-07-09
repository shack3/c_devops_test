# ifndef __DEVOPS_API_H__
# define __DEVOPS_API_H__

# include <string.h>
# include "csv.h"
# include "error.h"
# include "person.h"

typedef struct _ApiData {
    tPopulation population;    
} tApiData;

const char* api_version();

tApiError api_init(tApiData* data);
tApiError api_loadData(tApiData* data, const char* filename, bool reset);
void api_free(tApiData* data);

# endif

