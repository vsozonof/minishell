/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:05:48 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 12:26:26 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_problem_single(t_data *data, int *file, t_cmd *cmd)
{
	if (data->n_redirs > 0 && file != NULL)
		close_all_open_redirs(file, cmd);
	// if (pipefd != NULL)
	// 	free_pipe(pipefd, i);
	if (len_cmd(data->exec) > 1)
		free(data->pid);
	//free(pipefd)
	close(data->du1);
	close(data->du2);
	free_master(data);
	free_end_of_program(data->pr);
	exit(0);
}
