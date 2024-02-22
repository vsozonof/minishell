/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:02:04 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 14:34:14 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_manager(t_cmd *cmd, t_data *data)
{
	cmd = data->exec;
	// fprintf(stderr, "cmd->n_cmds = %d\n", cmd->n_cmds);
	// if (cmd->n_cmds > 1)
	pipex_exec(cmd);
	// else
		// single_arg(cmd);
	return (0);
}
