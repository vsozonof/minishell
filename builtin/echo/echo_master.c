/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:48:29 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/23 12:17:50 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(char **param, t_data *data)
{
	int		i;
	int		flag;
	int		wr;

	i = 0;
	wr = ((flag = 0));
	while (param[++i])
	{
		if (ft_strnstr(param[i], "-n", 2) && !wr)
			flag = 1;
		else
		{
			wr = 1;
			if (param[i + 1])
				printf("%s ", param[i]);
			else
				printf("%s", param[i]);
		}
	}
	if (!flag)
		printf("\n");
	set_status(data, 0, NULL, NULL);
}
