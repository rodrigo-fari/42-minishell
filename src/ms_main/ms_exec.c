/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:36:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/15 14:19:23 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*remove_quotes(char *input)
{
	char	*n_input;
	int		last_quote;
	int		i;

	n_input = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
		{
			last_quote = last_ocurrence(input, input[i++]);
			while (i <= (last_quote - 1))
				n_input = charjoin(n_input, input[i++]);
			return (n_input);
		}
		n_input = charjoin(n_input, input[i]);
		i++;
	}
	return (n_input);
}

void	ms_exec(t_env *env, char *input)
{
	char	**user_input;
	int		i = -1;

	if (input[0] == '\0' || !parsing(input))
		return ;
	input = remove_quotes(input);
	user_input = ft_split(input, ' ');
	if (ft_strchr(input, '$'))
		var_expand(user_input, env);
	while (user_input[++i])
		printf("user_input[%d] = %s\n", i, user_input[i]);
		
	exec_builtins(user_input, env, input);
	free(input);
	free_splits(user_input);
}
