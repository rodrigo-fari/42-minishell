/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:38:24 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/13 09:57:52 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_cd(char **user_input, t_env *env)
{
	if (check_too_many_arguments(user_input) == true)
		return ;
	if (!user_input[1] || ft_strcmp(user_input[1], "~") == 0)
		chdir(find_path_home_in_env(env));
	else if (ft_strcmp(user_input[1], "-") == 0)
		chdir(find_oldpwd_in_env(env));
	else
	{
		chdir(user_input[1]);
		// guardar o diretorio atual para atualizar no oldpwd apos execucao
		// efetuar a alteracao pro direto caso exista
		// atualizar o pwd para o atual caso necessario
	}
}

bool	check_too_many_arguments(char **user_input)
{
	int	i;

	i = 0;
	while (user_input[i] != NULL)
	{
		if (i >= 2)
		{
			bi_error("bash: cd: too many arguments");
			return (true);
		}
		i++;
	}
	return (false);
}

char	*find_path_home_in_env(t_env *env)
{
	char	*home_path;

	while (env != NULL)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
		{
			home_path = env->value;
			return (home_path);
		}
		env = env->next;
	}
	bi_error("bash: cd: HOME not set");
	return (NULL);
}

char	*find_oldpwd_in_env(t_env *env)
{
	char	*old_pwd_path;

	while (env != NULL)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			old_pwd_path = env->value;
			return (old_pwd_path);
		}
		env = env->next;
	}
	bi_error("bash: cd: OLDPWD not set");
	return (NULL);
}
