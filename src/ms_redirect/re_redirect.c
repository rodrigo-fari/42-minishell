/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:31:47 by aeberius          #+#    #+#             */
/*   Updated: 2025/02/23 21:30:21 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Redicionamento de Saída (> e >>): */
/* >: Redireciona a saída padrão (stdout) de um comando para um arquivo,
sobrescrevendo o conteúdo do arquivo. */
/* >>: Redireciona a saída padrão (stdout) de um comando para um arquivo,
anexando ao conteúdo existente do arquivo. */
/* Redirecionamento de Entrada (<):
<: Redireciona a entrada padrão (stdin) de um comando
a partir de um arquivo. */
/* Redirecionamento de Erro (2> e 2>>):
2>: Redireciona a saída de erro padrão (stderr) de um comando para um arquivo,
sobrescrevendo o conteúdo do arquivo.
2>>: Redireciona a saída de erro padrão (stderr) de um comando para um arquivo,
anexando ao conteúdo existente do arquivo. */

void redirect_input(const char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void redirect_output(const char *file, int append)
{
    int fd;
	printf("file: %s\n", file);
    if (append)
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
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
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDERR_FILENO) < 0)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}
