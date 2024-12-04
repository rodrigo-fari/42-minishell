/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:33 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/04 14:51:15 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parse_syntax(const char *input)
{
	if (!input)
		return false;
	if (ft_strcmp((char *)input, "exit") == false)
		exit (0);
	return (true);
}
