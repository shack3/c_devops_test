# ifndef __TEMPORAL_NODE_H__
# define __TEMPORAL_NODE_H__

#include "coordinate_node.h"
#include "date.h"

typedef struct _tTemporalNode {
    tCoordinateNode* coordinateNode;
    tDateTime date;
    struct _tTemporalNode* next;
} tTemporalNode;

typedef struct _tListDocuments {
    char** documents;
    int numDocuments;
} tListDocuments;
 
tTemporalNode* temporalNode_init(tDateTime date);
void temporalNode_free(tTemporalNode* node);

void temporalNode_addPersonCoordinate(tTemporalNode* node, tCoordinate coordinate, char* person);
void temporalNode_removePerson(tTemporalNode* node, char* person);
tListDocuments temporalNode_findPersonsContatcs(tTemporalNode* node, char* person);
int temporalNode_countPersons(tTemporalNode* node);
int temporalNode_cmpDate(tTemporalNode* node, tDateTime date);

# endif