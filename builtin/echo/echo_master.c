/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:48:29 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/23 12:11:51 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(char **param, t_data *data)
{
	int		i;
	int		flag;
	int		wr;

	i = 1;
	wr = ((flag = 0));
	while (param[i])
	{
		if (ft_strnstr(param[i], "-n", 2) && !wr)
		{
			i++;
			flag = 1;
		}
		else
		{
			wr = 1;
			if (param[i + 1])
				printf("%s ", param[i]);
			else
				printf("%s", param[i]);
			i++;
		}
	}
	if (!flag)
		printf("\n");
	set_status(data, 0, NULL, NULL);
}

int	is_wspace_or_null(char *str, int i)
{
	if (ft_is_whitespace(str[i]) || !str[i])
		return (1);
	else
		return (0);
}

int	flag_skipper(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '-')
			break ;
	while (str[i])
	{
		if (str[i] == '-')
			i++;
		else
			break ;
		if (str[i] != 'n')
			break ;
		while (str[i] && str[i] == 'n')
			i++;
		if (!ft_is_whitespace(str[i]))
			break ;
		else
			while (str[i] && ft_is_whitespace(str[i]))
				i++;
	}
	return (i);
}
