#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Define states
enum State {
    START,
    IDENTIFIER,
    CONSTANT,
    REJECT
    
};

// Define input symbols
enum InputSymbol {
    LETTER,
    DIGIT,
    SIGN,
    DECIMAL_POINT,
    OTHER
};

// Transition matrix for the finite automaton
int transitions[5][4] = {
    //LETTER    , DIGIT  ,SIGN     ,DICIMAL_POINT
    {IDENTIFIER, CONSTANT, CONSTANT, REJECT},    // START
    {IDENTIFIER, IDENTIFIER, REJECT, REJECT}, 
    {REJECT, CONSTANT, REJECT, CONSTANT},    
    {REJECT, CONSTANT, REJECT, REJECT},          
    {REJECT, CONSTANT, CONSTANT, REJECT}          
};

// Function to get the input symbol category for a character
enum InputSymbol getInputSymbol(char c) {
    if (isalpha(c))
        return LETTER;
    else if (isdigit(c))
        return DIGIT;
    else if (c == '+' || c == '-')
        return SIGN;
    else if (c == '.')
        return DECIMAL_POINT;
    else
        return OTHER;
}

// Function to check if a word is a valid identifier
bool isIdentifier(const char *word) {
    enum State currentState = START;

    // Iterate through the characters of the word
    for (int i = 0; word[i] != '\0'; i++) {
        enum InputSymbol symbol = getInputSymbol(word[i]);
        currentState = transitions[currentState][symbol];
    }

    // Return true if the final state is IDENTIFIER
    return currentState == IDENTIFIER;
}

// Function to check if a word is a valid constant
bool isConstant(const char *word) {
    enum State currentState = START;

    // Iterate through the characters of the word
    for (int i = 0; word[i] != '\0'; i++) {
        enum InputSymbol symbol = getInputSymbol(word[i]);
        currentState = transitions[currentState][symbol];
    }
    // Return true if the final state is CONSTANT
    return currentState == CONSTANT;
}

int main() {
    char word[100];

    // Read input from the user
    printf("Enter a word: ");
    scanf("%s", word);

    // Check if the word is a valid identifier or constant
    if (isIdentifier(word)) {
        printf("%s is a valid identifier.\n", word);
    } else if (isConstant(word)) {
        printf("%s is a valid constant.\n", word);
    } else {
        printf("%s is not recognized as an identifier or a constant.\n", word);
    }

    return 0;
}
