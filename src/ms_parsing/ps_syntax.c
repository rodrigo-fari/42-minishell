/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:46:29 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/12 14:58:38 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parse_quotes(char *input, int i, int s_quote, int d_quote)
{
	char	quote;
	int		validation;

	validation = 0;
	while (input[++i])
	{
		while (input[i] && (input[i] != '\'' && input[i] != '\"'))
			i++;
		quote = input[i++];
		validation++;
		while (input[i] && input[i] != quote)
		{
			if (input[i] == '\"')
				d_quote++;
			if (input[i] == '\'')
				s_quote++;
			i++;
		}
		if (input[i] == quote)
			validation++;
	}
if (validation % 2 != 0 || s_quote % 2 != 0 || d_quote % 2 != 0)
	return (false);
return (true);
}

bool	parse_pipes(char **user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (user_input[i][0] == '|')
		{
			if (!user_input[i + 1] || !user_input[i - 1])
			{
				ps_error("Invalid syntax: | ", NULL);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	parse_redin(char **user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (user_input[i][0] == '<' && ft_strlen(user_input[i]) > 2)
		{
			ps_error("Invalid syntax: < << ", NULL);
			return (false);
		}
		if (ft_strcmp(user_input[i], "<") == 0 ||
		ft_strcmp(user_input[i], "<<") == 0)
		{
			if (!user_input[i + 1] || !user_input[i - 1])
			{
				ps_error("Invalid syntax: < << ", NULL);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	parse_redout(char **user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (user_input[i][0] == '>' && ft_strlen(user_input[i]) > 2)
		{
			ps_error("Invalid syntax: > >> ", NULL);
			return (false);
		}
		if (ft_strcmp(user_input[i], ">") == 0 ||
		ft_strcmp(user_input[i], ">>") == 0)
		{
			if (!user_input[i + 1] || !user_input[i - 1])
			{
				ps_error("Invalid syntax: > >> ", NULL);
				return (false);
			}
		}
		i++;
	}
	return (true);
}
