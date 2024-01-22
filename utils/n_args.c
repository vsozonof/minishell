/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_args.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 05:05:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/22 11:39:20 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_args(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	while (str[i] && !ft_is_whitespace(str[i]))
		i++;
	while (str[i])
	{
		if (ft_is_whitespace(str[i]))
			i++;
		else
		{
			c++;
			while (str[i] && !ft_is_whitespace(str[i]))
				i++;
		}
	}
	return (c);
}
