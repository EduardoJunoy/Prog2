
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

// evaluate the postfix expression in expr
// return OK or ERROR
// if no error, *result contains the result of evaluating the expression

Status evalPostfix(char *expr, int *result) 
{ 
  
  Stack *s = NULL; 
  int i, *arg1, *arg2, res=0, *aux;
  Status st = OK;
  
  s = stack_init();
  if (!s) return ERROR;
  
  if (!expr || !result) return ERROR;

  for (i=0; expr[i] != '\0'; i++)
  {
    if (isOperand(expr[i]))
    {
      if (isIntOperand(expr[i]))
      {
        stack_push(s, int_init(expr[i] - '0'));
      }
      else
      {
        while (!stack_isEmpty(s))
        {
          int_free(stack_pop(s));
        }
        stack_free(s);
        return ERROR;
      }
    }
    else if (isOperator(expr[i]))
    {
      if (stack_size(s) < 2)
      {
        int_free(stack_pop(s));
        stack_free(s);
        return ERROR;
      }

      arg2 = (int*)stack_pop(s);
      if (!arg2)
      {
        while (!stack_isEmpty(s))
        {
          int_free(stack_pop(s));
        }
        stack_free(s);
        return ERROR;
      }

      arg1 = (int*)stack_pop(s);
      if (!arg1)
      {
        int_free(arg2);
        while (!stack_isEmpty(s))
        {
          int_free(stack_pop(s));
        }
        stack_free(s);
        return ERROR;
      }

      res = evaluate(*arg1, *arg2, expr[i]);
      int_free(arg1);
      int_free(arg2);
      stack_push(s, int_init(res));
    }
    else
    {
      stack_free(s);
      return ERROR;
    }
  }

  aux = (int*)stack_pop(s);
  *result = *aux;

  int_free(aux);
  if (!stack_isEmpty(s))
  {
    while (!stack_isEmpty(s))
    {
      int_free(stack_pop(s));
    }
    st = ERROR;
  }

  stack_free(s);
  return st; 
}
// END CODE