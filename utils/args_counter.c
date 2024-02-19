/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 05:05:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/19 16:14:23 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_args(char *str)
{
	int	i;
	int	c;

	c = ((i = 0));
	while (str[i])
	{
		if (ft_is_whitespace(str[i]))
			i++;
		else if (str[i] == 39 || str[i] == '"')
		{
			i += (quote_skipper(str, i) - i);
			c++;
		}
		else
		{
			c++;
			while (str[i] && !ft_is_whitespace(str[i]))
				i++;
		}
	}
	return (c);
}

int	quote_skipper(char *str, int c)
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
	if (str[c] == 39 || str[c] == '"')
		c++;
	return (c);
}

int	hdoc_counter(char *str)
{
	int	i;
	int	n;

	n = ((i = 0));
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			n++;
			i += 2;
		}
		i++;
	}
	return (n);
}
