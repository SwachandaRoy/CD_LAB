#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *input;
int i = 0;
char stack[50], handles[][7] = {")E(", "E*E", "E+E", "i", "E^E", "E-E", "E/E"};
int top = 0, l;

// Function to return the precedence level of an operator using if statements
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    if (c == 'i') return 4;
    if (c == '(' || c == ')') return 0;
    if (c == '$') return -1; // End marker
    return -1;
}

void shift() {
    stack[++top] = input[i++];
    stack[top + 1] = '\0';
}


int reduce() {
    for (int h = 0; h < 7; h++) {
        int len = strlen(handles[h]);
        
        if (top + 1 >= len && strncmp(&stack[top - len + 1], handles[h], len) == 0) {
            // Replace handle with 'E' in stack
            top = top - len + 1;
            stack[top] = 'E';
            stack[top + 1] = '\0';
            return 1; // Successful reduction
        }
    }
    return 0; // No reduction performed
}

void dispstack() {
    for (int j = 0; j <= top; j++) {
        printf("%c", stack[j]);
    }
}

void dispinput() {
    printf("%s", input + i);
}

int main() {
    input = (char *)malloc(50 * sizeof(char));
    printf("\nEnter the string\n");
    scanf("%s", input);
    strcat(input, "$");
    l = strlen(input);
    strcpy(stack, "$");

    printf("\nSTACK\tINPUT\tACTION\n");
    while (i < l) {
        shift();
        dispstack();
        printf("\t");
        dispinput();
        printf("\tShift\n");

        // Compare precedence of stack top and input
        while (precedence(stack[top]) >= precedence(input[i])) {
            if (reduce()) {
                dispstack();
                printf("\t");
                dispinput();
                printf("\tReduce\n");
            } else {
                break;
            }
        }
    }

    if (strcmp(stack, "$E$") == 0) {
        printf("\nAccepted;");
    } else {
        printf("\nNot Accepted;");
    }

    return 0;
}
