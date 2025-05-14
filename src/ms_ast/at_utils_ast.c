/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_utils_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:55:37 by aeberius          #+#    #+#             */
/*   Updated: 2025/05/14 20:13:18 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (!is_redir(token->type))
			count++;
		else
			token = token->next;
		token = token->next;
	}
	return (count);
}

void	fill_args(t_ast_node *node, t_token **token, int count)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = *token;
	while (curr && curr->type != TOKEN_PIPE && i < count)
	{
		if (!is_redir(curr->type))
		{
			node->args[i++] = ft_strdup(curr->value);
			curr = curr->next;
		}
		else
		{
			curr = curr->next;
			if (curr)
				curr = curr->next;
		}
	}
	*token = curr;
}

void	handle_command(t_ast_node **root, t_ast_node **current, t_token **token)
{
	t_ast_node	*new_node;
	int			count;

	new_node = create_node((*token)->type);
	if (!new_node)
		return ;
	count = count_tokens(*token);
	new_node->args = ft_calloc(count + 1, sizeof(char *));
	if (!new_node->args)
		return (free(new_node), (void)0);
	fill_args(new_node, token, count);
	if (!*root)
		*root = new_node;
	else if ((*root)->type == TOKEN_PIPE && !(*root)->right)
		(*root)->right = new_node;
	else if (*current)
		(*current)->right = new_node;
	*current = new_node;
}
