/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:55:54 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 08:59:54 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(t_cmd *cmd, int **pipefd)
{
	char	*cmd_arg;
	int		error;

	if (ft_pipex_helper_dup(cmd, pipefd) == -1)
	{
		//faire des free
		return (-1);
	}
	if (builtin_checker(cmd->cmds[i]) > 0)
	{
		builtin_multi(cmd);
		builtin_manager(cmd, builtin_checker(cmd->cmds[i]));
		free_multi_struct_and_arg(cmd, cmd_argument, pipefd);
		return (-1);
	}
	// if (cmd->cmd_valid == -1)
	// {
	// 	cmd_not_valid(cmd);
	// 	exit(cmd->status_code);
	// }
	// cree un if qui contiens checker de builtin
	int j = 0;
	fprintf(stderr, "ACTUAL PATH %s\n", cmd->actual_path[i]);
	while (cmd_argument[j])
	{
		fprintf(stderr, "ARG COMPLETE = %s\n", cmd_argument[j]);
		j++;
	}
	error = execve(cmd->actual_path[i], cmd_argument, cmd->pr->nv);
	if (error == -1)
		fprintf(stderr, "could not execute the command\n");
	free_manager(data, 2);
	free_end_of_program(data->pr);
	// free_all_pipe(pipefd);
	exit(2);
	return (-1);
}

int	ft_pipex_helper_dup(t_data *data, int **pipefd, int i)
{
	int		check;

	check = 0;
	if (i % 2 == 0)
		check = child_process_in(pipefd, cmd, 0);
	else if (i % 2 == 1)
		check = child_process_in(pipefd, cmd, 1);
	if (check == -1)
		return (-1);
	return (0);
}

int	builtin_multi(t_data *data)
{
	int	check;

	check = builtin_checker(data->input);
	if (check >= 1 && check <= 7)
	{
		if (data->n_redirs > 0)
		{
			data->first = malloc(sizeof(int) * 1);
			data->last = malloc(sizeof(int) * 1);
			data->first[0] = first_redirect(data, data->input, 0);
			data->last[0] = last_redirect(data, data->input, 0);
			redirection_dup1_in(data, data->first[0], data->last[0]);
		}
		builtin_manager(data, check);
		if (data->n_redirs > 0)
		{
			free(data->first);
			free(data->last);
		}
		return (-1);
	}
	return (0);
}

int		get_and_print_statuscode()
{
	int		wstatus;
	int		statusCode;

	wait(&wstatus);
	statusCode = -1;
	if (WIFEXITED(wstatus))
	{
		statusCode = WEXITSTATUS(wstatus);
		if (statusCode != 0)
			fprintf(stderr, "failure status code: %d\n", (statusCode + 155));
		statusCode = WIFSIGNALED(wstatus);
		if (statusCode != 0)
			fprintf(stderr, "failure with a signal is unknown %d\n", (statusCode + 155));
	}
	return (statusCode);
}
