/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:39:28 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 11:40:06 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Prints all environment variables stored in a linked list of `t_env`.
 * 
 * This function iterates through a linked list of `t_env` nodes and prints each
 * environment variable in the format `KEY=VALUE`, followed by a newline.
 * 
 * @param head A pointer to the head of the `t_env` linked list. Each node 
 *stores a key-value pair representing an environment variable.
 * 
 * @note 
 * - The function assumes the `head` pointer and nodes are properly initialized.
 * - Undefined behavior may occur if the list is malformed or contains invalid
 *data.
 * - The iteration stops when the `next` pointer of a node is `NULL`.
 * - If `key` or `value` is `NULL`, `(null)` is printed in place of that field.
 * 
 * @example
 * For a linked list with:
 * - Node 1: key = "PATH", value = "/usr/bin"
 * - Node 2: key = "HOME", value = "/home/user"
 * 
 * The output will be:
 * PATH=/usr/bin
 * HOME=/home/user
 */
void	print_env(t_env *head)
{
	while (head->next)
	{
		printf("%s", head->key);
		printf("=");
		printf("%s\n", head->value);
		head = head->next;
	}
}
