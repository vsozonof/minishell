/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:09:52 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/28 20:30:31 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipe(int **pipefd)
{
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][1]);
	close(pipefd[1][0]);
}

int	len_db_tab(char **str)
{
	int		j;

	j = 0;
	while (str[j])
		j++;
	return (j);
}

/*
void	close_all_pipe(int **pipefd)
{
	int	i;

	i = 0;
	while (i < data->n_args)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}
*/