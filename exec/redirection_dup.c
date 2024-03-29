/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:10:46 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/16 08:36:22 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_dup1_in(t_data *data, int first, int last)
{
	fprintf(stderr, "dans ma redirection mon first %d et end %d\n", first, last);
	if (first == -1)
	{
		first++;
		// if (dup2(0, 0) < 0)
		// {
		// 	close(data->tab[data->index_redirs][2]);
		// 	return (printf("problem with dup2 1"), -1);
		// }
	}
	else
	{
		if (dup2(data->tab[first][2], 0) < 0)
		{
			close(data->tab[first][2]);
			return (printf("problem with dup2 1"), -1);
		}
	}
	if (redirection_dup1_helper(data, last) == -1)
		return (-1);
	return (0);
}

int redirection_dup1_helper(t_data *data, int last)
{
	int		i;

	i = 0;
	if (last == -1)
		last++;
	else
	{
		if (dup2(data->tab[last][2], 1) < 0)
		{
			close(data->tab[data->index_redirs][2]);
			return (printf("problem with dup2 1"), -1);
		}
	}
	while (data->n_redirs > i)
	{
		close(data->tab[i][2]);
		i++;
	}
	return (0);
}
