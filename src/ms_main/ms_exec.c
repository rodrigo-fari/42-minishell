/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:36:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/10 15:22:46 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_exec(t_env *env, char *input)
{
	char	**user_input;

	if (input[0] == '\0')
		return ;
	user_input = ft_split(input, ' ');
	if (!parsing(input))
	{
		free_splits(user_input);
		return ;
	}
	exec_builtins(user_input, env);
	free_splits(user_input);
}
