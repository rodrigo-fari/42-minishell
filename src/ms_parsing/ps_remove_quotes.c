/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:07 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/17 19:19:24 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_fix(t_token *tokens)
{
	t_token		*temp;

	temp = tokens;
	while (temp)
	{
		temp->value = verify_quotes(temp->value);
		temp = temp->next;
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
	return (replace_values(input, current_quote, key, env_manager(NULL)));
}

char	*replace_values(char *input, char current_quote, bool key, t_env *env)
{
	char	*ret_str;
	
	if (key == true && current_quote == '\"')
	{
		ret_str = remove_quotes_and_expand(input, env);
		free(input);
		return (ret_str);
	}
	else if (key == true && current_quote == '\'')
	{
		ret_str = remove_quotes_and_expand(input, env);
		free(input);
		return (ret_str);
	}
	ret_str = remove_quotes_and_expand(input, env);
	free(input);
	return (ret_str);
}

char	*remove_quotes_and_expand(char *input, t_env *env)
{
	int		i = 0;
	char	quote = '\0';
	char	*ret_str = NULL;
	char	*tmp, *var_name, *var_value;

	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && quote == '\0')
			quote = input[i++];
		else if (input[i] == quote)
			quote = '\0', i++;
		else if (input[i] == '$' && quote != '\'')
		{
			if (!input[i + 1] || (!ft_isalnum(input[i + 1]) && input[i + 1] != '_'))
			{
				// Adiciona o '$' literal
				tmp = append_char_to_string(ret_str, '$');
				ret_str = tmp;
				i++;
			}
			else
			{
				i++;
				var_name = extract_var_name(input, &i);
				var_value = get_env_value(env, var_name);
				free(var_name);
				if (var_value)
				{
					tmp = append_string_to_string(ret_str, var_value);
					free(ret_str);
					ret_str = tmp;
				}
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
	while (input[i])
	{
		while (input[i] && (input[i] == '\"' || input[i] == '\''))
			i++;
		while (input[i] && input[i] != '\"' && input[i] != '\'')
		{
			tmp = append_char_to_string(ret_str, input[i]);
			ret_str = tmp;
			i++;
		}
		i++;
	}
	return (ret_str);
}
