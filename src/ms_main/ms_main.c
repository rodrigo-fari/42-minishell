/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:47:50 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/14 21:13:27 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(void)
{
	t_env		*env;
	char		*input;
	extern char	**environ;

	env = env_to_struct(environ);
	env = get_env(env);
	while (true)
	{
		env = get_env(NULL);
		signal(SIGINT, sig_ctrl_c);
		signal(SIGPIPE, SIG_IGN);
		input = readline(GREEN"░▒▓█[42]█▓▒░ ");
		if (!input)
			break ;
		add_history(input);
		env = get_env(NULL);
		ms_exec(input, env);
	}
	return (0);
}
