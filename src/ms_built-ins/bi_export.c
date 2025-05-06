/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   */
/*   Created: 2025/01/02 11:38:29 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/23 14:11:45 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_key_value(char *input, char **key, char **value, bool *has_equal)
{
	char	*equal_sign;

	equal_sign = ft_strchr(input, '=');
	*has_equal = (equal_sign != NULL);
	if (*has_equal)
	{
		*key = ft_substr(input, 0, equal_sign - input);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(input);
		*value = NULL;
	}
}

void	process_key_value(t_env *env, char *key, char *value, bool has_equal)
{
	if (!is_valid_key(key))
	{
		handle_invalid_key(key, value);
		return ;
	}
	if (value == NULL)
		env_update(env, key, "", has_equal);
	else
		env_update(env, key, value, has_equal);
	free(key);
	free(value);
}

void	bi_export(t_env *env, char **user_input)
{
	int		i;
	char	*key;
	char	*value;
	bool	has_equal;

	i = 1;
	if (user_input[1] == NULL)
	{
		print_org_env(env);
		return ;
	}
	while (user_input[i] != NULL)
	{
		parse_key_value(user_input[i], &key, &value, &has_equal);
		if (!is_valid_key(key))
		{
			free(key);
			free(value);
		}
		else
		{
			process_key_value(env, key, value, has_equal);
		}
		i++;
	}
}

bool	is_valid_key(char *key)
{
	int	i;

	if (!key || key[0] == '=' || !ft_isalpha(key[0]))
	{
		bi_error("Minishell: export: not a valid identifier\n");
		g_exit_status = 1;
		return (false);
	}
	i = 1;
	while (key[i] != '\0')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			bi_error("Minishell: export: not a valid identifier\n");
			g_exit_status = 1;
			return (false);
		}
		i++;
	}
	return (true);
}

void	env_add(t_env *env, char *key, char *value, bool has_equal)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (new == NULL)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->has_equal = has_equal;
	new->next = NULL;
	listadd_back(&env, new);
}
