/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:13:25 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/14 22:23:29 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exit(t_token *token)
{
	ft_putendl_fd("exit", 1);
	if (tk_listsize(token) == 1)
		define_exit_status(NULL);
	else if (!check_exit_arguments(token))
		define_exit_status(NULL);
	else if (!check_exit_signals(token))
		define_exit_status(NULL);
	else
		define_exit_status(token->next->value);
}

void	define_exit_status(char *exit_status)
{
	long		exit_lnumber;

	if (!exit_status)
	{
		cleanup_shell(get_shell());
		exit(g_exit_status);
	}
	if (ft_atol(exit_status) != ft_atod(exit_status))
	{
		g_exit_status = 2;
		cleanup_shell(get_shell());
		exit (g_exit_status);
	}
	exit_lnumber = ft_atol(exit_status);
	if (exit_lnumber > 256 || exit_lnumber < 0)
		exit_lnumber %= 256;
	g_exit_status = exit_lnumber;
	cleanup_shell(get_shell());
	exit (g_exit_status);
}

bool	check_exit_arguments(t_token *token)
{
	if (tk_listsize(token) > 2)
	{
		bi_error("Minishell: exit: too many arguments\n");
		g_exit_status = 1;
		return (false);
	}
	if (tk_listsize(token) == 2 && ft_strcmp(token->next->value, "--") == 0)
	{
		g_exit_status = 2;
		return (false);
	}
	return (true);
}

bool	check_exit_signals(t_token *token)
{
	int		i;
	int		qnt;

	i = 0;
	qnt = 0;
	while (token->next->value[i])
	{
		while (token->next->value[i] && (!ft_isdigit(token->next->value[i])))
		{
			qnt++;
			i++;
		}
		if (!check_signal_quantity(qnt))
			return (false);
		while (token->next->value[i] && (ft_isdigit(token->next->value[i])))
			i++;
		if (token->next->value[i])
		{
			bi_error("Minishell: exit: numeric argument required\n");
			g_exit_status = 2;
			return (false);
		}
	}
	return (true);
}

bool	check_signal_quantity(int qnt)
{
	if (qnt > 1)
	{
		bi_error("Minishell: exit: Invalid argument\n");
		g_exit_status = 2;
		return (false);
	}
	return (true);
}
