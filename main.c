#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

/* Stack structure to store numerical operands */
typedef struct {
    double data[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int push(Stack *s, double value) {
    if (s->top >= MAX_STACK_SIZE - 1) {
        printf("Error: Stack overflow\n");
        return 0;
    }
    s->data[++(s->top)] = value;
    return 1;
}

int pop(Stack *s, double *result) {
    if (s->top < 0) {
        printf("Error: Stack underflow\n");
        return 0;
    }
    *result = s->data[(s->top)--];
    return 1;
}

int main() {
    Stack s;
    initStack(&s);
    char instr[10];
    double val, op1, op2;

    printf("Reverse Polish Calculator - IC 2306\n");
    printf("Commands: ?, +, -, *, /, =, q\n\n");

    while (1) {
        printf("Enter Instruction: ");
        if (scanf("%s", instr) != 1) break;

        /* Exit condition */
        if (strcmp(instr, "q") == 0) break;

        /* Read Number Instruction */
        if (strcmp(instr, "?") == 0) {
            printf("Enter Number: ");
            if (scanf("%lf", &val) == 1) {
                push(&s, val);
            }
            printf("\n");
        }
        /* Print Result Instruction */
        else if (strcmp(instr, "=") == 0) {
            if (s.top > -1) {
                printf("Final Result = %.2f\n\n", s.data[s.top]);
            } else {
                printf("Error: Stack is empty\n\n");
            }
        }
        /* Arithmetic Operations */
        else if (strlen(instr) == 1 && strchr("+-*/", instr[0])) {
            if (s.top < 1) {
                printf("Error: Not enough operands\n\n");
            } else {
                pop(&s, &op2);
                pop(&s, &op1);

                if (instr[0] == '+') push(&s, op1 + op2);
                else if (instr[0] == '-') push(&s, op1 - op2);
                else if (instr[0] == '*') push(&s, op1 * op2);
                else if (instr[0] == '/') {
                    if (op2 == 0) {
                        printf("Error: Division by zero\n");
                        push(&s, op1); /* Restore stack */
                        push(&s, op2);
                    } else {
                        push(&s, op1 / op2);
                    }
                }
                printf("\n");
            }
        } else {
            printf("Error: Invalid instruction\n\n");
        }
    }

    return 0;
}
