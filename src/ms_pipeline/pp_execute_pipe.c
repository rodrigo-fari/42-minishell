/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:02:42 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/08 00:06:50 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_child1(int *pipefd, t_ast_node *left, t_env *env) 
{
    close(pipefd[0]);  // Close read end
    dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
    close(pipefd[1]);  // Close original write end
    
    // Execute left command
    left->in_pipe = true;
    execute_ast(left, env);
    
    exit(g_exit_status);  // This closes all FDs
}

void pipe_child2(int *pipefd, t_ast_node *right, t_env *env)
{
    // Close pipe completely before any redirections
    close(pipefd[0]);
    close(pipefd[1]);

    // Mark as in pipe to prevent double-forking
    right->in_pipe = true;
    
    // Execute with clean slate (pipe FDs closed)
    execute_ast(right, env);
    exit(g_exit_status);
}

void execute_pipe(t_ast_node *left, t_ast_node *right, t_env *env)
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("minishell");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        pipe_child1(pipefd, left, env);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        pipe_child2(pipefd, right, env);
    }

    // Parent closes both ends and waits
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

bool has_input_redirection(t_ast_node *node)
{
    if (!node) return false;
    if (node->type == TOKEN_REDIR_IN || node->type == TOKEN_HEREDOC) 
        return true;
    return has_input_redirection(node->left) || has_input_redirection(node->right);
}
