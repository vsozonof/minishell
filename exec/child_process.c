/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:55:54 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 10:07:06 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function takes as parameter: 
**
**	cmd: the structure who contains all utils
**	pipefd: the int who contains my pipes
**	i: an int i used to know if i am odd or even
** =====================================================
** =====================================================
**
**	this function will go to ft_pipex_helper_dup to
**	perform the dup2.
**	check if the command is a builtin.
**	check if my command is valid.
**	execute my command.
**
*/

int	child_process(t_data *data, int **pipefd, int i, t_cmd *cmd)
{
	int		*file;

	file = NULL;
	if (ft_pipex_helper_dup(data, pipefd, i) == -1)
	{
		free_problem(data, NULL, NULL);
		return (-1);
	}
	if (data->n_redirs > 0)
	{
		file = redirection_create(cmd, data);
		if (!file)
			return (-1);
	}
	if (builtin_single(cmd, data, file) == -1)
		return (-1);
	if (child_process_helper(data, cmd, file) == -1)
		return (-1);
	// cree un if qui contiens checker de builtin
	return (0);
}

int	child_process_helper(t_data *data, t_cmd *cmd, int *file)
{
	char	*cmd_arg;
	int		error;
	
	cmd_arg = ft_do_process(cmd->env, cmd->cmd);
	if (!cmd_arg)
	{
		free_problem(data, file, cmd);
		return (-1);
	}
	error = execve(cmd_arg, cmd->param, cmd->env);
	if (error == -1)
		fprintf(stderr, "could not execute the command\n");
	free_problem(data, file, cmd);
	return (-1);
}

int	ft_pipex_helper_dup(t_data *data, int **pipefd, int i)
{
	int		check;

	check = 0;
	check = child_process_in(pipefd, data, i);
	if (check == -1)
		return (-1);
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
