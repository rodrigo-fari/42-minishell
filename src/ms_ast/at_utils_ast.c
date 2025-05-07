/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_utils_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:55:37 by aeberius          #+#    #+#             */
/*   Updated: 2025/05/07 20:04:02 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token && !is_redir(token->type) && token->type != TOKEN_PIPE)
	{
		count++;
		token = token->next;
	}
	return (count);
}

void	fill_args(t_ast_node *node, t_token **token, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		node->args[i] = ft_strdup((*token)->value);
		*token = (*token)->next;
	}
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
