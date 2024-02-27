/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:43:04 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 09:23:30 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// n_redires = len du tab
// tab = redirection/here_doc
// retirer des initialisation

int	ft_pipex(t_data *data)
{
	int			**pipefd;
	int			i;
	char		*cmd;
	pid_t		*pid;

	i = ((data->i = 0));
	pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!pid)
		return (write(2, "problem with malloc\n", 21), -1);
	pipefd = alloc_pipe();
	if (!pipefd)
		return (write(2, "problem with malloc\n", 21), free(pid), free(pipefd), -1);
	else if (!pipefd[1])
		return (write(2, "problem with malloc\n", 21), free(pid), free(pipefd), free(pipefd[0]), -1);
	else if (!pipefd[0])
		return (write(2, "problem with malloc\n", 21), free(pid), free(pipefd), free(pipefd[1]), -1);
	cmd = ft_pipex_helper(data, pipefd, i, pid);
	wait_and_free(data, pipefd, pid, cmd);
	return (0);
}

char	*ft_pipex_helper(t_data *data, int **pipefd, int i, pid_t *pid)
{
	t_cmd	*cmd;

	cmd = data->exec;
	while (cmd)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("erreur de fork\n"), NULL);
		if (pid[i] == 0)
			child_process(data, pipefd, cmd);
		else
			pipefd = parent_process(pipefd, i);
		i++;
		data->i = i;
		cmd = cmd->next;
	}
	return (0);
}

// **	This function takes as parameter: 
// **
// **	pipefd: an array of pipe
// **	i: to know where i am in pipe
// **	(if i am equal to 0 i'm pair)
// **
// ** =====================================================
// ** =====================================================
// **
// **	so we check i we are pair or not
// **	then we close our pipe and alloc it again
// **

int	**parent_process(int **pipefd, int i)
{
	if (i % 2 == 0)
	{
		if (!pipefd[0] || !pipefd[1])
			return (free(pipefd[0]), free(pipefd[1]), free(pipefd), NULL);
		close(pipefd[1][1]);
		close(pipefd[1][0]);
		pipe(pipefd[1]);
	}
	else
	{
		if (!pipefd[0] || !pipefd[1])
			return (free(pipefd[0]), free(pipefd[1]), free(pipefd), NULL);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		pipe(pipefd[0]);
	}
	return (pipefd);
}
