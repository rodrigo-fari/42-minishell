/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:47:50 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/07 23:13:53 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_env		*env;
	char		*input;

	(void)av;
	if (ac > 1)
		return (1);
	env = env_to_struct(envp);
	env = env_manager(env);
	while (true)
	{
		env = env_manager(NULL);
		signal(SIGINT, sig_ctrl_c);
		signal(SIGPIPE, SIG_IGN);
		input = readline("43$ ");
		if (!input)
			break ;
		add_history(input);
		env = env_manager(NULL);
		ms_exec(input, env);
	}
	return (0);
}
