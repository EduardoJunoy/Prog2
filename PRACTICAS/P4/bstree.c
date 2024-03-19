#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

/* START [_BSTNode] */
typedef struct _BSTNode
{
  void *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree
{
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};
/* END [_BSTree] */

BSTNode *_tree_find_min_rec(BSTNode *pn);
void *_tree_find_max_rec(BSTNode *pn);
BSTNode *_tree_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);
BSTNode *_tree_contains_rec(P_ele_cmp cmp_ele, const void *elem, BSTNode *pn);
void *_tree_remove_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);

/*** BSTNode TAD private functions ***/
BSTNode *_bst_node_new()
{
  BSTNode *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn)
  {
    return NULL;
  }

  pn->left = NULL;
  pn->right = NULL;
  pn->info = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn)
{
  if (!pn)
  {
    return;
  }

  free(pn);
}

void _bst_node_free_rec(BSTNode *pn)
{
  if (!pn)
  {
    return;
  }

  _bst_node_free_rec(pn->left);
  _bst_node_free_rec(pn->right);
  _bst_node_free(pn);

  return;
}

int _bst_depth_rec(BSTNode *pn)
{
  int depth_l, depth_r;

  if (!pn)
  {
    return 0;
  }

  depth_l = _bst_depth_rec(pn->left);
  depth_r = _bst_depth_rec(pn->right);

  if (depth_r > depth_l)
  {
    return depth_r + 1;
  }
  else
  {
    return depth_l + 1;
  }
}

int _bst_size_rec(BSTNode *pn)
{
  int count = 0;

  if (!pn)
  {
    return count;
  }

  count += _bst_size_rec(pn->left);
  count += _bst_size_rec(pn->right);

  return count + 1;
}

int _bst_preOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele)
{
  int count = 0;

  if (!pn)
  {
    return count;
  }

  count += print_ele(pf, pn->info);
  count += _bst_preOrder_rec(pn->left, pf, print_ele);
  count += _bst_preOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele)
{
  int count = 0;

  if (!pn)
  {
    return count;
  }

  count += _bst_inOrder_rec(pn->left, pf, print_ele);
  count += print_ele(pf, pn->info);
  count += _bst_inOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_postOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele)
{
  int count = 0;

  if (!pn)
  {
    return count;
  }

  count += _bst_postOrder_rec(pn->left, pf, print_ele);
  count += _bst_postOrder_rec(pn->right, pf, print_ele);
  count += print_ele(pf, pn->info);

  return count;
}

/*** BSTree TAD functions ***/
BSTree *tree_init(P_ele_print print_ele, P_ele_cmp cmp_ele)
{
  BSTree *tree;

  if (!print_ele || !cmp_ele)
  {
    return NULL;
  }

  tree = malloc(sizeof(BSTree));
  if (!tree)
  {
    return NULL;
  }

  tree->root = NULL;
  tree->print_ele = print_ele;
  tree->cmp_ele = cmp_ele;

  return tree;
}

void tree_destroy(BSTree *tree)
{
  if (!tree)
  {
    return;
  }

  _bst_node_free_rec(tree->root);
  free(tree);

  return;
}

Bool tree_isEmpty(const BSTree *tree)
{
  if (!tree || !tree->root)
  {
    return TRUE;
  }
  return FALSE;
}

int tree_depth(const BSTree *tree)
{
  if (!tree)
  {
    return -1;
  }

  return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree *tree)
{
  if (!tree)
  {
    return -1;
  }

  return _bst_size_rec(tree->root);
}

int tree_preOrder(FILE *f, const BSTree *tree)
{
  if (!f || !tree)
  {
    return -1;
  }

  return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder(FILE *f, const BSTree *tree)
{
  if (!f || !tree)
  {
    return -1;
  }

  return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder(FILE *f, const BSTree *tree)
{
  if (!f || !tree)
  {
    return -1;
  }

  return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

void *tree_find_min(BSTree *tree)
{
  if (!tree)
    return NULL;

  return _tree_find_min_rec(tree->root);
}

BSTNode *_tree_find_min_rec(BSTNode *pn)
{
  if (pn == NULL || pn->left == NULL)
  {
    return pn->info;
  }

  return _tree_find_min_rec(pn->left);
}

void *tree_find_max(BSTree *tree)
{
  if (!tree)
    return NULL;

  return _tree_find_max_rec(tree->root);
}
void *_tree_find_max_rec(BSTNode *pn)
{
  if (pn == NULL || pn->right == NULL)
  {
    return pn->info;
  }

  return _tree_find_max_rec(pn->right);
}

Status tree_insert(BSTree *tree, const void *elem)
{
  if (tree == NULL || elem == NULL)
  {
    return ERROR;
  }
  BSTNode *pn;
  pn = _tree_insert_rec(tree->root, elem, tree->cmp_ele);
  if (pn == NULL)
  {
    return ERROR;
  }
  tree->root = pn;

  return OK;
}

BSTNode *_tree_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele)
{
  if (pn == NULL)
  {
    pn = _bst_node_new();
    if (pn == NULL)
    {
      return NULL;
    }
    pn->info = (void *)elem;
    return pn;
  }
  if (cmp_ele(elem, pn->info) < 0)
  {
    pn->left = _tree_insert_rec(pn->left, elem, cmp_ele);
  }
  else if (cmp_ele(elem, pn->info) > 0)
  {
    pn->right = _tree_insert_rec(pn->right, elem, cmp_ele);
  }

  return pn;
}

Bool bst_containsRec(BSTNode* pn, const void * pe, P_ele_cmp cmp_ele){
    int cmp = 0;
    Bool bool = FALSE;
    
    if(!pn)
        return ERROR;
    
    cmp = cmp_ele(pe, pn->info);
    if(cmp == 0)
        bool = TRUE;
    else if(cmp<0)
        return bst_containsRec(pn->left, pe, cmp_ele);
    else if(cmp > 0)
        return bst_containsRec(pn->right, pe, cmp_ele);
    
    return bool;
}

Bool tree_contains(BSTree * tree, const void * elem){
    Bool found = FALSE;
   
    if(!tree || !elem)
        return FALSE;
    
    found = bst_containsRec(tree->root, elem, tree->cmp_ele);
    
    return found;
   
}

Status tree_remove(BSTree *tree, const void *elem)
{
  if (tree == NULL || elem == NULL || tree_isEmpty(tree) == TRUE)
  {
    return ERROR;
  }
  BSTNode *n;

  n = _tree_remove_rec(tree->root, elem, tree->cmp_ele);
  tree->root = n;
  
  return OK;
}


void *_tree_remove_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele)
{
  BSTNode *ret_node = NULL, *aux_node = NULL;

  if (pn == NULL)
  {
    return NULL;
  }
  if (cmp_ele(elem, pn->info) < 0)
  {
    pn->left = _tree_remove_rec(pn->left, elem, cmp_ele);
  }
  else if (cmp_ele(elem, pn->info) > 0)
  {
    pn->right = _tree_remove_rec(pn->right, elem, cmp_ele);
  }
  else if (cmp_ele(elem, pn->info) == 0)
  {
    if (pn->left == NULL && pn->right == NULL)
    {
      _bst_node_free(pn);
      return NULL;
    }
    else if (pn->left == NULL && pn->right != NULL)
    {
      ret_node = pn->right;
      _bst_node_free(pn);
      return ret_node;
    }
    else if (pn->right == NULL && pn->left != NULL)
    {
      ret_node = pn->left;
      _bst_node_free(pn);
      return ret_node;
    }
    else if (pn->left != NULL && pn->right != NULL)
    {
      aux_node = _tree_find_min_rec(pn->right);
      pn->info = aux_node->info;
      pn->right = _tree_remove_rec(pn->right, aux_node->info, cmp_ele);
    }
  }
  return pn;
}