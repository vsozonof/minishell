/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd-utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 05:27:00 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/22 11:17:13 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_arg(char *str)
{
	int		i;
	int		c;
	char	*cd_path;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	while (str[i] && !ft_is_whitespace(str[i]))
		i++;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	c = i;
	if (str[i] == '"' || str[i] == 39)
	{
		c = quoted_arg_util(str, c);
		cd_path = ft_substr(str, i + 1, c - 3);
	}
	else
	{
		while (str[c] && !ft_is_whitespace(str[c]))
			c++;
		cd_path = ft_substr(str, i, c);
	}
	return (cd_path);
}

int	quoted_arg_util(char *str, int c)
{
	if (str[c] == 39)
	{
		c++;
		while (str[c] && str[c] != 39)
			c++;
	}
	else if (str[c] == '"')
	{
		c++;
		while (str[c] && str[c] != '"')
			c++;
	}
	if (str[c] == '"' || str[c] == 39)
		c--;
	return (c);
}
