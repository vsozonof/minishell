/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:02:04 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/28 01:32:18 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_manager(t_data *data)
{
	int	*file;

	data->index_here_doc = 0;
	file = NULL;
	data->i_status = 0;
	if (data->n_cmds > 1)
		pipex_exec(data);
	else
	{
		data->du1 = dup(0);
		data->du2 = dup(1);
		file = single_arg(data);
		dup2(data->du1, 0);
		dup2(data->du2, 1);
		close(data->du1);
		close(data->du2);
	}
	return (0);
}
