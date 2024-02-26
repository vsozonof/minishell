/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:42:38 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 09:46:00 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//wc > test1 < test2 | cat < test3 > test4 | sleep5
void	free_problem(t_data *data, int *file, t_cmd *cmd)
{
	if (data->n_redirs > 0 && file != NULL)
		close_all_open_redirs(file, cmd);
	// if (pipefd != NULL)
	// 	free_pipe(pipefd, i);
	free_master(data);
	free_end_of_program(data->pr);
	// exit(0);
}

void	redir_failed(t_data *data, int *file, int i)
{
	close_open_redirs(file, i - 1);
	free_master(data);
	free_end_of_program(data->pr);
	// exit(0);
}

void	free_problem_cmd_not_found(t_data *data, int *file, t_cmd *cmd)
{
	fprintf(stderr, "%s: command not found\n", data->exec->cmd);
	if (data->n_redirs > 0)
		close_all_open_redirs(file, cmd);
	free_master(data);
	free_end_of_program(data->pr);
	// exit(0);
}

void	close_all_open_redirs(int *file, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (len_list(cmd->redirs) > i)
	{
		fprintf(stderr, "voici mon i %d\n", i);
		close(file[i]);
		i++;
	}
	free(file);
}

void	close_open_redirs(int *file, int i)
{
	while (i >= 0)
	{
		fprintf(stderr, "voici mon i %d\n", i);
		close(file[i]);
		i--;
	}
	free(file);
}
