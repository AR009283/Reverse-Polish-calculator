#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100   // Maximum stack size

/* Stack structure */
typedef struct {
    double data[MAX_STACK_SIZE]; // Array to store numbers
    int top;                     // Top index
} Stack;

/* Initialize stack */
void initStack(Stack *s) {
    s->top = -1;
}

/* Check if stack is empty */
int isEmpty(Stack *s) {
    return s->top == -1;
}

/* Check if stack is full */
int isFull(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

/* Push value into stack */
int push(Stack *s, double value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return 0;
    }

    s->data[++(s->top)] = value;
    return 1;
}

/* Pop value from stack */
int pop(Stack *s, double *value) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return 0;
    }

    *value = s->data[(s->top)--];
    return 1;
}

/* Show top value without removing */
int peek(Stack *s, double *value) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return 0;
    }

    *value = s->data[s->top];
    return 1;
}

/* Print stack contents */
void printStack(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");

    for (int i = 0; i <= s->top; i++) {
        printf("%.2f ", s->data[i]);
    }

    printf("\n");
}

/* Perform arithmetic operation */
int performOperation(Stack *s, char op) {
    double a, b, result;

    // Pop two numbers
    if (!pop(s, &b)) return 0;
    if (!pop(s, &a)) {
        push(s, b); // restore
        return 0;
    }

    // Calculate result
    switch (op) {
        case '+':
            result = a + b;
            break;

        case '-':
            result = a - b;
            break;

        case '*':
            result = a * b;
            break;

        case '/':
            if (b == 0) {
                printf("Cannot divide by zero!\n");
                push(s, a);
                push(s, b);
                return 0;
            }
            result = a / b;
            break;

        default:
            printf("Invalid operator!\n");
            return 0;
    }

    // Push result back
    push(s, result);

    printf("%.2f %c %.2f = %.2f\n", a, op, b, result);

    return 1;
}

/* Process instruction sequence */
void processInstructions(Stack *s, char *instructions) {

    // Split instructions by spaces
    char *token = strtok(instructions, " ");

    while (token != NULL) {

        // Read number
        if (strcmp(token, "?") == 0) {

            double value;

            printf("Enter number: ");
            scanf("%lf", &value);

            push(s, value);

            printf("Pushed %.2f\n", value);
        }

        // Print top value
        else if (strcmp(token, "=") == 0) {

            double value;

            if (peek(s, &value)) {
                printf("Result = %.2f\n", value);
            }
        }

        // Arithmetic operators
        else if (
            strcmp(token, "+") == 0 ||
            strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 ||
            strcmp(token, "/") == 0
        ) {

            performOperation(s, token[0]);
        }

        // Quit instruction
        else if (strcmp(token, "q") == 0) {
            break;
        }

        // Unknown command
        else {
            printf("Unknown instruction: %s\n", token);
        }

        // Show current stack
        printStack(s);

        // Get next token
        token = strtok(NULL, " ");
    }
}

/* Main function */
int main() {

    Stack calculator;
    char input[512];
    int running = 1;

    // Initialize stack
    initStack(&calculator);

    printf("====================================\n");
    printf(" Reverse Polish Calculator (RPN)\n");
    printf("====================================\n");

    printf("Instructions:\n");
    printf("?  -> Enter number\n");
    printf("+  -> Add\n");
    printf("-  -> Subtract\n");
    printf("*  -> Multiply\n");
    printf("/  -> Divide\n");
    printf("=  -> Show result\n");
    printf("q  -> Quit\n\n");

    while (running) {

        // Clear stack for new calculation
        initStack(&calculator);

        printf("Enter instructions: ");

        fgets(input, sizeof(input), stdin);

        // Remove newline
        input[strcspn(input, "\n")] = '\0';

        // Exit program
        if (strcmp(input, "q") == 0) {
            running = 0;
            break;
        }

        printf("\nExecuting: %s\n", input);

        processInstructions(&calculator, input);

        printf("\n");
    }

    printf("Goodbye!\n");

    return 0;
}
