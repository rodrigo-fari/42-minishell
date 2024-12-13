/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:36:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/13 21:23:27 by rde-fari         ###   ########.fr       */
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
	while(input[i])
	{
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
			last_quote = last_ocurrence(input, input[i++]);
		while (i <= (last_quote - 1))
			n_input = charjoin(n_input, input[i++]);
	}
	printf("%s\n", n_input);
	return (n_input);
}

void	ms_exec(t_env *env, char *input)
{
	char	**user_input;

	if (input[0] == '\0')
		return ;
	user_input = ft_split(input, ' ');
	if (!parsing(input, user_input))
	{
		free_splits(user_input);
		return ;
	}
	exec_builtins(user_input, env);
	free_splits(user_input);
}
