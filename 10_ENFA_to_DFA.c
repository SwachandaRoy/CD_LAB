#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_TERMS 20
#define MAX_TRANSITIONS 50

// Global variables
char states[MAX_STATES], terms[MAX_TERMS];
bool is_final[MAX_STATES];
char transitions[MAX_STATES][MAX_TERMS][MAX_TRANSITIONS];
int num_states, num_terms;

// Simplified DFA table
char dfa_table[MAX_STATES][MAX_TERMS][MAX_TRANSITIONS];

// Helper to sort a string for easier matching
void sort_string(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (s[i] > s[j]) {
                char temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
}

// Simplified e-closure calculation (non-recursive)
void e_closure(int state, char *closure) {
    strcpy(closure, &states[state]);
    if (strcmp(transitions[state][num_terms], "-") != 0) {
        strcat(closure, transitions[state][num_terms]);
    }
    sort_string(closure);  // Ensure closure order consistency
}

// Transition to DFA for each state in closure
void build_dfa() {
    for (int i = 0; i < num_states; i++) {
        for (int t = 0; t < num_terms; t++) {
            char result[MAX_STATES] = {0};
            for (int j = 0; j < strlen(transitions[i][t]); j++) {
                strcat(result, transitions[transitions[i][t][j] - 'A'][t]);
            }
            sort_string(result);
            strcpy(dfa_table[i][t], result);
        }
    }
}

// Display the final DFA table
void display_dfa() {
    printf("DFA Transition Table:\n");
    printf("State\t");
    for (int i = 0; i < num_terms; i++) printf("%c\t", terms[i]);
    printf("Final?\n");

    for (int i = 0; i < num_states; i++) {
        printf("%c\t", states[i]);
        for (int j = 0; j < num_terms; j++) {
            printf("%s\t", dfa_table[i][j]);
        }
        printf("%s\n", is_final[i] ? "YES" : "NO");
    }
}

int main() {
    printf("Enter number of states and terminals: ");
    scanf("%d %d", &num_states, &num_terms);

    printf("Enter states: ");
    for (int i = 0; i < num_states; i++) scanf(" %c", &states[i]);

    printf("Enter terminals: ");
    for (int i = 0; i < num_terms; i++) scanf(" %c", &terms[i]);

    printf("Enter transition table (use '-' for no transition):\n");
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j <= num_terms; j++) {
            scanf("%s", transitions[i][j]);
        }
        is_final[i] = strcmp(transitions[i][num_terms + 1], "y") == 0;
    }

    build_dfa();
    display_dfa();
    return 0;
}
