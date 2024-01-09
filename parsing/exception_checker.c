/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:37:37 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/09 07:46:33 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_input_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (!ft_isalpha(str[i]))
		return (pr_error("parsing error : invalid input."));
	else if (!exception_checker(str))
		return (0);
	else if (!unclosed_quote_detector(str))
		return (0);
	return (1);
}

int	exception_checker(char *str)
{
	int	i;
	int	q_flag;

	i = 0;
	q_flag = 0;
	while (str[i])
	{
		if ((str[i] == 39 || str[i] == '"') && q_flag == 0)
			q_flag = 1;
		else if ((str[i] == 39 || str[i] == '"') && q_flag == 1)
			q_flag = 0;
		if ((str[i] == '(' || str[i] == ')') && !q_flag)
			return (pr_error("parsing error : parenthesis detected."));
		else if (str[i] == '*' && !q_flag)
			return (pr_error("parsing error : wildcard detected."));
		else if (str[i] == '&' && !q_flag)
			return (pr_error("parsing error : `&' detected."));
		else if (str[i] == ';' && !q_flag)
			return (pr_error("parsing error : `;' detected."));
		i++;
	}
	return (1);
}

int	unclosed_quote_detector(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] != 39)
				return (pr_error("parsing error : unclosed single quote."));
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] != '"')
				return (pr_error("parsing error : unclosed double quote."));
		}
		i++;
	}
	return (1);
}
