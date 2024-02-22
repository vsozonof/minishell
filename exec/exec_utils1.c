/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:28:28 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 08:57:47 by tpotilli         ###   ########.fr       */
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
		return (printf("problem with fd\n"), -1);
	return (fd);
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

// int	**alloc_pipe()
// {
// 	int		**pipefd;
// 	int		i;

// 	i = 0;
// 	pipefd = NULL;
// 	if (i == 0)
// 	{
// 		pipefd = malloc(sizeof(int *) * 2);
// 		if (!pipefd)
// 			return (fprintf(stderr, "probleme happend in alloc_pipe\n"), NULL);
// 		pipefd[0] = malloc(sizeof(int) * 2);
// 		pipefd[1] = malloc(sizeof(int) * 2);
// 		if (!pipefd[0] || !pipefd[1])
// 		{
// 			free(pipefd[0]);
// 			free(pipefd[1]);
// 			return (fprintf(stderr, "problem when creating the pipe"), NULL);
// 		}
// 		pipe(pipefd[0]);
// 		pipe(pipefd[1]);
// 	}
// 	return (pipefd);
// }
