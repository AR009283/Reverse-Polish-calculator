#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100

typedef struct {
    double data[MAX_STACK];
    int top;
} Stack;

/* --- MANDATORY STACK FUNCTIONS --- */

void stack_init(Stack *s) {
    s->top = -1;
}

int stack_empty(const Stack *s) {
    return s->top == -1;
}

int stack_full(const Stack *s) {
    return s->top == MAX_STACK - 1;
}

void stack_push(Stack *s, double value) {
    if (stack_full(s)) {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->data[++(s->top)] = value;
}

double stack_pop(Stack *s) {
    if (stack_empty(s)) {
        return 0;
    }
    return s->data[(s->top)--];
}

double stack_peek(const Stack *s) {
    if (stack_empty(s)) {
        return 0;
    }
    return s->data[s->top];
}

int is_number(const char *s) {
    if (!s || *s == '\0') return 0;
    char *p;
    strtod(s, &p);
    return *p == '\0';
}

/* --- HELPER FUNCTIONS --- */

void printStack(Stack *s) {
    if (stack_empty(s)) {
        return;
    }
    printf("Stack: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%.2f ", s->data[i]);
    }
    printf("\n");
}

void performOperation(Stack *s, char op) {
    double a, b, result;

    if (s->top < 1) {
        printf("Error: Insufficient operands on stack.\n\n");
        return;
    }

    b = stack_pop(s);
    a = stack_pop(s);

    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero\n\n");
                stack_push(s, a);
                stack_push(s, b);
                return;
            }
            result = a / b;
            break;
        default: return;
    }

    stack_push(s, result);
    /* Removed the explicit calculation line (a op b = result) per user request */
    printStack(s);
    printf("\n");
}

/* --- MAIN FUNCTION --- */

int main(void) {
    Stack calculator;
    stack_init(&calculator);
    char instr[10];
    double val;

    printf("====================================\n");
    printf(" Reverse Polish Calculator (RPN)\n");
    printf("====================================\n");
    printf("Instructions:\n");
    printf("?  -> Enter number\n");
    printf("+  -> Add\n");
    printf("-  -> Subtract\n");
    printf("* -> Multiply\n");
    printf("/  -> Divide\n");
    printf("=  -> Show result\n");
    printf("q  -> Quit\n\n");

    while (1) {
        printf("Enter Instruction: ");
        if (scanf("%s", instr) != 1) break;

        if (strcmp(instr, "q") == 0) break;

        if (strcmp(instr, "?") == 0) {
            printf("Enter Number: ");
            if (scanf("%lf", &val) == 1) {
                stack_push(&calculator, val);
                printf("Pushed %.2f\n", val);
                printStack(&calculator);
            }
            printf("\n");
        }
        else if (strcmp(instr, "=") == 0) {
            if (!stack_empty(&calculator)) {
                printf("Result = %.2f\n", stack_peek(&calculator));
                printStack(&calculator);
            } else {
                printf("Error: Stack is empty\n");
            }
            printf("\n");
        }
        else if (strlen(instr) == 1 && strchr("+-*/", instr[0])) {
            performOperation(&calculator, instr[0]);
        }
        else {
            printf("Error: Unknown instruction\n\n");
        }
    }

    printf("Goodbye!\n");
    return 0;
}

