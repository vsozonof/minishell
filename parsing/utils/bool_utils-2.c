/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_utils-2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:49:44 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/26 16:10:07 by vsozonof         ###   ########.fr       */
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

	i = 0;
	if (!prompt->input[i])
		return (0);
	while (prompt->input[i])
	{
		if ((prompt->input[i] == '>' || prompt->input[i] == '<')
			&& !is_in_quotes(prompt->input, i))
			return (1);
		i++;
	}
	return (0);
}

int	get_heredoc_counter(t_cmd *node)
{
	t_cmd	*pr;
	t_redir	*ptr;
	int		i;

	i = 0;
	pr = node;
	while (pr)
	{
		ptr = pr->redirs;
		while (ptr)
		{
			if (ptr->type == 3)
				i++;
			ptr = ptr->next;
		}
		pr = pr -> next;
	}
	return (i);
}
