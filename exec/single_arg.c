/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:09:07 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 15:03:25 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_data *data)
{
	char	*comd;

	comd = NULL;
	exec_single(data, comd, data->exec);
	free(comd);
	return (0);
}

int	exec_single(t_data *data, char *comd, t_cmd *cmd)
{
	int		pid;
	int		*file;

	file = NULL;
	pid = fork();
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
		child_process_single(data, cmd, file, comd);
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}

int	child_process_single(t_data *data, t_cmd *cmd, int *file, char *comd)
{
	int	error;

	if (data->n_redirs > 0)
	{
		file = redirection_create(cmd, data);
		if (!file)
			exit(0);
	}
	if (data->exec->cmd == NULL)
	{
		free_problem(data, file, cmd);
		exit(0);
	}
	if (builtin_single(cmd, data, file) == -1)
		exit(data->i_status);
	comd = ft_do_process(data->exec->env, data->exec->cmd);
	if (!comd)
	{
		free_problem(data, file, cmd);
		exit(0);
	}
	error = execve(comd, data->exec->param, data->exec->env);
	if (error == -1)
		write(2, "could not execute the command\n", 31);
	free_problem(data, file, cmd);
	free(comd);
	exit(0);
	return (-1);
}
