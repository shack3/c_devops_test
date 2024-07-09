# include "temporal_node.h"
# include "coordinate_node.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

tTemporalNode* temporalNode_init(tDateTime date) {
    tTemporalNode* node = (tTemporalNode*)malloc(sizeof(tTemporalNode));
    if (node) {
        node->coordinateNode = NULL;
        node->date = date;
        node->next = NULL;
    }
    return node;
}

void temporalNode_free(tTemporalNode* node) {
    if (node) {
        if (node->coordinateNode) {
            coordinateNode_free(node->coordinateNode);
        }
        free(node);
    }
}

void temporalNode_addPersonCoordinate(tTemporalNode* node, tCoordinate coordinate, char* person) {
    if (node && person) {
        if (!node->coordinateNode) {
            node->coordinateNode = coordinateNode_init();
            node->coordinateNode->coordinate = coordinate;
            coordinateNode_addPerson(node->coordinateNode, person);
        }
        else {
            tCoordinateNode* aux = node->coordinateNode;
            if (coordinateNode_hasCoordinate(aux, coordinate)) {
                coordinateNode_addPerson(aux, person);
                return;
            }

            while (aux->next) {
                aux = aux->next;
                if (coordinateNode_hasCoordinate(aux, coordinate)) {
                    coordinateNode_addPerson(aux, person);
                    return;
                }
            }
            aux->next = coordinateNode_init();
            aux->next->coordinate = coordinate;
            coordinateNode_addPerson(aux->next, person);
        }
    }        
}

void temporalNode_removePerson(tTemporalNode* node, char* person) {
    if (node && person) {
        tCoordinateNode* aux = node->coordinateNode;
        while (aux) {
            coordinateNode_removePerson(aux, person);
            aux = aux->next;
        }
    }
}

tListDocuments temporalNode_findPersonsContatcs(tTemporalNode* node, char* person) {
    tListDocuments list = {NULL, 0};
    if (node && person) {
        tCoordinateNode* aux = node->coordinateNode;
        while (aux) {
            if (coordinateNode_findPerson(aux, person) != -1) {
                char** persons = aux->persons;
                for (int i = 0; i < aux->numPersons; i++) {
                    if (strcmp(persons[i], person) != 0) {
                        list.numDocuments++;
                        list.documents = (char**)realloc(list.documents, list.numDocuments * sizeof(char*));
                        list.documents[list.numDocuments - 1] = (char*)malloc((strlen(persons[i]) + 1) * sizeof(char));
                        strcpy(list.documents[list.numDocuments - 1], persons[i]);
                    }
                }
            }
            aux = aux->next;
        }

        // remove repeated documents
        // for (int i = 0; i < list.numDocuments; i++) {
        //     for (int j = i + 1; j < list.numDocuments; j++) {
        //         if (strcmp(list.documents[i], list.documents[j]) == 0) {
        //             free(list.documents[j]);
        //             for (int k = j; k < list.numDocuments - 1; k++) {
        //                 list.documents[k] = list.documents[k + 1];
        //             }
        //             list.numDocuments--;
        //             list.documents = (char**)realloc(list.documents, list.numDocuments * sizeof(char*));
        //             j--;
        //         }
        //     }
        // }
    }
    return list;
}

int temporalNode_countPersons(tTemporalNode* node) {
    int count = 0;
    if (node) {
        tCoordinateNode* aux = node->coordinateNode;
        while (aux) {
            count += aux->numPersons;
            aux = aux->next;
        }
    }
    return count;
}

int temporalNode_cmpDate(tTemporalNode* node, tDateTime date) {
    if (node->date.date.year < date.date.year) {
        return -1;
    }
    if (node->date.date.year > date.date.year) {
        return 1;
    }
    // Check month
    if (node->date.date.month < date.date.month) {
        return -1;
    }
    if (node->date.date.month > date.date.month) {
        return 1;
    }  
    // Check day
    if (node->date.date.day < date.date.day) {
        return -1;
    }
    if (node->date.date.day > date.date.day) {
        return 1;
    }
    // Check hour
    if (node->date.time.hour < date.time.hour) {
        return -1;
    }
    if (node->date.time.hour > date.time.hour) {
        return 1;
    }
    // Check minutes
    if (node->date.time.minutes < date.time.minutes) {
        return -1;
    }
    if (node->date.time.minutes > date.time.minutes) {
        return 1;
    }
    
    return 0;
}