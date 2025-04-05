/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:19:43 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/19 15:29:00 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(char *input, t_env *env)
{ 
    char **commands;
    t_token *tokens;
    t_ast_node *ast_root;

    commands = tk_splitter(input, 0, 0);
    if (!ps_parsing(commands, 0))
    {
        ms_free(NULL, input, commands, NULL);
        return;
    }
    expand_exit(commands);
    quote_fix(commands);
    tokens = token_to_struct(commands);

    // Build the AST
    ast_root = build_ast(tokens);

    // Execute the AST
    execute_ast(ast_root, env);

    // Free the AST
    free_ast(ast_root);

    ms_free(NULL, input, commands, tokens);
    return;
}

t_ast_node *build_ast(t_token *tokens)
{
    t_ast_node *root = NULL;
    t_ast_node *current = NULL;
    t_token *token = tokens;

    while (token)
    {
        t_ast_node *new_node = ft_calloc(1, sizeof(t_ast_node));
        if (!new_node)
            return NULL;

        new_node->type = token->type;
        new_node->args = NULL;
        new_node->left = NULL;
        new_node->right = NULL;

        if (token->type == TOKEN_PIPE)
        {
            // Handle pipe: create a new pipe node and link left and right subtrees
            new_node->left = root;  // The current root becomes the left subtree
            root = new_node;       // The new pipe node becomes the new root
            token = token->next;   // Move to the next token
            continue;              // Skip the rest of the loop for this pipe node
        }
        else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || token->type == TOKEN_REDIR_OUT_APPEND || token->type == TOKEN_REDIR_ERR || token->type == TOKEN_REDIR_ERR_APPEND)
        {
            t_ast_node *redir_node = ft_calloc(1, sizeof(t_ast_node));
            if (!redir_node)
                return (NULL);
            redir_node->type = token->type;
            redir_node->left = root;
            token = token->next;
            if (token)
            {
                t_ast_node *filename_node = ft_calloc(1, sizeof(t_ast_node));
                if (!filename_node)
                    return (NULL);
                filename_node->type = TOKEN_FILENAME;
                filename_node->args = ft_calloc(1, sizeof(char *));
                if (!filename_node->args)
                {
                    free(filename_node);
                    return (NULL);
                }
                filename_node->args[0] = ft_strdup(token->value);
                filename_node->args[1] = NULL;
                redir_node->right = filename_node;
            }
            root = redir_node;
            token = token->next;
            continue;
        }
        else
        {
            int token_count = 0;
            t_token *temp = token;

            while (temp && temp->type != TOKEN_PIPE && temp->type != TOKEN_REDIR_IN &&
                temp->type != TOKEN_REDIR_OUT && temp->type != TOKEN_REDIR_OUT_APPEND &&
                temp->type != TOKEN_REDIR_ERR && temp->type != TOKEN_REDIR_ERR_APPEND)
            {
                token_count++;
                temp = temp->next;
            }

            // Allocate space for args
            new_node->args = ft_calloc(token_count + 1, sizeof(char *));
            if (!new_node->args)
            {
                free(new_node);
                return NULL;
            }
            
            // Copy all tokens for this command into args
            for (int i = 0; i < token_count; i++)
            {
                new_node->args[i] = ft_strdup(token->value);
                token = token->next;
            }
            new_node->args[token_count] = NULL;  // Null-terminate the args array

            if (!root)
            {
                // If root is NULL, this is the first node
                root = new_node;
            }
            else if (root->type == TOKEN_PIPE && !root->right)
            {
                // If the root is a pipe node, link the new node as its right child
                root->right = new_node;
            }
            else if (current)
            {
                // Otherwise, link the new node to the right of the current node
                current->right = new_node;
            }
        }

        current = new_node;
    }

    return root;
}

void execute_ast(t_ast_node *node, t_env *env)
{
    if (!node)
        return;

    if (node->type == TOKEN_PIPE)
    {
        execute_pipe(node->left, node->right, env);
    }
    else if (node->type == TOKEN_REDIR_IN || node->type == TOKEN_REDIR_OUT ||
            node->type == TOKEN_REDIR_OUT_APPEND || node->type == TOKEN_REDIR_ERR ||
            node->type == TOKEN_REDIR_ERR_APPEND)
    {
        execute_redirection(node, env);
    }
    else
    {
        if (is_builtin(node->args[0]))
            execute_builtin(node->args, env);
        else
        {
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork");
                return;
            }

            if (pid == 0)
            {
                // Child process: execute the command
                bi_exec(node->args, env);
                exit(EXIT_SUCCESS);
            }
            else
            {
                // Parent process: wait for the child to finish
                waitpid(pid, NULL, 0);
            }
        }
}
}

void execute_pipe(t_ast_node *left, t_ast_node *right, t_env *env)
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (pid1 == 0)
    {
        // Child process 1 (handles left command)
        close(pipefd[0]);  // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe's write end
        close(pipefd[1]);

        execute_ast(left, env);  // Execute the left command
        exit(EXIT_SUCCESS);
    }

    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (pid2 == 0)
    {
        // Child process 2 (handles right command)
        close(pipefd[1]);  // Close unused write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to pipe's read end
        close(pipefd[0]);

        execute_ast(right, env);  // Execute the right command
        exit(EXIT_SUCCESS);
    }

    // Parent process
    close(pipefd[0]);  // Close both ends of the pipe
    close(pipefd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void execute_redirection(t_ast_node *node, t_env *env)
{
    int fd;
    pid_t pid;
    
    // Assume the filename is the first (and only) argument for redirection
    if (!node->right || !node->right->args || !node->right->args[0])
    return;
    
    char *filename = node->right->args[0];
    
    if (!filename)
    {
        // Handle error: no filename provided for redirection
        fprintf(stderr, "Error: No filename provided for redirection\n");
        return;
    }
    
    if (node->type == TOKEN_REDIR_IN)
        fd = open(filename, O_RDONLY);
    else if (node->type == TOKEN_REDIR_OUT)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (node->type == TOKEN_REDIR_OUT_APPEND)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (node->type == TOKEN_REDIR_ERR)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (node->type == TOKEN_REDIR_ERR_APPEND)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        
    if (fd == -1)
    {
        perror("open");
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(fd);
        return;
    }

    if (pid == 0)
    {
        // Child process: handle redirection and execute the command
        if (node->type == TOKEN_REDIR_IN)
        {
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                perror("dup2");
                close(fd);
                exit(EXIT_FAILURE);
            }
        }
        else if (node->type == TOKEN_REDIR_OUT || node->type == TOKEN_REDIR_OUT_APPEND)
        {
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                close(fd);
                exit(EXIT_FAILURE);
            }
        }
        else if (node->type == TOKEN_REDIR_ERR || node->type == TOKEN_REDIR_ERR_APPEND)
        {
            if (dup2(fd, STDERR_FILENO) == -1)
            {
                perror("dup2");
                close(fd);
                exit(EXIT_FAILURE);
            }
        }

        close(fd);

        // Execute the left subtree (the command)
        if (node->left)
            execute_ast(node->left, env);

        exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent process: wait for the child to finish
        close(fd);
        waitpid(pid, NULL, 0);
    }
}

void free_ast(t_ast_node *node)
{
    if (node == NULL)
        return;

    free_ast(node->left);
    free_ast(node->right);

    if (node->args != NULL)
    {
        free_splits(node->args);
        node->args = NULL;
    }

    free(node);
}

char **collect_command_args(t_ast_node *node)
{
    int arg_count = 0;
    t_ast_node *current = node;

    // First, count the number of arguments
    while (current && current->args)
    {
        for (int i = 0; current->args[i]; i++)
            arg_count++;
        current = current->right;
    }

    // Allocate memory for the argument array
    char **args = (char **)malloc(sizeof(char *) * (arg_count + 1));  // +1 for NULL terminator
    if (!args)
        return NULL;

    // Collect the arguments
    current = node;
    int i = 0;
    while (current && current->args)
    {
        for (int j = 0; current->args[j]; j++)
        {
            args[i] = ft_strdup(current->args[j]);
            i++;
        }
        current = current->right;
    }
    args[i] = NULL;  // NULL-terminate the argument array

    return args;
}


int is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "cd") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0 ||
            ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}