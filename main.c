/*
 * Reverse Polish (Postfix) Calculator
 * IC 2306 - Programming II | Final Group Project
 *
 * Background:
 *   In Reverse Polish Notation (RPN), operators come AFTER their operands.
 *   For example, "a + b" in infix becomes "a b +" in postfix.
 *   This calculator uses a stack to evaluate RPN expressions.
 *
 * Supported instructions:
 *   ?   - Prompt the user for a number and push it onto the stack
 *   +   - Pop two numbers, push their sum
 *   -   - Pop two numbers, push their difference (first - second)
 *   *   - Pop two numbers, push their product
 *   /   - Pop two numbers, push their quotient (first / second)
 *   =   - Print the top of the stack WITHOUT removing it
 *   q   - Quit the program
 *
 * Example:
 *   Input:  ? ? + =      (then enter 3 and 4 when prompted)
 *   Output: Result = 7
 *
 * Example from the assignment spec:
 *   "? a ? b ? c − = * ? d + ="
 *   pushes a, b, c; prints b-c; computes a*(b-c); pushes d; prints (a*(b-c))+d
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximum number of values the stack can hold at one time */
#define MAX_STACK_SIZE 100

/* -------------------------------------------------------
 * Stack: a global array used as the operand stack.
 * 'stack_top' is the index of the current top element.
 * A value of -1 means the stack is empty.
 * ------------------------------------------------------- */
double stack[MAX_STACK_SIZE];
int stack_top = -1;

/* push: add a new value onto the top of the stack */
void push(double value) {
  if (stack_top >= MAX_STACK_SIZE - 1) {
    printf("Error: stack overflow (too many operands)\n");
    exit(1);
  }
  stack[++stack_top] = value;
}

/* pop: remove and return the top value from the stack */
double pop() {
  if (stack_top < 0) {
    printf("Error: not enough operands for this operation\n");
    exit(1);
  }
  return stack[stack_top--];
}

/* peek: return the top value WITHOUT removing it (used by '=') */
double peek() {
  if (stack_top < 0) {
    printf("Error: stack is empty, nothing to display\n");
    exit(1);
  }
  return stack[stack_top];
}

/* -------------------------------------------------------
 * main: reads instructions one token at a time and
 * executes them using the stack defined above.
 * ------------------------------------------------------- */
int main(void) {
  char instruction[64]; /* holds one instruction token at a time, e.g. "?", "+",
                           "=" */

  printf("=================================\n");
  printf(" Reverse Polish Calculator\n");
  printf("=================================\n");
  printf(" ?   push a number\n");
  printf(" +   add\n");
  printf(" -   subtract\n");
  printf(" *   multiply\n");
  printf(" /   divide\n");
  printf(" =   print top of stack\n");
  printf(" q   quit\n");
  printf("=================================\n\n");

  /* keep reading instructions until the user quits */
  while (1) {
    printf("Enter instruction: ");

    /* read one whitespace-delimited token */
    if (scanf("%63s", instruction) != 1)
      break;

    if (strcmp(instruction, "q") == 0) {
      /* quit */
      printf("Goodbye!\n");
      break;

    } else if (strcmp(instruction, "?") == 0) {
      /* read a number from the user and push it */
      double number;
      printf("  Enter number: ");
      scanf("%lf", &number);
      push(number);
      printf("  Pushed %.6g\n", number);

    } else if (strcmp(instruction, "=") == 0) {
      /* print the top of the stack without removing it */
      printf("  Result = %.6g\n", peek());

    } else if (strlen(instruction) == 1 && strchr("+-*/", instruction[0])) {
      /* arithmetic: pop two operands, apply the operator, push the result */
      double second_operand =
          pop(); /* popped first, so it is the right-hand side */
      double first_operand =
          pop(); /* popped second, so it is the left-hand side */

      /* guard against division by zero */
      if (instruction[0] == '/' && second_operand == 0) {
        printf("Error: division by zero\n");
        push(first_operand); /* restore the stack to its previous state */
        continue;
      }

      double result = (instruction[0] == '+')   ? first_operand + second_operand
                      : (instruction[0] == '-') ? first_operand - second_operand
                      : (instruction[0] == '*')
                          ? first_operand * second_operand
                          : first_operand / second_operand;
      push(result);

    } else {
      /* unrecognised token — warn the user and continue */
      printf("  Unknown instruction '%s' (ignored)\n", instruction);
    }
  }

  return 0;
}
