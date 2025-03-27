/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:07 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/26 23:28:47 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_fix(char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		commands[i] = verify_quotes(commands[i]);
		i++;
	}
}

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
	printf("current_quote = %c\n", current_quote);
	return (replace_values(input, i, current_quote, key, env_manager(NULL)));
}

char	*replace_values(char *input, int i, char current_quote, bool key, t_env *env)
{
	char	*ret_str;

	// printf("Estou entrando aq\n");
	if (key == true && current_quote == '\"')
	{
		ret_str = remove_quotes_and_expand(input, key, i, current_quote, env);
		free(input);
		return (ret_str);
	}
	else if (key == true && current_quote == '\'')
	{
		ret_str = remove_quotes_and_expand(input, key, i, current_quote, env);
		free(input);
		return (ret_str);
	}
	ret_str = remove_quotes_and_expand(input, key, i, current_quote, env);
	free(input);
	return (ret_str);
}

char	*remove_quotes_and_expand(char *input, bool key, int start, char current_quote, t_env *env)
{
	char	*ret_str;
	char	*tmp;
	char	*var_name;
	char	*var_value;
	int		i;

	i = start;
	ret_str = NULL;
	while (input[i] && input[i] != current_quote)
	{
		if (input[i] == '$' && (current_quote == '\"' || !current_quote))
		{
			i++;
			var_name = extract_var_name(input, &i);
			var_value = get_env_value(env, var_name);
			free(var_name);
			if (var_value)
			{
				tmp = append_string_to_string(ret_str, var_value);
				ret_str = tmp;
			}
		}
		else if (input[i] == '$' && current_quote == '\'' && key == false)
		{
			i++;
			var_name = extract_var_name(input, &i);
			var_value = get_env_value(env, var_name);
			free(var_name);
			if (var_value)
			{
				tmp = append_string_to_string(ret_str, var_value);
				ret_str = tmp;
			}
		}
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
