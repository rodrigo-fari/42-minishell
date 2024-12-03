/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:01:47 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/03 18:45:06 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int main(void)
{
	const char*	input;
	int i = 0;
	input = NULL;
	while(true)
	{
		input = readline("💻Minishell: ");
		while (i++ <= 2)
			printf("%s\n", input);
	}
	return (0);
}
