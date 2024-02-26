/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_utils-2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:49:44 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/26 11:53:10 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	if (c == 39 || c == '"' || c == '>' || c == '<')
		return (0);
	return (1);
}

int	is_there_redirs(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->input[++i])
		if ((prompt->input[i] == '>' || prompt->input[i] == '<')
			&& !is_in_quotes(prompt->input, i))
			return (1);
	return (0);
}
