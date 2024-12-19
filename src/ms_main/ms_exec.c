/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:36:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/19 14:48:31 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*remove_quotes(char *input)
{
	char	*n_input;
	int		last_quote;
	int		i;

	i = 0;
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
		{
			last_quote = last_ocurrence(input, input[i++]);
			n_input = ft_calloc(sizeof(char), last_quote + 1);
			ft_strlcpy(n_input, input, last_quote);
			free(input);
			return (n_input);
		}
	return (input);
}

void	ms_exec(t_env *env, char *input)
{
	char	**user_input;
	char	*new_input;

	if (input[0] == '\0' || !parsing(input))
		return ;
	new_input = remove_quotes(input);
	user_input = ft_split(new_input, ' ');
	if (ft_strchr(new_input, '$'))
		var_expand(user_input, env);
	exec_builtins(user_input, env, new_input);
}
