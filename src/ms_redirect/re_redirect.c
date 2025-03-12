/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:31:47 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/12 12:27:55 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirect_input(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0) {
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void redirect_output(const char *file, int append)
{
	int fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0) {
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void redirect_error(const char *file, int append)
{
	int fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDERR_FILENO) < 0) {
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}