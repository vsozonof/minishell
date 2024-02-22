/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:14:42 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 13:57:22 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_node_handler(t_data *data)
{
	char	**tab;
	t_cmd	*ptr;

	ptr = malloc(sizeof(t_cmd));
	if (!ptr)
		return ;
	data->exec = ptr;
	tab = input_to_lst(data);
	if (!tab)
		return (free_master(data));
	put_input_to_lst(data->inp, tab);
	identify_nodes(data->inp);
	format_node(ptr, data->inp, data); // j'ajoute data pour l'env	
}

int	put_input_to_lst(t_input *ptr, char **tab)
{
	int		i;
	t_input	*nav;

	i = 0;
	if (!tab)
		return (0);
	nav = ptr;
	while (tab[i])
	{
		nav->str = ft_strdup(tab[i]);
		if (tab[i + 1])
		{
			nav->next = malloc(sizeof(t_input));
			if (!nav->next)
				return (0);
			nav = nav->next;
		}
		else
			nav->next = NULL;
		i++;
	}
	ft_split_free(tab);
	return (1);
}