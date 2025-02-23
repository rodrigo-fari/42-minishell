/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:22:54 by aeberius          #+#    #+#             */
/*   Updated: 2025/02/23 21:28:06 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirects(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("tmp->value: %s\n", tmp->value);
		if (tmp->type == TOKEN_REDIR_OUT)
			redirect_output(tmp->next->value, 0); // 0 para sobrescrever
		else if (tmp->type == TOKEN_REDIR_IN)
			redirect_input(tmp->next->value);
		else if (tmp->type == TOKEN_REDIR_OUT_APPEND)
			redirect_output(tmp->next->value, 1); // 1 para anexar
		else if (tmp->type == TOKEN_REDIR_ERR)
			redirect_error(tmp->next->value, 0); // 0 para sobrescrever
		else if (tmp->type == TOKEN_REDIR_ERR_APPEND)
			redirect_error(tmp->next->value, 1); // 1 para anexar
		tmp = tmp->next;
	}
}
