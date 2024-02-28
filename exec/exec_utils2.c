/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:42:38 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/28 05:38:44 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_problem(t_data *data, int *file, t_cmd *cmd)
{
	int		status;

	status = data->i_status;
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

int	**alloc_pipe(void)
{
	int		**pipefd;
	int		i;

	i = 0;
	pipefd = NULL;
	if (i == 0)
	{
		pipefd = malloc(sizeof(int *) * 2);
		if (!pipefd)
			return (write(2, "probleme happend in alloc_pipe\n", 32), NULL);
		pipefd[0] = malloc(sizeof(int) * 2);
		pipefd[1] = malloc(sizeof(int) * 2);
		if (!pipefd[0] || !pipefd[1])
		{
			free(pipefd[0]);
			free(pipefd[1]);
			return (write(2, "probleme when creating the pipe\n", 33), NULL);
		}
		pipe(pipefd[0]);
		pipe(pipefd[1]);
	}
	return (pipefd);
}

void	close_all_open_redirs(int *file, t_cmd *cmd)
{
	int		i;
	t_redir	*re;

	i = 0;
	re = cmd->redirs;
	while (len_list(cmd->redirs) > i)
	{
		if (file[i] > -1)
		{
			close(file[i]);
			if (re->type == 3)
				unlink(re->file);
		}
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
