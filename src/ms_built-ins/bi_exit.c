/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:22:57 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/21 22:28:33 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	handle_exit(t_token *tokens, t_env *env, char **commands)
{
	int		exit_code;
	t_token	*arg;

	exit_code = 0;
	arg = tokens->next;
	printf("exit\n");
	if (arg)
	{
		if (!is_numeric(arg->value))
		{
			perror("minishell: exit: %s: numeric argument required\n");
			exit_code = 255;
		}
		else if (arg->next)
		{
			perror("exit: too many arguments\n");
			exit_code = 1;
		}
		else
			exit_code = ft_atoi(arg->value) % 256;
	}
	ms_free(env, NULL, commands, tokens);
	exit(exit_code);
}

void	bi_exit(t_token *tokens, t_env *env, char **commands)
{
	handle_exit(tokens, env, commands);
}
