#include<stdio.h>
#define MAX_STATES 100
#define MAX_SYMBOLS 100

typedef struct {
    int transition[MAX_STATES][MAX_SYMBOLS][MAX_STATES];  // Transition matrix
    int epsilon[MAX_STATES][MAX_STATES];                  // Epsilon transition matrix
    int numStates;                                        // Total number of states
    int numSymbols;                                       // Number of symbols
} NFA;

// Adds a standard transition in the NFA
void addTransition(NFA *nfa, int from, int to, int symbol) {
    nfa->transition[from][symbol][to] = 1;  // Set transition from 'from' to 'to' on 'symbol'
}

// Adds an epsilon (ε) transition in the NFA
void addEpsilonTransition(NFA *nfa, int from, int to) {
    nfa->epsilon[from][to] = 1;  // Set epsilon transition from 'from' to 'to'
}

// Finds the epsilon closure of a state recursively
void epsilonClosure(NFA *nfa, int state, int *closure, int *closureSize) {
    closure[*closureSize] = state;  // Add state to closure
    (*closureSize)++;

    // Explore epsilon transitions from the current state
    for (int i = 0; i < nfa->numStates; i++) {
        if (nfa->epsilon[state][i]) {  // Check if there's an epsilon transition to state 'i'
            int alreadyInClosure = 0;  // Flag to check if 'i' is already in closure

            for (int j = 0; j < *closureSize; j++) {  // Loop to check if 'i' is already in closure
                if (closure[j] == i) {
                    alreadyInClosure = 1;  // Mark if already in closure
                    break;
                }
            }

            if (!alreadyInClosure) {  // If not in closure, recursively add epsilon closure of 'i'
                epsilonClosure(nfa, i, closure, closureSize);
            }
        }
    }
}

int main() {
    NFA nfa;
    int epsilonClosureResult[MAX_STATES];

    printf("Enter the number of states: ");
    scanf("%d", &nfa.numStates);

    printf("Enter the number of input symbols: ");
    scanf("%d", &nfa.numSymbols);

    // Initialize transition and epsilon matrices to 0
    for (int i = 0; i < nfa.numStates; i++) {
        for (int j = 0; j < nfa.numSymbols; j++) {
            for (int k = 0; k < nfa.numStates; k++) {
                nfa.transition[i][j][k] = 0;
            }
        }
        for (int k = 0; k < nfa.numStates; k++) {
            nfa.epsilon[i][k] = 0;
        }
    }

    // Input transitions for each state
    for (int i = 0; i < nfa.numStates; i++) {
        printf("\nEnter the transitions for state %d\n", i);
        for (int j = 0; j < nfa.numSymbols; j++) {
            printf("\t for symbol %c: ", j == nfa.numSymbols - 1 ? 35 : j + 97);
            int toState;
            while (1) {
                scanf("%d", &toState);
                if (toState == -1) break;  // Stop input when -1 is entered

                if (j == nfa.numSymbols - 1)  // Last symbol indicates epsilon transition
                    addEpsilonTransition(&nfa, i, toState);
                else
                    addTransition(&nfa, i, toState, j);
            }
        }
    }

    // Calculate and display epsilon closure for each state
    for (int i = 0; i < nfa.numStates; i++) {
        int closure[MAX_STATES];
        int closureSize = 0;

        epsilonClosure(&nfa, i, closure, &closureSize);  // Compute epsilon closure for state 'i'

        printf("Epsilon closure of state %d: { ", i);
        for (int j = 0; j < closureSize; j++) {
            printf("%d ", closure[j]);
        }
        printf("}\n");
    }

    return 0;
}
