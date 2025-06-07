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
    head->next->next->next = create_token(TOKEN_REDIRECT_OUT, ">");
    head->next->next->next->next = create_token(TOKEN_WORD, "test.txt");
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

// --- Mock Lexer Output Functions ---

// ... (your existing create_token, get_test_input_1_tokens, etc., functions go here) ...

// Test Input 3: cat file.txt | grep "search"
// Purpose: Tests a simple pipeline with the | operator.
// Expected Token Sequence:
// 1. TOKEN_WORD,   value: "cat"
// 2. TOKEN_WORD,   value: "file.txt"
// 3. TOKEN_PIPE,   value: "|" (or NULL if your lexer doesn't store values for operators)
// 4. TOKEN_WORD,   value: "grep"
// 5. TOKEN_STRING, value: "\"search\""
// 6. TOKEN_EOF,    value: NULL
t_token *get_test_input_3_tokens() {
    t_token *head = create_token(TOKEN_WORD, "cat");
    head->next = create_token(TOKEN_WORD, "file.txt");
    head->next->next = create_token(TOKEN_PIPE, "|");
    head->next->next->next = create_token(TOKEN_WORD, "grep");
    head->next->next->next->next = create_token(TOKEN_STRING, "\"search\"");
    head->next->next->next->next->next = create_token(TOKEN_EOF, NULL);
    return head;
}

// Test Input 4: grep "error" < log.txt >> errors.log
// Purpose: Tests multiple redirections (input and append-output) on a single command.
// Expected Token Sequence:
// 1. TOKEN_WORD,         value: "grep"
// 2. TOKEN_STRING,       value: "\"error\""
// 3. TOKEN_REDIRECT_IN,  value: "<"
// 4. TOKEN_WORD,         value: "log.txt"
// 5. TOKEN_APPEND,       value: ">>"
// 6. TOKEN_WORD,         value: "errors.log"
// 7. TOKEN_EOF,          value: NULL
t_token *get_test_input_4_tokens() {
    t_token *head = create_token(TOKEN_WORD, "grep");
    head->next = create_token(TOKEN_STRING, "\"error\"");
    head->next->next = create_token(TOKEN_REDIRECT_IN, "<");
    head->next->next->next = create_token(TOKEN_WORD, "log.txt");
    head->next->next->next->next = create_token(TOKEN_APPEND, ">>");
    head->next->next->next->next->next = create_token(TOKEN_WORD, "errors.log");
    head->next->next->next->next->next->next = create_token(TOKEN_EOF, NULL);
    return head;
}

// Test Input 5: wc -l <<< END
// Purpose: Tests the here-document redirection as specified in the subject. 
// Note: Your subject uses '<<<', while the `e_token_type` enum has TOKEN_HEREDOC,
// which is commonly associated with '<<'. Ensure your lexer correctly maps '<<<'
// to TOKEN_HEREDOC to match the project requirements.
// Expected Token Sequence:
// 1. TOKEN_WORD,    value: "wc"
// 2. TOKEN_WORD,    value: "-l"
// 3. TOKEN_HEREDOC, value: "<<<"
// 4. TOKEN_WORD,    value: "END" (the delimiter)
// 5. TOKEN_EOF,     value: NULL
t_token *get_test_input_5_tokens() {
    t_token *head = create_token(TOKEN_WORD, "wc");
    head->next = create_token(TOKEN_WORD, "-l");
    head->next->next = create_token(TOKEN_HEREDOC, "<<<");
    head->next->next->next = create_token(TOKEN_WORD, "END");
    head->next->next->next->next = create_token(TOKEN_EOF, NULL);
    return head;
}

// Test Input 6: cat < infile | grep "test" > outfile
// Purpose: Tests a more complex chain involving both input/output redirection and a pipe.
// This checks if your parser correctly associates redirections with the right commands in a pipeline.
// Expected Token Sequence:
// 1. TOKEN_WORD,         value: "cat"
// 2. TOKEN_REDIRECT_IN,  value: "<"
// 3. TOKEN_WORD,         value: "infile"
// 4. TOKEN_PIPE,         value: "|"
// 5. TOKEN_WORD,         value: "grep"
// 6. TOKEN_STRING,       value: "\"test\""
// 7. TOKEN_REDIRECT_OUT, value: ">"
// 8. TOKEN_WORD,         value: "outfile"
// 9. TOKEN_EOF,          value: NULL
t_token *get_test_input_6_tokens() {
    t_token *head = create_token(TOKEN_WORD, "cat");
    head->next = create_token(TOKEN_REDIRECT_IN, "<");
    head->next->next = create_token(TOKEN_WORD, "infile");
    head->next->next->next = create_token(TOKEN_PIPE, "|");
    head->next->next->next->next = create_token(TOKEN_WORD, "grep");
    head->next->next->next->next->next = create_token(TOKEN_STRING, "\"test\"");
    head->next->next->next->next->next->next = create_token(TOKEN_REDIRECT_OUT, ">");
    head->next->next->next->next->next->next->next = create_token(TOKEN_WORD, "outfile");
    head->next->next->next->next->next->next->next->next = create_token(TOKEN_EOF, NULL);
    return head;
}

// Test Input 7: echo "Status was: $?"
// Purpose: Tests variable expansion within double quotes, specifically the exit status variable '$?'. 
// Your parser will need to know not to expand this, but the executor will.
// For the lexer, it's just a string.
// Expected Token Sequence:
// 1. TOKEN_WORD,   value: "echo"
// 2. TOKEN_STRING, value: "\"Status was: $?\""
// 3. TOKEN_EOF,    value: NULL
t_token *get_test_input_7_tokens() {
    t_token *head = create_token(TOKEN_WORD, "echo");
    head->next = create_token(TOKEN_STRING, "\"Status was: $?\"");
    head->next->next = create_token(TOKEN_EOF, NULL);
    return head;
}

// --- New, More Complex Test Cases ---

/**
 * @brief Test Input 8: < infile grep "test" | wc -l > outfile
 * @purpose Tests redirections on both the first and last commands of a pipeline.
 * It ensures that '< infile' is associated with 'grep' and '> outfile' with 'wc'.
 * Note: Placing input redirection before the command is valid in bash.
 */
t_token *get_test_input_8_tokens() {
    t_token *head = create_token(TOKEN_REDIRECT_IN, "<");
    head->next = create_token(TOKEN_WORD, "infile");
    head->next->next = create_token(TOKEN_WORD, "grep");
    head->next->next->next = create_token(TOKEN_STRING, "\"test\"");
    head->next->next->next->next = create_token(TOKEN_PIPE, "|");
    head->next->next->next->next->next = create_token(TOKEN_WORD, "wc");
    head->next->next->next->next->next->next = create_token(TOKEN_WORD, "-l");
    head->next->next->next->next->next->next->next = create_token(TOKEN_REDIRECT_OUT, ">");
    head->next->next->next->next->next->next->next->next = create_token(TOKEN_WORD, "outfile");
    head->next->next->next->next->next->next->next->next->next = create_token(TOKEN_EOF, NULL);
    return head;
}

/**
 * @brief Test Input 9: ls -l | grep ".c" | sort -r | cat -e
 * @purpose Tests a longer pipeline with multiple pipes to ensure the
 * AST is built correctly as a linked series of pipe nodes.
 */
t_token *get_test_input_9_tokens() {
    t_token *head = create_token(TOKEN_WORD, "ls");
    head->next = create_token(TOKEN_WORD, "-l");
    head->next->next = create_token(TOKEN_PIPE, "|");
    head->next->next->next = create_token(TOKEN_WORD, "grep");
    head->next->next->next->next = create_token(TOKEN_STRING, "\".c\"");
    head->next->next->next->next->next = create_token(TOKEN_PIPE, "|");
    head->next->next->next->next->next->next = create_token(TOKEN_WORD, "sort");
    head->next->next->next->next->next->next->next = create_token(TOKEN_WORD, "-r");
    head->next->next->next->next->next->next->next->next = create_token(TOKEN_PIPE, "|");
    head->next->next->next->next->next->next->next->next->next = create_token(TOKEN_WORD, "cat");
    head->next->next->next->next->next->next->next->next->next->next = create_token(TOKEN_WORD, "-e");
    head->next->next->next->next->next->next->next->next->next->next->next = create_token(TOKEN_EOF, NULL);
    return head;
}

/**
 * @brief Test Input 10: cat << END | grep "keyword" >> log.txt
 * @purpose Tests a pipeline that starts with a heredoc and ends with an append redirection.
 */
t_token *get_test_input_10_tokens() {
    t_token *head = create_token(TOKEN_WORD, "cat");
    head->next = create_token(TOKEN_HEREDOC, "<<");
    head->next->next = create_token(TOKEN_WORD, "END");
    head->next->next->next = create_token(TOKEN_PIPE, "|");
    head->next->next->next->next = create_token(TOKEN_WORD, "grep");
    head->next->next->next->next->next = create_token(TOKEN_STRING, "\"keyword\"");
    head->next->next->next->next->next->next = create_token(TOKEN_APPEND, ">>");
    head->next->next->next->next->next->next->next = create_token(TOKEN_WORD, "log.txt");
    head->next->next->next->next->next->next->next->next = create_token(TOKEN_EOF, NULL);
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
