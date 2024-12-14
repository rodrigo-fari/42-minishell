/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:38:24 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/14 17:17:32 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_cd(char **user_input, t_env *env)
{
	char	*old_pwd;

	old_pwd = NULL;
	if (check_too_many_arguments(user_input) == true)
		return ;
	old_pwd = getcwd(NULL, 0);
	if (!user_input[1] || ft_strcmp(user_input[1], "~") == 0)
	{
		if (chdir(find_path_home_in_env(env)) == 0)
			update_pwd(env, old_pwd);
	}
	else if (ft_strcmp(user_input[1], "-") == 0)
	{
		if (chdir(find_oldpwd_in_env(env)) == 0)
			update_pwd(env, old_pwd);
	}
	else
	{
		if (chdir(user_input[1]) == 0)
			update_pwd(env, old_pwd);
		else
			perror("bash: cd");
	}
	return ;
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

void	update_pwd(t_env *env, char *old_pwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
			env->value = pwd;
		if (ft_strcmp(env->key, "OLDPWD") == 0)
			env->value = old_pwd;
		env = env->next;
	}
}
