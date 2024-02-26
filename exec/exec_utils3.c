/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:48:51 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 15:57:26 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_redir_parent(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->exec;
	fprintf(stderr, "je casse la?\n");
	while (cmd)
	{
		if (len_list(cmd->redirs))
		{
			while (cmd->redirs)
			{
				if (cmd->redirs->type == 3)
				{
					close(cmd->redirs)
					unlink(cmd->redirs->file);
				}
				cmd->redirs = cmd->redirs->next;
			}
		}
		cmd = cmd->next;
	}
}
