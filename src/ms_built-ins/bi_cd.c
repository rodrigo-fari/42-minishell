/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:38:24 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/21 22:36:41 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			bi_error("Minishell: cd: No such file or directory\n");
			g_exit_status = 1;
		}
	}
	free(old_pwd);
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
			bi_error("bash: cd: too many arguments\n");
			g_exit_status = 1;
			return (true);
		}
		i++;
	}
	return (false);
}

char	*find_path_home_in_env(t_env *env)
{
	char	*home_path;
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
		{
			home_path = tmp->value;
			return (home_path);
		}
		tmp = tmp->next;
	}
	bi_error("bash: cd: HOME not set\n");
	g_exit_status = 1;
	return (NULL);
}

char	*find_oldpwd_in_env(t_env *env)
{
	char	*old_pwd_path;
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			old_pwd_path = tmp->value;
			return (old_pwd_path);
		}
		tmp = tmp->next;
	}
	bi_error("bash: cd: OLDPWD not set\n");
	g_exit_status = 1;
	return (NULL);
}

void	update_pwd(t_env *env, char *old_pwd)
{
	char	*pwd;
	t_env	*tmp;

	pwd = getcwd(NULL, 0);
	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_pwd);
		}
		tmp = tmp->next;
	}
	free(pwd);
}
