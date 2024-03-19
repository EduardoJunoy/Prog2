#include "list.h"
#include <stdio.h>
#include <stdlib.h>




typedef struct _NodeList
{
    void *data;
    struct _NodeList *next;
} NodeList;

struct _List
{
    NodeList *last;
};

NodeList *node_new () {
    NodeList *pn = NULL;
    pn = (NodeList *) malloc(sizeof(NodeList));
    if (!pn) {
        return NULL;
    }
    pn ->data = NULL;
    pn ->next = NULL;
    return pn;
}

List *list_new() {
    List *pl = (List *) malloc(sizeof(List));
    if (!pl) {
        return NULL;
    }
    pl->last = NULL;
    return pl;
}

Bool list_isEmpty(const List *pl) {
    return pl->last == NULL;
}

Status list_pushFront (List *pl , void *e) {
    NodeList *pn = NULL;
    if (pl == NULL || e == NULL) {
        return ERROR;
    }
    pn = node_new ();
    if (pn == NULL) {
        return ERROR;
    }
    pn->data = (void *)e;
    if (list_isEmpty (pl)) {
        pn ->next = pn;
        pl ->last = pn;
    } 
    else {
        pn ->next = pl ->last ->next;
        pl ->last ->next = pn;
    }
    return OK;
}


Status list_pushBack (List *pl , void *e) {
    NodeList *pn = NULL;
    if (pl == NULL || e == NULL) {
        return ERROR;
    }
    pn = node_new ();
    if (pn == NULL) {
        return ERROR;
    }
    pn ->data = (void *)e;
    if (list_isEmpty (pl) == TRUE) {
        pn ->next = pn;
        pl ->last = pn;
    }

    else {
        pn ->next = pl ->last ->next;
        pl ->last ->next = pn;
        pl ->last = pn;
    }
    return OK;
}

Status list_pushInOrder(List *pl, void *e, P_ele_cmp f, int order) {
    NodeList *new_node, *current, *prev;
    if (!pl || !e || !f) {
        return ERROR;
    }

    new_node = (NodeList *) malloc(sizeof(NodeList));
    if (!new_node) {
        return ERROR;
    }
    new_node->data = e;

    if (list_isEmpty(pl)) {
        new_node->next = new_node;
        pl->last = new_node;
        return OK;
    }

    current = pl->last->next;
    prev = pl->last;

    while (current != pl->last && order * f(e, current->data) > 0) {
        prev = current;
        current = current->next;
    }

    new_node->next = current;
    prev->next = new_node;

    if (current == pl->last) {
        pl->last = new_node;
    }

    return OK;
}

void * list_popFront (List *pl) {
    NodeList *pn = NULL;
    void *pe = NULL;
    if (pl == NULL || list_isEmpty (pl) == TRUE) {
        return NULL;
    }

    pn = pl ->last ->next;
    pe = pn ->data;

    if (pl ->last ->next == pl ->last) {
        pl ->last = NULL;
    }    
    else {
        pl ->last ->next = pn ->next;
    }
    free(pn);
    return pe;
}

void * list_popBack (List *pl) {
    NodeList *pn = NULL;
    void *pe = NULL;
    if (pl == NULL || list_isEmpty (pl) == TRUE) {
        return NULL;
    }
    if (pl ->last ->next == pl ->last) {
        pe = pl ->last ->data;
        free(pl ->last);
        pl ->last = NULL;
        return pe;
    }

    pn = pl ->last;

    while (pn ->next != pl ->last) {
        pn = pn ->next;
    }

    pe = pl ->last ->data;
    pn ->next = pl ->last ->next;
    free(pl ->last);
    pl ->last = pn;

    return pe;
}

void list_free(List *pl) {
    if (!pl) {
        return;
    }
    while (!list_isEmpty(pl)) {
        list_popFront(pl);
    }
    free(pl);
}

size_t list_size(const List *pl) {
    if (list_isEmpty(pl)) {
        return 0;
    }
    size_t count = 1;
    NodeList *current = pl->last->next;
    while (current != pl->last) {
        count++;
        current = current->next;
    }
    return count;
}

int list_print(FILE *fp, const List *pl, P_ele_print f) {
    if (!pl || !fp || !f) {
        return -1;
    }

    if (list_isEmpty(pl)) {
        return 0;
    }

    NodeList *current = pl->last->next;
    int count = 0, printed;

    count = fprintf(fp, "SIZE: %ld\n", list_size(pl));

    do {
        printed = f(fp, current->data);
        printed += fprintf(fp, " ");
        if (printed < 0) {
            return -1;
        }
        count += printed;
        current = current->next;
    } while (current != pl->last->next);

    return count;
}
