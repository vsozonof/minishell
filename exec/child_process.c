/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:55:54 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 13:10:29 by tpotilli         ###   ########.fr       */
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

int	child_process(t_data *data, t_cmd *cmd)
{
	int		*file;

	file = NULL;
	if (ft_pipex_helper_dup(data, data->i) == -1)
	{
		free_problem(data, NULL, NULL);
		return (-1);
	}
	if (data->n_redirs > 0)
	{
		file = redirection_create(cmd, data);
		if (!file)
		{
			fprintf(stderr, "je free les redir\n");
			exit(0);
		}
	}
	if (data->exec->cmd == NULL)
		free_problem(data, NULL, NULL); // voir pour free pipefd pour ce cas particulier
	if (builtin_multi(cmd, data, file) == -1)
		return (-1);
	if (child_process_helper(data, cmd, file) == -1)
		return (-1);
	// cree un if qui contiens checker de builtin
	return (0);
}

int	child_process_helper(t_data *data, t_cmd *cmd, int *file)
{
	char	*cmd_arg;
	struct sigaction    sa;
	
	cmd_arg = ft_do_process(cmd->env, cmd->cmd, data);
	if (!cmd_arg)
	{
		free(data->pipefd);
		free_problem(data, file, cmd);
		return (-1);
	}
	cmd = data->exec;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	execve(cmd_arg, cmd->param, cmd->env);
	free_problem(data, file, cmd);
	free(cmd_arg);
	free(data->pipefd);
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
