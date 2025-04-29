/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:18:36 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/22 00:31:10 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_env	*temp;

	env = env_manager(NULL);
	temp = env;
	while (temp)
	{
		printf("%s", temp->key);
		printf("=");
		if (temp->value)
			printf("%s", temp->value);
		printf("\n");
		temp = temp->next;
	}
}

void	update_shell_level(void)
{
	t_env	*env;
	int		value_to_int;
	char	*value_to_char;

	value_to_int = 0;
	env = env_manager(NULL);
	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			value_to_int = ft_atoi(env->value);
			value_to_int++;
			value_to_char = ft_itoa(value_to_int);
			env_update(env, "SHLVL", value_to_char, true);
			// tmp = env->next->next;
			// free (env->next->value);
			// free (env->next->key);
			// free (env->next);
			// env->next = tmp;
			// env_add(env, "SHLVL", value_to_char, true);
			// free (value_to_char);
		}
		env = env->next;
	}
}
