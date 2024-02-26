/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:28:28 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 10:00:15 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function takes as parameter: 
**
**	argv = the name of the file
**	flag = the option for open
**	
** =====================================================
** =====================================================
**
**	this function will open a file wth the option in flag
**
*/

int	ft_create_fd(char	*argv, int flag)
{
	int	fd;

	fd = open(argv, flag, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

long	len_list(t_redir *redir)
{
	long	len;

	len = 0;
	while (redir)
	{
		len++;
		redir = redir->next;
	}
	return (len);
}

void	wait_and_free(t_data *data, int **pipefd, int *pid)
{
	int	i;

	i = 0;
	while (i < data->n_cmds)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free_all_pipe(pipefd);
	// free_all_fd();
	free(pid);
}

void	free_all_pipe(int **pipefd)
{
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][1]);
	close(pipefd[1][0]);
	free(pipefd[1]);
	free(pipefd[0]);
	free(pipefd);
}

// void	free_all_fd(t_data *data)
// {
// 	t_cmd	*ptr;
// 	int		j;

// 	ptr = cmd;
// 	while (ptr)
// 	{
// 		j = 0;
// 		while (j < ptr->n_redirs)
// 		{
// 			close(ptr->redirs->);
// 		}
// 		ptr = ptr->next;
// 	}
// }

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

int	**alloc_pipe()
{
	int		**pipefd;
	int		i;

	i = 0;
	pipefd = NULL;
	if (i == 0)
	{
		pipefd = malloc(sizeof(int *) * 2);
		if (!pipefd)
			return (fprintf(stderr, "probleme happend in alloc_pipe\n"), NULL);
		pipefd[0] = malloc(sizeof(int) * 2);
		pipefd[1] = malloc(sizeof(int) * 2);
		if (!pipefd[0] || !pipefd[1])
		{
			free(pipefd[0]);
			free(pipefd[1]);
			return (fprintf(stderr, "problem when creating the pipe"), NULL);
		}
		pipe(pipefd[0]);
		pipe(pipefd[1]);
	}
	return (pipefd);
}
