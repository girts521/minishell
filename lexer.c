#include "minishell.h"

// Helper function to create a new token
// This function allocates memory for the token and its value.
// Remember to free this memory later.
t_token *create_token(t_token_type type, const char *value_str) {
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token) {
        perror("Failed to allocate token");
        // In a real minishell, you'd handle this more gracefully
        exit(EXIT_FAILURE);
    }

    new_token->type = type;
    if (value_str) {
        new_token->value = strdup(value_str); // strdup allocates memory for the string copy
        if (!new_token->value) {
            perror("Failed to allocate token value");
            free(new_token);
            exit(EXIT_FAILURE);
        }
    } else {
        new_token->value = NULL;
    }
    new_token->next = NULL;
    return new_token;
}

// --- Mock Lexer Output Functions ---

// Test Input 1: ls -l /tmp
// Expected Token Sequence:
// 1. TOKEN_WORD, value: "ls"
// 2. TOKEN_WORD, value: "-l"
// 3. TOKEN_WORD, value: "/tmp"
// 4. TOKEN_EOF,   value: NULL
t_token *get_test_input_1_tokens() {
    t_token *head = create_token(TOKEN_WORD, "ls");
    head->next = create_token(TOKEN_WORD, "-l");
    head->next->next = create_token(TOKEN_WORD, "/tmp");
    head->next->next->next = create_token(TOKEN_EOF, NULL); // End of the command
    return head;
}

// Test Input 2: echo "Hello $USER" 'no expansion here'
// Expected Token Sequence:
// 1. TOKEN_WORD,   value: "echo"
// 2. TOKEN_STRING, value: "\"Hello $USER\"" (raw value, includes quotes)
// 3. TOKEN_SQUOTE, value: "'no expansion here'" (raw value, includes quotes)
// 4. TOKEN_EOF,    value: NULL
t_token *get_test_input_2_tokens() {
    t_token *head = create_token(TOKEN_WORD, "echo");
    head->next = create_token(TOKEN_STRING, "\"Hello $USER\"");
    head->next->next = create_token(TOKEN_SQUOTE, "'no expansion here'");
    head->next->next->next = create_token(TOKEN_EOF, NULL); // End of the command
    return head;
}

// --- Utility Functions (for testing and cleanup) ---

// Function to print the token list (for verification)
void print_token_list(t_token *token_list) {
    t_token *current = token_list;
    printf("Generated Token List:\n");
    int i = 0;
    while (current != NULL) {
        printf("  Token %d: Type = %d, Value = \"%s\"\n",
               i, current->type, (current->value ? current->value : "NULL"));
        if (current->type == TOKEN_EOF) { // Stop after EOF for clarity
            break;
        }
        current = current->next;
        i++;
    }
    printf("------------------------\n");
}

// Function to free the token list
// Crucial to prevent memory leaks [cite: 14]
void free_token_list(t_token *token_list) {
    t_token *current = token_list;
    t_token *next_token;
    while (current != NULL) {
        next_token = current->next;
        free(current->value); // Free the duplicated string
        free(current);        // Free the token structure itself
        current = next_token;
    }
}

/*
// --- Example Usage (Uncomment to test) ---
int main() {
    printf("Generating Test Input 1 (ls -l /tmp):\n");
    t_token *tokens1 = get_test_input_1_tokens();
    print_token_list(tokens1);
    // Your AST parser would take tokens1 here
    free_token_list(tokens1); // Clean up

    printf("\nGenerating Test Input 2 (echo \"Hello $USER\" 'no expansion here'):\n");
    t_token *tokens2 = get_test_input_2_tokens();
    print_token_list(tokens2);
    // Your AST parser would take tokens2 here
    free_token_list(tokens2); // Clean up

    return 0;
}
*/
