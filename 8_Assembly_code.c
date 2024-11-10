#include <stdio.h>
#include <string.h>

// Simplified register mapping function
const char* mapRegister(char var[]) {
    if (strcmp(var, "T1") == 0) return "CH";
    if (strcmp(var, "T2") == 0) return "CL";
    if (strcmp(var, "T3") == 0) return "DH";
    if (strcmp(var, "T4") == 0) return "DL";
    return var;  // For non-temporary variables, return original
}

// Function to generate the assembly code for arithmetic operation
void generateAssembly(char op, char fir[], char sec[], char res[], FILE* fp2) {
    const char* reg1 = mapRegister(fir); // Map first operand
    const char* reg2 = mapRegister(sec); // Map second operand
    const char* resReg = mapRegister(res); // Map result

    // Load first operand into AX if not already in a register
    if (strcmp(reg1, "AX") != 0) {
        fprintf(fp2, "MOV AX, [%s]\n", reg1);
    }
    // Load second operand into BX if not already in a register
    if (strcmp(reg2, "BX") != 0) {
        fprintf(fp2, "MOV BX, [%s]\n", reg2);
    }

    // Write the operation code
    switch (op) {
        case '+':
            fprintf(fp2, "ADD AX, BX\n");
            break;
        case '-':
            fprintf(fp2, "SUB AX, BX\n");
            break;
        case '*':
            fprintf(fp2, "MUL BX\n");  // MUL implicitly multiplies with AX
            break;
        case '/':
            fprintf(fp2, "DIV BX\n");  // DIV implicitly divides AX by BX
            break;
    }

    // Move the result back to the result variable
    if (strcmp(resReg, "AX") != 0) {
        fprintf(fp2, "MOV [%s], AX\n", resReg);
    }
}

int main() {
    FILE *fp1 = fopen("input.txt", "r");
    FILE *fp2 = fopen("result.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error: Could not open input or output file.\n");
        return 1;
    }

    char op, fir[10], sec[10], res[10];

    // Process each line in input file
    while (fscanf(fp1, " %c %s %s %s", &op, fir, sec, res) == 4) {
        printf("%c %s %s %s\n", op, fir, sec, res);
        generateAssembly(op, fir, sec, res, fp2); // Call function to generate assembly
    }

    // Close files
    fclose(fp1);
    fclose(fp2);
    return 0;
}
