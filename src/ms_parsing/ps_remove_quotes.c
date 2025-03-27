/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:07 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/27 19:42:07 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*verify_quotes(char *input)
{
	int		i;
	char	current_quote;
	bool	key;

	key = false;
	i = 0;
	current_quote = '\0';
	if (input[i] && (input[i] == '\"' || input[i] == '\''))
		current_quote = input[i];
	while (input[i] == current_quote)
	{
		key = bool_changer(key);
		i++;
	}
	return (replace_values(input, i, current_quote, key));
}

char	*replace_values(char *input, int i, char quote, bool key)
{
	t_env	*env;
	char	*ret_str;

	env = env_manager(NULL);
	if (key == true && (quote == '\"' || quote == '\''))
	{
		ret_str = remove_and_expand(input, i, quote);
		free(input);
		return (ret_str);
	}
	ret_str = remove_and_expand(input, i, quote);
	free(input);
	return (ret_str);
}

char	*handle_variable_expansion(char *input, int *i, char *ret_str)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;
	t_env	*env;

	env = env_manager(NULL);
	(*i)++;
	var_name = extract_var_name(input, i);
	var_value = get_env_value(env, var_name);
	free(var_name);
	if (var_value)
	{
		tmp = append_string_to_string(ret_str, var_value);
		ret_str = tmp;
	}
	return (ret_str);
}

char	*remove_and_expand(char *input, int start, char quote)
{
	char	*ret_str;
	char	*tmp;
	int		i;

	i = start;
	ret_str = NULL;
	while (input[i] && input[i] != quote)
	{
		if (input[i] == '$' && (quote == '\"' || !quote))
			ret_str = handle_variable_expansion(input, &i, ret_str);
		else
		{
			tmp = append_char_to_string(ret_str, input[i]);
			ret_str = tmp;
			i++;
		}
	}
	return (ret_str);
}

char	*remove_quotes(char *input)
{
	char	*ret_str;
	char	*tmp;
	int		i;

	i = 0;
	ret_str = NULL;
	while (input[i] && (input[i] == '\"' || input[i] == '\''))
		i++;
	while (input[i] && input[i] != '\"' && input[i] != '\'')
	{
		tmp = append_char_to_string(ret_str, input[i]);
		ret_str = tmp;
		i++;
	}
	return (ret_str);
}
