/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_validator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:23:26 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/07 21:35:06 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Prints a validation result message based on the validator value.
 * 
 * This function prints the given string followed by a validation result. If the 
 * validator is negative, it prints "Unavailable" in yellow. If the validator is 
 * `true`, it prints "Valid" in green. Otherwise, it prints "Invalid" in red.
 * 
 * @param validator An integer representing the validation result. A negative 
 *                  value results in "Unavailable", `true` prints "Valid", 
 *                  and all other values print "Invalid".
 * @param str The string to be printed before the validation result message.
 * 
 * @note 
 * - The function uses colored text for messages, with colors defined by the 
 *   `YELLOW`, `GREEN`, `RED`, and `RESET` macros.
 * - Ensure that the necessary macros are defined for proper color formatting.
 * 
 * @example
 * For `validator = -1`, `str = "Test: "`, the output will be:
 * ```
 * Test: Unavailable!
 * ```
 * 
 * For `validator = true`, `str = "Test: "`, the output will be:
 * ```
 * Test: Valid!
 * ```
 * 
 * For `validator = 0`, `str = "Test: "`, the output will be:
 * ```
 * Test: Invalid!
 * ```
 */
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
