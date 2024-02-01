/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_single.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:10:46 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/01 17:22:05 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirection_single_1(t_data *data, int first, int last, int verif)
{
	(void)verif;
	if (data->n_redirs > 1)
	{
		if (first == -1)
		{
			if (dup2(0, 0) < 0)
				return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
		}
		else
		{
			if (dup2(data->tab[first][2], 0) < 0)
				return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
		}
		if (dup2(data->tab[last][2], 1) < 0)
			return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
		close(data->tab[0][2]);
		close(data->tab[1][2]);
		// close(data->tab[last][2]);
	}
	return (0);
}

int redirection_single_2(t_data *data, int first, int last, int verif)
{
	(void)verif;
	(void)first;
	(void)last;
	if (data->n_redirs == 1)
	{
		if (redirection_single_chev(data, data->input) == 0)
		{
			if (dup2(data->tab[0][2], 0) < 0)
				return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
		}
		else if (redirection_single_chev(data, data->input) == 1)
		{
			if (dup2(data->tab[0][2], 1) < 0)
				return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
		}
			close(data->tab[0][2]);
		fprintf(stderr, "je sors\n");
	}
	return (0);
}
