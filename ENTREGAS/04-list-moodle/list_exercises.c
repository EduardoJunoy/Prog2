#include "list_exercises.h"
#include "elements.h"
#include "list.h"
#include "types.h"

void list_delete(List *pl, const void *elem, elem_cmp_fn compare) {
    if (pl == NULL || elem == NULL || compare == NULL ||  list_isEmpty(pl)==TRUE)
    {
        return ;
    }
    Node *pn, *previous = NULL;

    for (pn = pl->first; pn != NULL; pn = pn->next) {
        if (compare(elem, pn->info) == 0) {
            if (previous == NULL) {
                pl->first = pn->next;
            } else {
                previous->next = pn->next;
            }
            free(pn);
            break;
        }
        previous = pn;
    }
}

List *list_copy(List *pl) {
    
    if (pl == NULL || list_isEmpty(pl) == TRUE)
    {
        return NULL;
    }
    
    List *copy = list_new();
    if (!copy)
    {
        return NULL;
    }
            
    Node *pn, *last_copied = NULL;

    for (pn = pl->first; pn != NULL; pn = pn->next) {
        Node *node_copy = malloc(sizeof(Node));
        if (!node_copy) {
            list_free(copy);    
            return NULL;
        }
        node_copy->info = pn->info;
        node_copy->next = NULL;

        if (last_copied == NULL) {
            copy->first = node_copy;
        } else {
            last_copied->next = node_copy;
        }
        last_copied = node_copy;
    }
    return copy;
}