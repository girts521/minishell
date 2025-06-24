#include "ast_parser.h"
#include <stdio.h>

// Helper function to convert redirection enums to strings for printing
static const char* get_redir_str(t_redirection_type type) {
    switch (type) {
        case REDIR_IN:      return "<";
        case REDIR_OUT:     return ">";
        case REDIR_APPEND:  return ">>";
        case REDIR_HEREDOC: return "<<";
        default:            return "UNKNOWN";
    }
}

/**
 * @brief Recursively prints the AST with indentation.
 * * @param node  The current node in the AST to print.
 * @param level The current depth in the tree, used for indentation.
 */
static void print_ast_recursive(t_ast *node, int level) {
    // Base case: If the node is NULL, we've reached the end of a branch.
    if (node == NULL) {
        return;
    }

    // Create indentation string
    for (int i = 0; i < level; ++i) {
        printf("    ");
    }

    // Print based on the node type
    switch (node->type) {
        case PIPE_NODE:
            printf("PIPE_NODE\n");

            // --- UPDATED SECTION ---
            // Explicitly label the Left and Right children
            for (int i = 0; i < level + 1; ++i) { printf("    "); }
            printf("-> Left Side (Executes First):\n");
            print_ast_recursive(node->left, level + 1);

            for (int i = 0; i < level + 1; ++i) { printf("    "); }
            printf("-> Right Side (Receives Pipe):\n");
            print_ast_recursive(node->right, level + 1);
            // --- END OF UPDATE ---
            break;

        case COMMAND_NODE:
            printf("COMMAND_NODE\n");
            
            t_command_node *cmd = &node->data.command_node;

            // Indent and print the command
            for (int i = 0; i < level + 1; ++i) { printf("    "); }
            printf("Command: %s\n", cmd->value ? cmd->value : "NULL");

            // Indent and print arguments
            if (cmd->argc > 0) {
                for (int i = 0; i < level + 1; ++i) { printf("    "); }
                printf("Arguments (%ld):\n", cmd->argc);
                for (long i = 0; i < cmd->argc; ++i) {
                    for (int j = 0; j < level + 2; ++j) { printf("    "); }
                    printf("[%ld]: %s\n", i, cmd->args[i]);
                }
            }

            // Indent and print redirections
            if (cmd->redirc > 0) {
                for (int i = 0; i < level + 1; ++i) { printf("    "); }
                printf("Redirections (%ld):\n", cmd->redirc);
                for (long i = 0; i < cmd->redirc; ++i) {
                    for (int j = 0; j < level + 2; ++j) { printf("    "); }
                    printf("Type: %s, Dest: %s\n", 
                           get_redir_str(cmd->redirection[i]), 
                           cmd->redir_dest[i] ? cmd->redir_dest[i] : "NULL");
                }
            }
            break;
            
        default:
             for (int i = 0; i < level; ++i) { printf("    "); }
             printf("Unknown Node Type: %d\n", node->type);
             break;
    }
}

/**
 * @brief Public-facing function to start printing the AST.
 * * @param root The root of the AST.
 */
void print_ast(t_ast *root) {
    printf("--- Abstract Syntax Tree ---\n");
    print_ast_recursive(root, 0);
    printf("----------------------------\n");
}
