/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:42:38 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 17:41:21 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//wc > test1 < test2 | cat < test3 > test4 | sleep5
void	free_problem(t_data *data, int *file, t_cmd *cmd)
{
	int		status;

	status = data->status_code;
	if (data->n_redirs > 0 && file != NULL)
		close_all_open_redirs(file, cmd);
	if (len_cmd(data->exec) > 1)
		free(data->pid);
	free_master(data);
	free_end_of_program(data->pr);
	exit(status);
}

void	redir_failed(t_data *data, int *file, int i)
{
	close_open_redirs(file, i - 1);
	free(data->pid);
	free_master(data);
	free_end_of_program(data->pr);
	exit(0);
}

void	free_problem_cmd_not_found(t_data *data, int *file, t_cmd *cmd)
{
	write(2, data->exec->cmd, ft_strlen(data->exec->cmd));
	write(2, ": command not found\n", 21);
	if (data->n_redirs > 0)
		close_all_open_redirs(file, cmd);
	free_master(data);
	free_end_of_program(data->pr);
	// exit(0);
}

void	close_all_open_redirs(int *file, t_cmd *cmd)
{
	int		i;
	t_redir	*re;

	i = 0;
	re = cmd->redirs;
	fprintf(stderr, "JE VIENS CLOSE\n");
	while (len_list(cmd->redirs) > i)
	{
		if (file[i] > -1)
			close(file[i]);
		if (re->type == 3)
			unlink(re->file);
		re = re->next;
		i++;
	}
	free(file);
}

void	close_open_redirs(int *file, int i)
{
	while (i >= 0)
	{
		close(file[i]);
		i--;
	}
	free(file);
}
