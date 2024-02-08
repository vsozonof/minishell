/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:11:05 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/08 10:00:09 by tpotilli         ###   ########.fr       */
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

int	ft_pipex(t_data	*data, int i, char **cmd_argument)
{
	pid_t		pid[data->n_cmds];
	int			**pipefd;

	pipefd = alloc_pipe(i);
	if (!pipefd[1] || !pipefd[0])
		return (free(pipefd), -1);
	fprintf(stderr, "============DEBUT DE PP\n============");
	while (i < data->n_cmds)
	{
		fprintf(stderr, "JE SUIS A MA %d\n", i);
		fprintf(stderr, "mon input = %s\n", data->cmds[i]);
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("erreur de fork\n"), 1);
		if (pid[i] == 0)
			child_process(data, pipefd, i, cmd_argument);
		else
			pipefd = parent_process(pipefd, i);
		i++;
		data->i = i;
	}
	wait_and_free(data, pipefd, pid);
	return (0);
}



/*
**	This function takes as parameter: 
**
**	pipefd: an array of pipe
**	i: to know where i am in pipe
**	(if i am equal to 0 i'm pair)
**
** =====================================================
** =====================================================
**
**	this function will allocate two array of pipe
**
*/

/*
**	This function takes as parameter: 
**
**	pipefd: an array of pipe
**	i: to know where i am in pipe
**	(if i am equal to 0 i'm pair)
**
** =====================================================
** =====================================================
**
**	this function will allocate two array of pipe
**
*/

int	**alloc_pipe(int i)
{
	int		**pipefd;

	pipefd = NULL;
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

/*
**	This function takes as parameter: 
**
**	pipefd: an array of pipe
**	i: to know where i am in pipe
**	(if i am equal to 0 i'm pair)
**
** =====================================================
** =====================================================
**
**	so we check i we are pair or not
**	then we close our pipe and alloc it again
**
*/

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


/*

int	ft_pipex(t_data	*data, int i, char **cmd_argument, char *cmd_arg)
{
	pid_t		pid[data->n_cmds];
	int			**pipefd;

	pipefd = alloc_pipe(i);
	if (!pipefd[1] || !pipefd[0])
		return (free(pipefd), -1);
	fprintf(stderr, "============DEBUT DE PP\n============");
	while (i < data->n_cmds)
	{
		fprintf(stderr, "JE SUIS A MA %d\n", i);
		fprintf(stderr, "mon input = %s\n", data->cmds[i]);
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("erreur de fork\n"), 1);
		if (pid[i] == 0)
		{
			ft_pipex_helper(data pipefd, i);
			if (i % 2 == 0)
				child_process_in(pipefd, data, i, 0);
			else if (i % 2 == 1)
				child_process_in(pipefd, data, i, 1);
			if (check_redirection_now(data, i) == 0)
				cmd_arg = data->redir_tab[i];
			else
				cmd_arg = data->cmds[i];
			fprintf(stderr, "all_cmd = %s\n", cmd_arg);
			cmd_argument = ft_split(cmd_arg, ' ');
			int q = 0;
			while (data->actual_path[q])
			{
				fprintf(stderr, "data->actual_path[%d] = %s\n", q, data->actual_path[q]);
				q++;
			}
			q = 0;
			if (data->n_redirs > 0)
			{
				while (data->redir_tab[q])
				{
					fprintf(stderr, "data->aredir_tab[%d] = %s\n", q, data->redir_tab[q]);
					q++;
				}
			}
			fprintf(stderr, "juste avant mon execve mon i = %d et path %s\n", i, data->actual_path[i]);
			execve(data->actual_path[i], cmd_argument, data->pr->nv);
			free_all_pipe(pipefd);
			exit(0);
		}
		else
			pipefd = parent_process(pipefd, i);
		i++;
		data->i = i;
	}
	wait_and_free(data, pipefd, pid);
	return (0);
}
*/