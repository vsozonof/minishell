/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:30:26 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/26 20:21:44 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_checker(char *str, int i)
{
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '\0')
		return (pr_error("parse error near '\\n'"));
	else if (str[i] == '<')
		return (pr_error("parse error near '<'"));
	else if (str[i] == '>')
		return (pr_error("parse error near '>'"));
	return (1);
}

int	is_there_redirs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if ((str[i] == '>' || str[i] == '<') && is_in_quotes(str, i) != 1)
			return (1);
	return (0);
}
