#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "stack.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Bool balancedParens(char *str);
Status evalPostfix(char *str, int *result);
// return TRUE if string str has well-balanced parenthesis
Bool balancedParens(char *str);
// evaluate the postfix expression in expr
// return OK or ERROR
// if no error, *result contains the result of evaluating the expression in expr
Status evalPostfix(char *expr, int *result);
#endif