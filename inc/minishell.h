/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:19:21 by rde-fari          #+#    #+#             */
/*   Updated: 2024/11/30 16:21:37 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

//=====================================| Colors |
# define RED "\033[31m"
# define GREEN "\033[32m"
# define ORANGE "\033[38;5;208m"
# define PURPLE "\e[35m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

//=====================================| Libraries |
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <readline/readline.h>
# include <curses.h>
# include <term.h>
# include "../src/ms_libft/libft/libft.h"

//=====================================| Support Defines |



//=====================================| Structs |
typedef struct s_struct
{
	void		*data;
}				t_struct;

//=====================================| Function declaration (by file) |


//=====================================| Endif |
#endif