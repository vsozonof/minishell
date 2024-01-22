/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:10:29 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/22 13:17:36 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dup(int pipe, int token, int pipe2)
{
	if (token == 0)
	{
		if (dup2(STDIN_FILENO, STDIN_FILENO) < 0)
			return (printf("problem with dup2 1"), -1);
		if (dup2(pipe2, 1) < 0)
			return (printf("problem with dup2 2"), -1);
	}
	else if (token == 1)
	{
		if (dup2(pipe, 0) < 0)
			return (printf("problem with dup2 3"), -1);
		if (dup2(STDOUT_FILENO, 1) < 0)
			return (printf("problem with dup2 4"), -1);
		// close(pipe);
			// return (free(pipesfd[0]), free(pipesfd[1]), free(pipesfd), printf("problem with dup2"), -1);
	}
	else if (token == 2)
	{
		if (dup2(pipe, 0) < 0)
			return (printf("problem with dup2 5"), -1);
		if (dup2(pipe2, 1) < 0)
			return (printf("problem with dup2 6"), -1);
	}
	return (0);
}
// regler le probleme des fd
char	*child_process_in(int **pipefd, char **argv, char **env, int i, int argc, int token)
{
	char		*cmd;
	char		**buf;
	int			verif;

	if (i == 0)
	{
		close(pipefd[0][0]);
		close(pipefd[1][0]);
		close(pipefd[1][1]);
		verif = check_dup(0, 0, pipefd[0][1]);
		close(pipefd[0][1]);
		if (verif == -1)
			return (free_pipe_argv(pipefd, argv), NULL);
	}
	else if (i == argc - 1)
	{
		close(pipefd[1][1]);
		close(pipefd[0][1]);
		if (token == 0)
			verif = check_dup(pipefd[1][0], 1, 0);
		else
			verif = check_dup(pipefd[0][0], 1, 0);
		close(pipefd[1][0]);
		close(pipefd[0][0]);
		if (verif == -1)
			return (free_pipe_argv(pipefd, argv), NULL);
	}
	else if (token == 0)
	{
		close(pipefd[1][1]);
		close(pipefd[0][0]);
		verif = check_dup(pipefd[1][0], 2, pipefd[0][1]);
		close(pipefd[1][0]);
		close(pipefd[0][1]);
		if (verif == -1)
			return (free_pipe_argv(pipefd, argv), NULL);
	}
	else if (token == 1)
	{
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		verif = check_dup(pipefd[0][0], 2, pipefd[1][1]);
		close(pipefd[0][0]);
		close(pipefd[1][1]);
		if (verif == -1)
			return (free_pipe_argv(pipefd, argv), NULL);
	}
	buf = arg(argv[i]);
	cmd = ft_do_process(env, buf[0], pipefd, i);
	if (cmd == NULL)
		return (free_pipe_argv(pipefd, argv), NULL);
	free(pipefd[0]);
	free(pipefd[1]);
	return (cmd);
}

char	**arg(char *str)
{
	char	**buf;

	buf = ft_split(str, ' ');
	return (buf);
}
