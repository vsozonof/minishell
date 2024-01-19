/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:37:37 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/18 23:29:26 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_input_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	else if (!exception_checker(str))
		return (0);
	else if (!unclosed_quote_detector(str))
		return (0);
	return (1);
}

int	exception_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_in_quotes(str, i))
		{
			if ((str[i] == '(' || str[i] == ')'))
				return (pr_error("input error : parenthesis detected."));
			else if (str[i] == '*')
				return (pr_error("input error : wildcard detected."));
			else if (str[i] == '&')
				return (pr_error("input error : `&' detected."));
			else if (str[i] == ';')
				return (pr_error("input error : `;' detected."));
		}
		i++;
	}
	return (1);
}
