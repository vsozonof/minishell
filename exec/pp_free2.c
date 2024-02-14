/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:14:34 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/14 16:37:38 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_all_fd(data);
	free(pid);
}
