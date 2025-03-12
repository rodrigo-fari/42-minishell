/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:11:14 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/12 12:33:54 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_print_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	count_args(char **commands)
{
	int count;

	count = 0;
	while (commands[count])
		count++;
	return (count);
}