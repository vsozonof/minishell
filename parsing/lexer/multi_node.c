/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:15:28 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 11:02:23 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multi_node_handler(t_data *data, int i)
{
	char	***tab;

	data->inp->cmds = pipes_splitter(data->input, '|', data);
	if (!data->inp->cmds)
		return ;
	tab = malloc(sizeof(char **) * (data->n_cmds + 1));
	if (!tab)
		return ;
	while (data->inp->cmds[i])
	{
		free(data->input);
		data->input = data->inp->cmds[i];
		tab[i] = input_to_lst(data);
		i++;
	}
	tab[i] = NULL;
	data->multi_inp = alloc_struct(data->multi_inp, (data->n_cmds + 1));
	if (!data->multi_inp)
		return ;
	multi_input_to_lst(data->multi_inp, tab, 0, 0);
	i = -1;
	while (data->multi_inp[++i])
		identify_nodes(data->multi_inp[i]);
	multi_node_formatting(data->pr->multi_inp, data);
}

int	multi_input_to_lst(t_input **ptr, char ***tab, int i, int n)
{
	t_input	*nav;

	while (ptr[i])
	{
		nav = ptr[i];
		while (tab[i][n])
		{
			nav->str = ft_strdup(tab[i][n]);
			if (tab[i][n + 1])
			{
				nav->next = malloc(sizeof(t_input));
				if (!nav->next)
					return (0);
				nav = nav->next;
			}
			else
				nav->next = NULL;
			n++;
		}
		n = 0;
		i++;
	}
	return (1);
}

void	multi_node_formatting(t_input **inp, t_data *data)
{
	
}
