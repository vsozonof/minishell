/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:55:54 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/25 19:28:32 by tpotilli         ###   ########.fr       */
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
	char	*cmd_arg;
	int		error;
	int		*file;

	if (ft_pipex_helper_dup(data, pipefd, i) == -1)
		free_problem(data, NULL);
	if (data->n_redirs > 0)
		file = redirection_create(cmd, data);
	builtin_single(cmd, data, file);
	// cree un if qui contiens checker de builtin
	cmd_arg = ft_do_process(cmd->env, cmd->cmd);
	if (!cmd_arg)
		free_problem(data, file);
	error = execve(cmd_arg, cmd->param, cmd->env);
	if (error == -1)
		fprintf(stderr, "could not execute the command\n");
	free_problem(data, file);
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
