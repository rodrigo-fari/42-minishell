/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:22:57 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/20 12:25:17 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exit(char **commands, t_env *env)
{
	if (commands)
		free_splits(commands);
	if (env)
		free_env_struct(env);
	printf("exit\n");
	exit(0);
}
