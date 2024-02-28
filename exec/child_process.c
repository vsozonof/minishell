/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:55:54 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/28 02:47:50 by tpotilli         ###   ########.fr       */
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

int	child_process(t_data *data, t_cmd *cmd, int *file)
{
	if (ft_pipex_helper_dup(data, data->i) == -1)
		return (free_problem(data, NULL, cmd), -1);
	if (data->n_redirs > 0)
	{
		file = redirection_create(cmd, data, file);
		if (!file)
		{
			free(data->pipefd);
			free_problem(data, file, cmd);
			exit(1);
		}
	}
	if (cmd->cmd == NULL
		|| ft_strlen(cmd->cmd) == 0)
	{
		if (len_list(cmd->redirs) > 0)
		{
			free(data->pipefd);
			free_problem(data, file, cmd);
		}
		set_status(data, 0, "Command not found\n", cmd->cmd);
		data->i_status = 127;
		free(data->pipefd);
		free_problem(data, NULL, cmd);
	}
	builtin_multi(cmd, data, file);
	if (child_process_helper(data, cmd, file) == -1)
		return (-1);
	return (0);
}

int	child_process_helper(t_data *data, t_cmd *cmd, int *file)
{
	char				*cmd_arg;
	struct sigaction	sa;

	cmd_arg = ft_do_process(cmd->env, cmd->cmd, data);
	if (!cmd_arg)
	{
		free(data->pipefd);
		free_problem(data, file, cmd);
	}
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	execve(cmd_arg, cmd->param, cmd->env);
	free_problem(data, file, cmd);
	free(cmd_arg);
	free(data->pipefd);
	exit(1);
	return (-1);
}

int	ft_pipex_helper_dup(t_data *data, int i)
{
	int		check;

	check = child_process_in(data, i);
	if (check == -1)
		return (-1);
	return (0);
}
