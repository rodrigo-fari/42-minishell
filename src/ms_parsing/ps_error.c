/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:33 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 15:07:32 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ps_error(char *str, char **user_input)
{
	printf(RED"[Error]"RESET);
	printf("%s\n", str);
	if (user_input)
		free_splits(user_input);
}
