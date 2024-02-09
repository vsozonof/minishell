/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:10:46 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/08 15:07:22 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirection_dup1_in(t_data *data, int first, int last)
{
	int		i;

	i = 0;
	fprintf(stderr, "dans ma redirection mon first %d et end %d\n", first, last);
	if (first == -1 && dup2(0, 0) < 0)
		return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
	else
	{
		if (dup2(data->tab[first][2], 0) < 0)
			return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
	}
	if (redirection_dup1_out(data, last, i) == -1)
		return (-1);
	return (0);
}

int	redirection_dup1_out(t_data *data, int last, int i)
{
	if (last == -1)
	{
		if (dup2(0, 1) < 0)
			return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
	}
	else
	{
		if (dup2(data->tab[last][2], 1) < 0)
			return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
	}
	while (data->n_redirs > i)
	{
		close(data->tab[i][2]);
		i++;
	}
	return (0);
}

int redirection_dup_2(t_data *data, int first, int last)
{
	(void)first;
	(void)last;
	if (data->n_redirs == 1)
	{
		// if (redirection_here_doc(data, data->input) == 1)
		// {
		// 	file = main_here_doc(data);
		// 	fprintf(stderr, "j'ai detecter un here_doc\n");
		// 	path = ft_do_here_doc(data);
		// 	file = ft_create_fd(path, O_WRONLY | O_CREAT | O_TRUNC);
		// 	if (dup2(file, 0) < 0)
		// 		return (close(file), unlink(ft_itoa(file)), printf("problem with dup2 1"), -1);
		// 	close(file);
		// 	unlink(ft_itoa(file));
		// }
		// mettre le if en dessous en else if
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

// {
// 	int		i;
// 	(void)data;

// 	i = 0;
// 	while (input[i] && input[i + 1])
// 	{
// 		if (input[i] == '<' && input[i + 1] == '<')
// 			return (1);
// 		i++;
// 	}
// 	return (-1);
// }
