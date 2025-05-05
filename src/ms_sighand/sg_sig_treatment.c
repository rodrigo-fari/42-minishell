/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sg_sig_treatment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:12:38 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/05 20:13:47 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
