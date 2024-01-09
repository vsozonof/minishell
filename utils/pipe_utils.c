/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 06:15:38 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/09 07:16:50 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->input[++i])
		if (prompt->input[i] == '|')
			return (1);
	return (0);
}

int	is_valid_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '|')
		return (pr_error("syntax error near unexpected token `|'"));
	while (str[i])
	{
		while (str[i] && str[i] != '|')
			i++;
		if (str[i] == '|' && str[i + 1] == '|'
			&& str[i + 2] != '|')
			return (pr_error("`||' operator not handled"));
		else if (str[i] == '|' && str[i + 1] == '|'
			&& str[i + 2] == '|')
			return (pr_error("syntax error near unexpected token `|'"));
		if (str[i] == '|')
			i++;
	}
	return (0);
}
