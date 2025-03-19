/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:11:14 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/19 15:10:34 by rde-fari         ###   ########.fr       */
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