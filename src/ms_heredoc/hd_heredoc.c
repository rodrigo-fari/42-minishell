/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:43:29 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/05 20:23:12 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void handle_heredoc_input(const char *delimiter, int fd)
{
	char *line;

	signal(SIGINT, sig_ctrl_c);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int execute_heredoc(t_ast_node *node)
{
	int fd;

	if (!node || node->type != TOKEN_HEREDOC)
		return (-1);
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	handle_heredoc_input(node->args[0], fd);
	close(fd);
	return (0);
}