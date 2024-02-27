/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:43:04 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 23:47:26 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// n_redires = len du tab
// tab = redirection/here_doc
// retirer des initialisation

int	ft_pipex(t_data *data)
{
	int			i;
	char		*cmd;

	i = ((data->i = 0));
	data->pipefd = NULL;
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		return (write(2, "problem with malloc\n", 21), -1);
	data->pipefd = alloc_pipe();
	if (!data->pipefd)
		return (free_pipe_begin(data, 0), -1);
	if (!data->pipefd[1])
		return (free_pipe_begin(data, 1), -1);
	if (!data->pipefd[0])
		return (free_pipe_begin(data, 2), -1);
	cmd = ft_pipex_helper(data, i);
	i = wait_and_free(data);
	return (i);
}

void	free_pipe_begin(t_data *data, int token)
{
	write(2, "problem with malloc\n", 21);
	if (token == 0)
	{
		free(data->pid);
		free(data->pipefd);
	}
	else if (token == 1)
	{
		close(data->pipefd[0][0]);
		close(data->pipefd[0][1]);
		free(data->pipefd[0]);
		free(data->pipefd[1]);
		free(data->pid);
		free(data->pipefd);
	}
	else if (token == 2)
	{
		close(data->pipefd[1][0]);
		close(data->pipefd[1][1]);
		free(data->pipefd[0]);
		free(data->pipefd[1]);
		free(data->pid);
		free(data->pipefd);
	}
}

char	*ft_pipex_helper(t_data *data, int i)
{
	t_cmd				*cmd;
	struct sigaction	sa;

	cmd = data->exec;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = &handle_signals;
	sigaction(SIGQUIT, &sa, NULL);
	while (cmd)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (printf("erreur de fork\n"), NULL);
		if (data->pid[i] == 0)
			child_process(data, cmd);
		else
			data->pipefd = parent_process(data, i);
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

int	**parent_process(t_data *data, int i)
{
	if (i % 2 == 0)
	{
		if (!data->pipefd[0] || !data->pipefd[1])
		{
			free(data->pipefd[0]);
			return (free(data->pipefd[1]), free(data->pipefd), NULL);
		}
		close(data->pipefd[1][1]);
		close(data->pipefd[1][0]);
		pipe(data->pipefd[1]);
	}
	else
	{
		if (!data->pipefd[0] || !data->pipefd[1])
		{
			free(data->pipefd[0]);
			return (free(data->pipefd[1]), free(data->pipefd), NULL);
		}
		close(data->pipefd[0][0]);
		close(data->pipefd[0][1]);
		pipe(data->pipefd[0]);
	}
	return (data->pipefd);
}
