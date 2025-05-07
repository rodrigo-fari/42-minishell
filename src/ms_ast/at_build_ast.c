/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_build_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:57:47 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/07 19:58:45 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_node(t_type type)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	handle_pipe(t_ast_node **root, t_ast_node *new_node, t_token **token)
{
	new_node->left = *root;
	*root = new_node;
	*token = (*token)->next;
}

void	handle_heredoc(t_ast_node **root, t_token **token)
{
	t_ast_node	*heredoc_node;

	heredoc_node = create_node(TOKEN_HEREDOC);
	if (!heredoc_node)
		return ;
	heredoc_node->args = ft_calloc(2, sizeof(char *));
	if (heredoc_node->args)
		heredoc_node->args[0] = ft_strdup((*token)->next->value);
	*root = heredoc_node;
	*token = (*token)->next->next;
}

void	handle_redir(t_ast_node **root, t_token **token)
{
	t_ast_node	*redir_node;
	t_ast_node	*filename_node;

	redir_node = create_node((*token)->type);
	if (!redir_node)
		return ;
	redir_node->left = *root;
	*token = (*token)->next;
	if (*token)
	{
		filename_node = create_node(TOKEN_FILENAME);
		if (!filename_node)
			return ;
		filename_node->args = ft_calloc(2, sizeof(char *));
		if (filename_node->args)
			filename_node->args[0] = ft_strdup((*token)->value);
		redir_node->right = filename_node;
	}
	*root = redir_node;
	*token = (*token)->next;
}

t_ast_node	*build_ast(t_token *tokens)
{
	t_ast_node	*root;
	t_ast_node	*current;
	t_token		*token;

	root = NULL;
	current = NULL;
	token = tokens;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			handle_pipe(&root, create_node(token->type), &token);
		else if (is_redir(token->type))
			handle_redir(&root, &token);
		else if (token->type == TOKEN_HEREDOC)
			handle_heredoc(&root, &token);
		else
			handle_command(&root, &current, &token);
	}
	return (root);
}
