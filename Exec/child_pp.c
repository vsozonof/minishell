/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:10:29 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/24 04:52:47 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dup(int pipe, int token, int pipe2)
{
	if (token == 0)
	{
		if (dup2(0, 0) < 0)
			return (printf("problem with dup2 1"), -1);
		if (dup2(pipe2, 1) < 0)
			return (printf("problem with dup2 2"), -1);
	}
	else if (token == 1)
	{
		if (dup2(pipe, 0) < 0)
			return (printf("problem with dup2 3"), -1);
		if (dup2(1, 1) < 0)
			return (printf("problem with dup2 4"), -1);
	}
	else if (token == 2)
	{
		if (dup2(pipe, 0) < 0)
			return (printf("problem with dup2 5"), -1);
		if (dup2(pipe2, 1) < 0)
			return (printf("problem with dup2 6"), -1);
	}
	return (0);
}

// regler le probleme des fd
char	*child_process_in(int **pipefd, t_data *data, int i, int token)
{
	char		*cmd;
	char		**buf;
	// int			verif;

	// verif = 0;
	if (i == 0 || i == data->n_cmds -1 )
	{
		if (child_process_in_or_out(pipefd, data, i, token) == -1)
			return (NULL);
	}
	else if (token == 0 || token == 1)
	{
		if (child_process_middle(pipefd, data, token) == -1)
			return (NULL);
	}
	buf = arg(data->cmds[i]);
	cmd = ft_do_process(data->pr->nv, buf[0]);
	if (cmd == NULL)
		return (free_pipe_argv(pipefd, data->cmds), NULL);
	free(pipefd[0]);
	free(pipefd[1]);
	return (cmd);
}

int	child_process_in_or_out(int	**pipefd, t_data *data, int i, int token)
{
	int	verif;

	if (i == 0)
	{
		close(pipefd[0][0]);
		close(pipefd[1][0]);
		close(pipefd[1][1]);
		if (check_dup(0, 0, pipefd[0][1]) == -1)
			return (close(pipefd[0][1]), free_pipe_argv(pipefd, data->cmds), -1);
		close(pipefd[0][1]);
	}
	else if (i == data->n_cmds - 1)
	{
		close(pipefd[1][1]);
		close(pipefd[0][1]);
		if (token == 0)
			verif = check_dup(pipefd[1][0], 1, 0);
		else
			verif = check_dup(pipefd[0][0], 1, 0);
		close(pipefd[1][0]);
		close(pipefd[0][0]);
		if (verif == -1)
			return (free_pipe_argv(pipefd, data->cmds), -1);
	}
	return (0);
}

int		child_process_middle(int **pipefd, t_data *data, int token)
{
	int		verif;

	if (token == 0)
	{
		close(pipefd[1][1]);
		close(pipefd[0][0]);
		verif = check_dup(pipefd[1][0], 2, pipefd[0][1]);
		close(pipefd[1][0]);
		close(pipefd[0][1]);
		if (verif == -1)
			return (free_pipe_argv(pipefd, data->cmds), -1);
	}
	else if (token == 1)
	{
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		verif = check_dup(pipefd[0][0], 2, pipefd[1][1]);
		close(pipefd[0][0]);
		close(pipefd[1][1]);
		if (verif == -1)
			return (free_pipe_argv(pipefd, data->cmds), -1);
	}
	return (0);
}

char	**arg(char *str)
{
	char	**buf;

	buf = ft_split(str, ' ');
	return (buf);
}