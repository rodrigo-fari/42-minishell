/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:46:29 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/07 21:41:40 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks the validity of quotes in a string for syntax correctness.
 * 
 * This function validates whether all single (`'`) and double (`"`) quotes 
 * in the input string are properly matched and closed. It also counts their 
 * occurrences.
 * 
 * @param input A pointer to the input string to be checked.
 * @param i Initial index for iteration (typically set to -1 to start at 0).
 * @param s_quote An integer to track occurrences of single quotes (`'`).
 * @param d_quote An integer to track occurrences of double quotes (`"`).
 * 
 * @return Returns `true` if all quotes are properly matched and closed. Returns
 *         `false` otherwise.
 * 
 * @note 
 * - The function assumes the input string is null-terminated.
 * - Improper nesting or unclosed quotes will result in a `false` return.
 * - The `validation` variable ensures the total number of quotes is even.
 * - Counters for single and double quotes must also be even for a valid result.
 * 
 * @example
 * Given the input string: "This is a 'test' with \"quotes\"."
 * - The function will return `true` as all quotes are properly matched.
 * 
 * For the input string: "This is an 'unmatched test."
 * - The function will return `false` due to an unclosed single quote.
 */
bool	quote_check(char *input, int i, int s_quote, int d_quote)
{
	char	quote;
	int		validation;

	validation = 0;
	while (input[++i])
	{
		while (input[i] && (input[i] != '\'' && input[i] != '\"'))
			i++;
		quote = input[i++];
		validation++;
		while (input[i] && input[i] != quote)
		{
			if (input[i] == '\"')
				d_quote++;
			if (input[i] == '\'')
				s_quote++;
			i++;
		}
		if (input[i] == quote)
			validation++;
	}
	if (validation % 2 != 0 || s_quote % 2 != 0 || d_quote % 2 != 0)
		return (false);
	return (true);
}

/**
 * @brief Validates the placement of pipe (`|`) characters in the user input.
 * 
 * This function ensures that pipes (`|`) in the user input string are properly 
 * positioned. It checks that pipes are not at the beginning or end of the input
 * and are surrounded by alphanumeric characters or valid input segments.
 * 
 * @param user_input A null-terminated array of strings representing user input 
 *                   split into segments.
 * 
 * @return Returns `true` if all pipes are correctly placed. Returns `false` if 
 *         any pipe is misplaced.
 * 
 * @note 
 * - The first character of `user_input[0]` cannot be a pipe (`|`).
 * - A pipe must be surrounded by valid segments, with no empty or invalid input
 *   immediately before or after it.
 * - The function uses `ft_isalnum` to verify if adjacent segments are
 * alphanumeric.
 * 
 * @example
 * Input: {"echo", "|", "grep", "|", NULL}
 * - Returns `true` because the pipes are properly placed.
 * 
 * Input: {"|", "grep", "test", NULL}
 * - Returns `false` because the pipe is at the beginning.
 * 
 * Input: {"echo", "|", "|", "grep", NULL}
 * - Returns `false` because there are consecutive pipes.
 */
bool	parse_pipes(char **user_input)
{
	int	i;

	if (user_input[0][0] == '|')
		return (false);
	i = 0;
	while (user_input[i])
	{
		if (user_input[i][0] == '|')
		{
			if (user_input[i + 1] && !ft_isalnum(user_input[i - 1][0]))
				return (false);
			if (!user_input[i + 1] || !ft_isalnum(user_input[i + 1][0]))
				return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Validates the placement of input redirection (`<`) in the user input.
 * 
 * This function ensures that the input redirection (`<`) is properly placed in 
 * the user input. It checks that a redirection is not at the beginning or end 
 * and that it is followed by valid input.
 * 
 * @param user_input A null-terminated array of strings representing user input 
 *                   split into segments.
 * 
 * @return Returns `true` if all redirections are correctly placed. Returns `false` 
 *         if any redirection is misplaced.
 * 
 * @note 
 * - The first character of `user_input[0]` cannot be a redirection (`<`).
 * - A redirection must be followed by a valid input segment, not an invalid or 
 *   empty one.
 * - The function uses `ft_isalnum` to verify if adjacent segments are alphanumeric.
 * 
 * @example
 * Input: {"echo", "<", "file.txt", NULL}
 * - Returns `true` because the redirection is properly placed.
 * 
 * Input: {"<", "file.txt", NULL}
 * - Returns `false` because the redirection is at the beginning.
 * 
 * Input: {"echo", "<", "<", "file.txt", NULL}
 * - Returns `false` because there are consecutive redirection symbols.
 */
bool	parse_redin(char **user_input)
{
	int	i;

	if (user_input[0][0] == '<')
		return (false);
	i = 0;
	while (user_input[i])
	{
		if (user_input[i][0] == '<')
		{
			if (user_input[i + 1] && !ft_isalnum(user_input[i - 1][0]))
				return (false);
			if (!user_input[i + 1] || !ft_isalnum(user_input[i + 1][0]))
				return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Validates the placement of output redirection (`>`) in the user input.
 * 
 * This function ensures that the output redirection (`>`) is properly placed in 
 * the user input. It checks that a redirection is not at the beginning or end 
 * of the input and that it is followed by valid input.
 * 
 * @param user_input A null-terminated array of strings representing user input 
 *                   split into segments.
 * 
 * @return Returns `true` if all redirections are correctly placed. Returns `false` 
 *         if any redirection is misplaced.
 * 
 * @note 
 * - The first character of `user_input[0]` cannot be a redirection (`>`).
 * - A redirection must be followed by a valid input segment, not an invalid or 
 *   empty one.
 * - The function uses `ft_isalnum` to verify if adjacent segments are alphanumeric.
 * 
 * @example
 * Input: {"echo", ">", "file.txt", NULL}
 * - Returns `true` because the redirection is properly placed.
 * 
 * Input: {">", "file.txt", NULL}
 * - Returns `false` because the redirection is at the beginning.
 * 
 * Input: {"echo", ">", ">", "file.txt", NULL}
 * - Returns `false` because there are consecutive redirection symbols.
 */
bool	parse_redout(char **user_input)
{
	int	i;

	if (user_input[0][0] == '>')
		return (false);
	i = 0;
	while (user_input[i])
	{
		if (user_input[i][0] == '>')
		{
			if (user_input[i + 1] && !ft_isalnum(user_input[i - 1][0]))
				return (false);
			if (!user_input[i + 1] || !ft_isalnum(user_input[i + 1][0]))
				return (false);
		}
		i++;
	}
	return (true);
}