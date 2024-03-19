#include "bstree.h"
#include "search_queue.h"
#include <stdlib.h>

struct _SearchQueue {
    BSTree *data;
};

/**
 * @brief This function creates and initializes a SearchQueue.
 *
 * Allocates memory for the new SearchQueue. When creating a SearchQueue it is
 * necessary to specify the pointers to functions that:
 * - Print an element.
 * - Compare two elements
 *
 * @param print_ele Pointer to the function that prints a SearchQueue element.
 * @param cmp_ele Pointer to a function that compares two SearchQueue elements.
 *
 * @return A pointer to the SearchQueue if it could be created or NULL in case
 * of error.
 **/
SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele) {
    SearchQueue *sq = NULL;
    if (print_ele && cmp_ele) {
        sq = (SearchQueue *) malloc (sizeof(SearchQueue));
        if (sq) {
            sq->data = tree_init(print_ele, cmp_ele);
            if (!sq->data) {
                free(sq);
                
                sq = NULL;
            }
        }
    }

    return sq;
}

void search_queue_free(SearchQueue *q) {
    tree_destroy(q->data);
    free(q);
    
}

Bool search_queue_isEmpty(const SearchQueue *q) {
    return tree_isEmpty(q->data);
}

Status search_queue_push(SearchQueue *q, void *ele) {
    return tree_insert(q->data, ele);
}

void *search_queue_pop(SearchQueue *q) {
    if (q == NULL || q->data == NULL) {
        return NULL;
    }
    void *e = NULL;
    e = tree_find_min(q->data);
    if (!e) return NULL;
    tree_remove(q->data, e);

    return e;
}

void *search_queue_getFront(const SearchQueue *q) {
    return tree_find_min(q->data);
}

void *search_queue_getBack(const SearchQueue *q) {
    return tree_find_max(q->data);
}

size_t search_queue_size(const SearchQueue *q) {
    return tree_size(q->data);
}

int search_queue_print(FILE *fp, const SearchQueue *q) {
    return tree_preOrder(fp, q->data);
}
