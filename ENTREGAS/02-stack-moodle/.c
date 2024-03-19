
#include "expressions.h"
#include "stack.h"
#include "types.h"
#include <ctype.h> // for isdigit()
#include <stdio.h>
#include <stdlib.h>

#define OPERATORS "+-*/%"

// is char c an operator?
Bool isOperator(char c)
{
  char *oper = OPERATORS;
  char *pc;

  // exclude the char '\0' as operator
  if (c == '\0')
    return FALSE;

  // search for c in operators
  pc = strchr(oper, c);

  if (!pc)
    return FALSE;
  return TRUE;
}

// is char c an operand?
// accepts anything that is not an operator
Bool isOperand(char c)
{
  Bool b;
  b = (isOperator(c) == TRUE) ? FALSE : TRUE;
  return b;
}

// is char c a digit
Bool isIntOperand(char c) { return isdigit(c) ? TRUE : FALSE; }

// evaluate expresion with operator oper
int evaluate(int arg1, int arg2, char oper)
{
  int p = 0;

  switch (oper)
  {
  case '+':
    p = arg1 + arg2;
    break;
  case '-':
    p = arg1 - arg2;
    break;
  case '*':
    p = arg1 * arg2;
    break;
  case '/':
    p = arg1 / arg2;
    break;
  default:
    printf("Invalid operator");
  }

  return p;
}
/******************************************/

// START YOUR CODE

// return TRUE if string str has well-balanced parenthesis

Bool balancedParens(char *str)
{
  int i, len;
  Status st = OK;
  Stack *s;

  if (!str)
    return FALSE;

  s = stack_init();
  if (!s)
    st = ERROR;

  len = strlen(str);

  for (i = 0; i < len && st == OK; i++)
  {
    if (str[i] == '(')
    {
      st = stack_push(s, str + i);
    }
    else if (str[i] == ')')
    {
      if (stack_isEmpty(s))
      {
        st = FALSE;
      }
      else
      {
        stack_pop(s);
      }
    }
  }
  if (stack_isEmpty(s) == FALSE)
    return FALSE;
  stack_free(s);
  
  return st;
}

Status evalPostfix(char *expr, int *result) 
{ 
  
  Stack *s = stack_init();
  if (!s) return ERROR;
  
  int i, arg1, arg2, operand, res;

  if (!expr || !result) return ERROR;

  for (i=0; expr[i] != '\0'; i++)
  {
    if (isIntOperand(expr[i]))
    {
      operand = *(int *)int_init(expr[i] - '0');
      stack_push(s, &operand);
    }
    else if (isOperator(expr[i]))
    {
      if (stack_size(s) < 2)
      {
        stack_free(s);
        return ERROR;
      }
      arg2 = *(int *)stack_pop(s);
      arg1 = *(int *)stack_pop(s);
      res = evaluate(arg1, arg2, expr[i]);
      stack_push(s, &res);
    }
    else
    {
      stack_free(s);
      return ERROR;
    }
  }

  *result = *(int*)stack_pop(s);

  if (!stack_isEmpty(s))
  {
    stack_free(s);
    return ERROR;
  }

  stack_free(s);
  return OK; 
}