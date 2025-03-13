/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:07 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/13 17:35:10 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_expand(char *input)
{
	t_env	*tmp;

	tmp = env_manager(NULL);
	printf("INPUT = %s\n", input);
	while (tmp)
	{
		if (ft_strcmp(input, tmp->key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char 	*verify_quotes(char *input)
{
	int		i;
	int		len;
	char	current_quote;
	char	*ret_str;
	bool	key;

	key = false;
	i = 0;
	ret_str = NULL;
	while (input[i] && (input[i] != '\'' && input[i] != '\"'))
		i++;
	current_quote = input[i];
	while (input[i] && input[i] == current_quote)
	{
		key = bool_changer(key);
		i++;
	}
	len = 0;
	if (key == true)
		return (get_quote_content(input, current_quote, i, 0));
	return (get_quote_content(input, '\"', 0, 0));
}

char	*get_quote_content(char *input, char current_quote, int i, int j)
{
	int		len;
	char	*ret_str;
	char	*tmp_str;
	char	**input_array;

	len = 0;
	while (input[i] && input[i] != current_quote)
	{
		i++;
		len++;
	}
	ret_str = ft_substr(input, (i - len), len);
	if (current_quote == '\"')
	{
		input_array = ft_split(ret_str, ' ');
		free (ret_str);
		while (input_array[j])
		{
			if (ft_strchr(input_array[j], '$'))
			{
				tmp_str = ft_strdup(input_array[j]);
				free(input_array[j]);
				input_array[j] = var_expand(tmp_str + 1);
				free (tmp_str);
			}
			printf("input_array = %s\n", input_array[j]); 
			ft_strjoin(ret_str, input_array[j]);
			printf("ret_str = %s\n", ret_str);
			j++;
		}
	}
	free (input);
	return (ret_str);
}

void	remove_quotes(char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		commands[i] = verify_quotes(commands[i]);
		i++;
	}
}

bool	bool_changer(bool key)
{
	if (key == true)
		return (false);
	return (true);
}
