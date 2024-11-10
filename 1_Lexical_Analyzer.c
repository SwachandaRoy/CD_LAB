#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *buffer) {
    char *keywords[] = {
        "break", "case", "char", "const", "continue", "default", "do", 
        "double", "else", "enum", "extern", "float", "goto", "if", "int", 
        "long", "register", "return", "while", "printf", "scanf", "void", "main"
    };
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(char ch) {
    char operators[] = "+-*/%";
    for (int i = 0; i < sizeof(operators) - 1; i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

int isRelationalOperator(char ch, char nextchar, FILE *fp) {
    if (ch == '<' && nextchar == '=') {
        fprintf(fp, "<=\t -> Relational Operator LTE\n");
        return 1;
    } else if (ch == '>' && nextchar == '=') {
        fprintf(fp, ">=\t -> Relational Operator GTE\n");
        return 1;
    } else if (ch == '=' && nextchar == '=') {
        fprintf(fp, "==\t -> Relational Operator EQ\n");
        return 1;
    } else if (ch == '<') {
        fprintf(fp, "<\t -> Relational Operator LT\n");
        return 1;
    } else if (ch == '>') {
        fprintf(fp, ">\t -> Relational Operator GT\n");
        return 1;
    }
    return 0;
}

int isAssignmentOperator(char ch, char nextchar, FILE *fp) {
    if (ch == '=' && nextchar != '=') {
        fprintf(fp, "=\t -> Assignment Operator\n");
        return 1;
    }
    return 0;
}

int isIdentifier(char *buffer) {
    return (strcmp(buffer, "a") == 0 || strcmp(buffer, "b") == 0 || strcmp(buffer, "c") == 0);
}

int main() {
    int ch, lineno = 1, i = 0;
    char buffer[50], nextchar;
    FILE *fp1, *fp2;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file.\n");
        exit(0);
    }

    while ((ch = fgetc(fp1)) != EOF) {
        if (ch == '\n') {
            lineno++;
            fprintf(fp2, "\n");
        }

        if (isOperator(ch)) {
            fprintf(fp2, "%c\t -> Arithmetic Operator\n", ch);
            continue;
        }

        if (ch == '<' || ch == '>' || ch == '=') {
            nextchar = fgetc(fp1);
            if (isRelationalOperator(ch, nextchar, fp2)) {
                continue;
            }

            if (isAssignmentOperator(ch, nextchar, fp2)) {
                continue;
            }

            ungetc(nextchar, fp1);  // Put back the character if not needed
        }

        if (isalnum(ch)) {
            buffer[i++] = (char)ch;
        } else {
            buffer[i] = '\0';  // Null-terminate the word
            i = 0;

            if (isKeyword(buffer)) {
                fprintf(fp2, "%s\t -> keyword\n", buffer);
            } else if (isIdentifier(buffer)) {
                fprintf(fp2, "%s\t -> identifier\n", buffer);
            }

            buffer[0] = '\0';  // Reset buffer
        }
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
