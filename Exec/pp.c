/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:11:05 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/22 13:17:12 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex(char *argv[], char *env[], int argc)
{
	pid_t		pid[argc];
	int			**pipefd;
	int			i;
	char		**cmd_argument;
	char		*cmd;
	int			c;

	i = ((c = 0));
	pipefd = NULL;
	pipefd = alloc_pipe(i, pipefd);
	if (!pipefd[1] || !pipefd[0])
		return (free(pipefd), -1);
	while (i < argc)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("erreur de fork\n"), 1);
		if (pid[i] == 0)
		{
			if (i % 2 == 0)
				cmd = child_process_in(pipefd, argv, env, i, argc, 0);
			else
				cmd = child_process_in(pipefd, argv, env, i, argc, 1);
			if (cmd == NULL)
			{
				free_pipe_argv(pipefd, argv);
				exit(0);
			}
			else
			{
				cmd_argument = ft_split(argv[i], ' ');
				execve(cmd, cmd_argument, env);
				close(pipefd[0][1]);
				close(pipefd[0][0]);
				close(pipefd[1][0]);
				close(pipefd[1][1]);
				free(pipefd[0]);
				free(pipefd[1]);
				free(pipefd);
				exit(0);
			}
		}
		else
			pipefd = parent_process(pipefd, i);
		i++;
	}
	i = 0;
	while (i < argc)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	close(pipefd[0][1]);
	close(pipefd[0][0]);
	close(pipefd[1][0]);
	close(pipefd[1][1]);
	free(pipefd[0]);
	free(pipefd[1]);
	free(pipefd);
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
