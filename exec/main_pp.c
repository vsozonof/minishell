/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:10:50 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/06 15:36:29 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex_exec(t_data	*data)
{
	char	*buf;
	int		i;

	i = 0;
	data->index_redirs = 0;
	fprintf(stderr, "je passe par multi\n");
	// fprintf(stderr, "je test la commande complete sans redirection\n");
	// int		j = 0;
	// while (data->redir_tab[j])
	// {
	// 	fprintf(stderr, "voici mon pipe cpmplet %s \n", data->redir_tab[j]);
	// 	j++;
	// }
	fprintf(stderr, "\n\n\n\n");
	data->actual_path = malloc(sizeof(char *) * (len_db_tab(data->cmds) + 1));
	if (!data->actual_path)
		return (0);
	while (data->cmds[i])
	{
		data->actual_path[i] = malloc(sizeof(char) * (ft_strlen(data->cmds[i]) + 1));
		if (!data->actual_path[i])
			return (0);
		buf = arg(data->cmds[i], data);
		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
		if (!data->actual_path[i])
		{
			perror("wrong commd\n");
			free(buf);
			// ft_freedb(data->cmds);
			return (0);
		}
		free(buf);
		i++;
	}
	ft_pipex(data);
	waitpid(-1, NULL, 0);
	return (0);
}
// (juste avant le return ft_freedb(data->cmds); 
// a voir par rapport a mes free
