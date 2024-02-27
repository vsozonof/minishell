/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:28:28 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 23:49:18 by tpotilli         ###   ########.fr       */
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

long	len_cmd(t_cmd *cmd)
{
	long	len;

	len = 0;
	while (cmd)
	{
		len++;
		cmd = cmd->next;
	}
	return (len);
}

int	wait_and_free(t_data *data)
{
	int	i;
	int	cpt1;
	int	status;
	int	tmp;

	i = cpt1 = 0;
	while (42)
	{
		if (data->n_cmds == i)
			i = 0;
		if (waitpid(data->pid[i], &status , WNOHANG) > 0)
		{
			cpt1++;
			if (cpt1 == data->n_cmds - 1)
				tmp = status;
		}
		if (cpt1 == data->n_cmds)
			break ;
		i++;
	}
	return (tmp);
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
