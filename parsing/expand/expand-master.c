/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand-master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:31:51 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 15:31:11 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_nodes(t_cmd *cmd, t_data *data)
{
	t_cmd	*nav;
	int		i;

	(void)cmd;
	i = 0;
	nav = data->exec;
	while (nav)
	{
		data->input = nav->cmd;
		reg_expander(data, 0);
		nav->cmd = ft_strdup(data->input);
		free(data->input);
		while (nav->param[i])
		{
			data->input = nav->param[i];
			reg_expander(data, 0);
			if (data->input)
				nav->param[i] = ft_strdup(data->input);
			else
				nav->param[i] = NULL;
			i++;
		}
		nav = nav->next;
	}
}
