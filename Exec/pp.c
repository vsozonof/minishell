/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:11:05 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/25 11:06:14 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// n_redires = len du tab
// tab = redirection/here_doc
// retirer des initialisation
// 1 = simple quote vers la gauche
// 2 = droite
// 3 = db_gauche
// 4 = droite

int	ft_pipex(t_data	*data)
{
	pid_t		pid[data->n_cmds];
	int			**pipefd;
	int			i;
	char		**cmd_argument;
	char		*cmd;

	i = 0;
	pipefd = NULL;
	cmd = NULL;
	pipefd = alloc_pipe(i, pipefd);
	if (!pipefd[1] || !pipefd[0])
		return (free(pipefd), -1);
	while (i < data->n_cmds)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("erreur de fork\n"), 1);
		if (pid[i] == 0)
		{
			// if (data->n_redirs >= 1)
			// 	cmd = redirection_here_manager(data, pipefd, i);
			if (i % 2 == 0)
				cmd = child_process_in(pipefd, data, i, 0);
			else if (i % 2 == 1)
				cmd = child_process_in(pipefd, data, i, 1);
			fprintf(stderr, "cmd = %s\n", cmd);
			if (cmd == NULL)
			{
				free_pipe_argv(pipefd, data->cmds);
				exit(0);
			}
			else
			{
				cmd_argument = ft_split(data->cmds[i], ' ');
				execve(cmd, cmd_argument, data->pr->nv);
				free_pipe_argv(pipefd, data->cmds);
				exit(0);
			}
		}
		else
			pipefd = parent_process(pipefd, i);
		i++;
	}
	i = 0;
	while (i < data->n_cmds)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free_pipe_argv(pipefd, data->cmds);
	return (0);
}

int	**alloc_pipe(int i, int **pipefd)
{
	if (i == 0)
	{
		pipefd = malloc(sizeof(int *) * 2);
		if (!pipefd)
			return (fprintf(stderr, "probleme happend in alloc_pipe"), NULL);
		pipefd[0] = malloc(sizeof(int) * 2);
		pipefd[1] = malloc(sizeof(int) * 2);
		if (!pipefd[0] || !pipefd[1])
		{
			free(pipefd[0]);
			free(pipefd[1]);
			return (pipefd);
		}
		pipe(pipefd[0]);
		pipe(pipefd[1]);
	}
	return (pipefd);
}

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
