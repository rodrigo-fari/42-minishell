/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:53:41 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 10:01:11 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Adds a new node to the end of a linked list of `t_env` structures.
 * 
 * This function appends a new `t_env` node to the end of an existing linked 
 * list. If the list is empty (i.e., the head is `NULL`), the new node becomes
 * the head. Otherwise, the function finds the last node and links it to the 
 * new node.
 * 
 * @param lst A pointer to the head pointer of the linked list of `t_env` nodes.
 *            This allows modifying the head of the list if it's empty.
 * @param new A pointer to the new `t_env` node to be added to the list.
 * 
 * @note 
 * - The function assumes that the `new` node is properly allocated and 
 *   initialized.
 * - If the list is empty, the new node becomes the head of the list.
 * - The `list_last` function is used to find the last node in the list.
 */
void	listadd_back(t_env **lst, t_env *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		list_last(*lst)->next = new;
}

/**
 * @brief Finds and returns the last node in a linked list of `t_env` structures.
 * 
 * This function iterates through the linked list of `t_env` nodes until it
 * reaches the last node (i.e., the node whose `next` pointer is `NULL`).
 * It returns a pointer to this last node. If the list is empty, it returns
 * `NULL`.
 * 
 * @param lst A pointer to the head of the linked list of `t_env` nodes.
 * 
 * @return A pointer to the last node in the linked list, or `NULL` if the list
 * is empty.
 * 
 * @note 
 * - The function assumes that the list is properly initialized.
 * - If the list is empty, `lst` is `NULL`, and the function will return `NULL`.
 * 
 * @example
 * Given a linked list:
 * - Node 1: key = "PATH", value = "/usr/bin"
 * - Node 2: key = "HOME", value = "/home/user"
 * 
 * The function will return a pointer to Node 2, which is the last node.
 */
t_env	*list_last(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
