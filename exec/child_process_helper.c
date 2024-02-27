/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:51:54 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 10:03:50 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dup(int pipe, int token, int pipe2)
{
	int	tmp;

	tmp = 0;
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

int	child_process_in(t_data *data, int i)
{
	int			verif;
	int			token;

	verif = 0;
	if (i % 2 == 0)
		token = 0;
	else if (i % 2 == 1)
		token = 1;
	if (i == 0 || i == data->n_cmds -1)
	{
		if (child_process_in_or_out(data, i, token) == -1)
			return (free_all_pipe(data->pipefd), -1);
	}
	else if (token == 0 || token == 1)
	{
		if (child_process_middle(data, token, verif) == -1)
			return (free_all_pipe(data->pipefd), -1);
	}
	free(data->pipefd[0]);
	free(data->pipefd[1]);
	return (0);
}

// if (redirection_manager(pipefd, token, data, i) == -1)
// 	return (NULL);

int	child_process_in_or_out(t_data *data, int i, int token)
{
	int	verif;

	if (i == 0)
	{
		close(data->pipefd[0][0]);
		close(data->pipefd[1][0]);
		close(data->pipefd[1][1]);
		if (check_dup(0, 0, data->pipefd[0][1]) == -1)
			return (-1);
		close(data->pipefd[0][1]);
	}
	else if (i == data->n_cmds - 1)
	{
		close(data->pipefd[1][1]);
		close(data->pipefd[0][1]);
		if (token == 0)
			verif = check_dup(data->pipefd[1][0], 1, 0);
		else
			verif = check_dup(data->pipefd[0][0], 1, 0);
		close(data->pipefd[1][0]);
		close(data->pipefd[0][0]);
		if (verif == -1)
			return (-1);
	}
	return (0);
}

// ATTENTION ICI VERIF N'EST PAS BON
int	child_process_middle(t_data *data, int token, int verif)
{
	if (token == 0)
	{
		close(data->pipefd[1][1]);
		close(data->pipefd[0][0]);
		verif = check_dup(data->pipefd[1][0], 2, data->pipefd[0][1]);
		close(data->pipefd[1][0]);
		close(data->pipefd[0][1]);
		if (verif == -1)
			return (-1);
	}
	else if (token == 1)
	{
		close(data->pipefd[0][1]);
		close(data->pipefd[1][0]);
		verif = check_dup(data->pipefd[0][0], 2, data->pipefd[1][1]);
		close(data->pipefd[0][0]);
		close(data->pipefd[1][1]);
		if (verif == -1)
			return (-1);
	}
	return (0);
}
