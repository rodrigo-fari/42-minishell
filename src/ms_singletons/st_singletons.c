/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_singletons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:08:28 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/14 21:37:44 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env(t_env *env)
{
	static t_env	*static_env;

	if (env)
		static_env = env;
	return (static_env);
}

t_shell	*get_shell(void)
{
	static t_shell shell;
	return (&shell);
}
