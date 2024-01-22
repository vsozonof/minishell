/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:12:21 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/22 15:49:02 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *str_join_free(char *path, char *cmd)
{
	char *str;
	
	str = ft_strjoin(path, cmd);
	free(path);
	return (str);
}

void	ft_freedb(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_pipe_argv(int **pipefd, char *argv[])
{
	(void)argv;
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][1]);
	close(pipefd[1][0]);
	free(pipefd[1]);
	free(pipefd[0]);
	free(pipefd);
	// ft_freedb(argv);
}
