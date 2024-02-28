/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:05:48 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/28 01:52:58 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_problem_single(t_data *data, int *file)
{
	int		status;

	status = data->i_status;
	if (data->n_redirs > 0 && file != NULL)
		close_all_open_redirs(file, data->exec);
	if (len_cmd(data->exec) > 1)
		free(data->pid);
	close(data->du1);
	close(data->du2);
	free_master(data);
	free_end_of_program(data->pr);
	exit(status);
}
