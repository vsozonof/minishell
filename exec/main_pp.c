/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:10:50 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/27 03:53:33 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex_exec(t_data	*data)
{
	char	*buf;
	char	*fre;
	int		i;

	i = 0;
	data->index_redirs = 0;
	while (data->cmds[i])
	{
		buf = arg(data->cmds[i], data);
		fre = ft_do_process(data->pr->nv, buf);
		if (!fre)
		{
			perror("wrong commd\n");
			free(buf);
			ft_freedb(data->cmds);
			return (0);
		}
		free(buf);
		free(fre);
		i++;
	}
	ft_pipex(data);
	waitpid(-1, NULL, 0);
	return (0);
}
// (juste avant le return ft_freedb(data->cmds); 
// a voir par rapport a mes free
