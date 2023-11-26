/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 05:01:39 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/26 07:39:26 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flags_counter(char *str)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (str[++i])
		if (((str[i] == '-' && ft_isalpha(str[i + 1])) && str[i - 1] != '-')
			|| ((str[i] == '-' && str[i + 1] == '-') && ft_isalpha(str[i + 2])))
			c++;
	return (c);
}

int	flags_counter_pipe(char *str)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (str[++i] && str[i] != '|')
		if (((str[i] == '-' && ft_isalpha(str[i + 1])) && str[i - 1] != '-')
			|| ((str[i] == '-' && str[i + 1] == '-') && ft_isalpha(str[i + 2])))
			c++;
	return (c);
}
