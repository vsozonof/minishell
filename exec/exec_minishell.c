/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:43:04 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 15:14:39 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// n_redires = len du tab
// tab = redirection/here_doc
// retirer des initialisation

int	ft_pipex(t_cmd *cmd)
{
	pid_t		*pid;
	int			**pipefd;

	pid = malloc(sizeof(pid_t) *cmd->n_cmd); //voir comment free le pid dans un child
	if (!pid)
		return (fprintf(stderr, "problem with malloc\n"), -1);
	pipefd = alloc_pipe();
	if (!pipefd || !pipefd[1] || !pipefd[0])
		return (free(pid), free(pipefd), -1);
	ft_pipex_helper(cmd, pid, pipefd);
	wait_and_free(cmd, pipefd, pid);
	return (0);
}

int	ft_pipex_helper(t_cmd *cmd, int *pid, int **pipefd)
{
	int		i;

	i = 0;
	while (cmd) // liste chainee
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("erreur de fork\n"), 1);
		if (pid[i] == 0)
		{
			if (child_process(cmd, pipefd, i) == -1)
				fprintf(stderr, "il y a une erreur dans le child\n");
				// pour le moment ne rien faire
		}
		else
		{
			pipefd = parent_process(pipefd, i);
			// fprintf(stderr, "je suis dans le parent (test de retour d'erreur)\n");
			// get_and_print_statuscode();
		}
		i++;
		cmd = cmd->next;
	}
	return (0);
}

// /*
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
// */

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
