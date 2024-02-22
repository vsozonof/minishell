/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters-2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:43:45 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 15:40:31 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_node_len(t_cmd *lst)
{
	size_t	i;
	t_cmd	*nav;

	i = 0;
	nav = lst;
	while (nav)
	{
		nav = nav->next;
		i++;
	}
	return (i);
}

int	get_n_redir(t_cmd *lst)
{
	size_t	i;
	t_cmd	*nav;
	t_redir	*nav2;

	i = 0;
	nav = lst;
	while (nav)
	{
		nav2 = nav->redirs;
		while (nav2)
		{
			i++;
			nav2 = nav2->next;
		}
		nav = nav->next;
	}
	return (i);
}