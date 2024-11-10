#include <stdio.h>
#include <ctype.h>
#include <string.h>

char productions[10][10];
char first[10][10];
int production_count;

void addToSet(char set[], char c) {
    int i;
    for (i = 0; set[i] != '\0'; i++)
        if (set[i] == c) return;  // Avoid duplicates
    set[i] = c;
    set[i+1] = '\0';
}

void calculateFirst(char symbol, char result[]) {
    // If the symbol is a terminal, add it directly
    if (!isupper(symbol)) {
        addToSet(result, symbol);
        return;
    }

    // Process productions for non-terminal symbol
    for (int i = 0; i < production_count; i++) {
        if (productions[i][0] == symbol) {
            int j = 2;
            while (productions[i][j] != '\0') {
                char nextSymbol = productions[i][j];
                calculateFirst(nextSymbol, result);
                
                // If ε is not in FIRST(nextSymbol), stop
                if (strchr(first[nextSymbol - 'A'], '#') == NULL) break;
                
                j++;
            }
            if (productions[i][j] == '\0') {
                addToSet(result, '#'); // Add ε if end of production
            }
        }
    }
}

void findAllFirstSets() {
    for (int i = 0; i < production_count; i++) {
        char symbol = productions[i][0];
        calculateFirst(symbol, first[symbol - 'A']);
    }
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &production_count);

    printf("Enter the productions (e.g., E->E+T):\n");
    for (int i = 0; i < production_count; i++) {
        scanf("%s", productions[i]);
    }

    // Initialize FIRST sets
    for (int i = 0; i < 10; i++) {
        first[i][0] = '\0';
    }

    findAllFirstSets();

    // Print FIRST sets
    for (int i = 0; i < production_count; i++) {
        char symbol = productions[i][0];
        printf("FIRST(%c) = { ", symbol);
        for (int j = 0; first[symbol - 'A'][j] != '\0'; j++) {
            printf("%c ", first[symbol - 'A'][j]);
        }
        printf("}\n");
    }

    return 0;
}
