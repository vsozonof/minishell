/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 04:58:56 by vsozonof          #+#    #+#             */
/*   Updated: 2023/12/15 15:49:25 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_counter(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i] && ft_is_whitespace(str[i]))
			i++;
		while (str[i] && !ft_is_whitespace(str[i]))
			i++;
		while (str[i] && ft_is_whitespace(str[i]))
			i++;
		if (str[i] != '-' && str[i] != '\0')
			c++;
	}
	return (c);
}

int	args_counter_pipe(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] && str[i] != '|')
	{
		while (str[i] && ft_is_whitespace(str[i]))
			i++;
		if (str[i] != '-' && str[i] != '\0' && str[i] != '|')
			c++;
		while (str[i] && !ft_is_whitespace(str[i]) && str[i] != '|')
			i++;
	}
	return (c);
}
