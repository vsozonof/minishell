/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 06:15:38 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/08 07:23:43 by vsozonof         ###   ########.fr       */
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

int	is_valid_pipe(char *str, int i)
{
	printf("i = %i\n", i);
	while (ft_is_whitespace(str[i]) && str[i])
		i++;
	if (str[i] == '|')
		return (printf
			("minishell: syntax error near unexpected token `|'\n"));
	while (str[i])
	{
		while (str[i] && str[i] != '|')
			i++;
		if (str[i] == '|' && str[i + 1] == '|'
			&& str[i + 2] != '|')
			return (printf("Double Pipe Handler\n"));
		else if (str[i] == '|' && str[i + 1] == '|'
			&& str[i + 2] == '|')
			return (printf
				("minishell: syntax error near unexpected token `|'\n"));
		else
			i++;
	}
	return (0);
}
