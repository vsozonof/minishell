/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:42:38 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/25 18:18:31 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_problem(t_data *data, int *file)
{
	if (data->n_redirs > 0)
		close_all_open_redirs(file, data->n_redirs - 1);
	free_master(data);
	free_end_of_program(data->pr);
	exit(0);
}

void	redir_failed(t_data *data, int *file, int i)
{
	close_all_open_redirs(file, i - 1);
	free_master(data);
	free_end_of_program(data->pr);
	exit(0);
}

void	free_problem_cmd_not_found(t_data *data, int *file)
{
	fprintf(stderr, "%s: command not found\n", data->exec->cmd);
	if (data->n_redirs > 0)
		close_all_open_redirs(file, data->n_redirs - 1);
	free_master(data);
	free_end_of_program(data->pr);
	exit(0);
}
