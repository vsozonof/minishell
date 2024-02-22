/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:02:04 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 15:45:57 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_manager(t_cmd *cmd, t_data *data)
{
	cmd = data->exec;
	// fprintf(stderr, "cmd->n_cmds = %d\n", cmd->data->n_cmd);
	if (get_node_len(cmd) > 1)
		pipex_exec(cmd);
	else
		single_arg(cmd);
	fprintf(stderr, "fin exec\n");
	return (0);
}
