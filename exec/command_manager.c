/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:02:04 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 10:56:43 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_manager(t_cmd *cmd, t_data *data)
{
	cmd = data->exec;
	// if (cmd->n_cmd > 1)
	// 	multi_arg(cmd);
	// else
	single_arg(cmd);
	return (0);
}
