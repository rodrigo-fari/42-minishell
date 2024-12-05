/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_validator.C                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:23:26 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/05 19:53:58 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	validator(int validator, char *str)
{
	printf("%s", str);
	if (validator < 0)
		printf(YELLOW"Unavailable!\n"RESET);
	else if (validator == true)
		printf(GREEN"Valid!\n"RESET);
	else
		printf(RED"Invalid!\n"RESET);
}
