/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 04:58:56 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/25 05:09:27 by vsozonof         ###   ########.fr       */
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
		if (str[i] != '-' && str[i] != '\0')
			c++;
		while (str[i] && !ft_is_whitespace(str[i]))
			i++;
	}
	return (c);
}
