/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:38:58 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/13 23:43:22 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_exit(char **user_input, t_env *env, char *input)
{
	if (input)
		free(input);
	if (user_input)
		free(user_input);
	if (env)
		free(env);
	exit (0);
}

//Apenas para testes, exit necessita mais informação e parametros!