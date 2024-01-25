/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 23:35:58 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/24 05:07:51 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && is_in_quotes(str, i) != 1)
			return (1);
	return (0);
}

int	is_there_backslash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\\' && is_in_quotes(str, i) != 1)
			return (1);
	return (0);
}

int	is_valid_char(int c)
{
	if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
		return (1);
	else
		return (0);
}