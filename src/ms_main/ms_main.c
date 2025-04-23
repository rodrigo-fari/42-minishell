/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:47:50 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/23 23:41:02 by rde-fari         ###   ########.fr       */
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
	env = env_manager(env);
	while (true)
	{
		env = env_manager(NULL);	
		//signal(SIGINT, sig_ctrl_c);
		//signal(SIGPIPE, SIG_IGN);
		input = readline("43$ ");
		if (!input)
			break ;
		add_history(input);
		env = env_manager(NULL);
		ms_exec(input, env);
	}
	return (0);
}
