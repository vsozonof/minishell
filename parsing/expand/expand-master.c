/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand-master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:31:51 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 21:09:05 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_nodes(t_input *inp, t_data *data)
{
	t_input	*nav;
	int		i;

	i = 0;
	nav = inp;
	while (nav)
	{
		ft_printlst(inp);
		data->input = nav->str;
		reg_expander(data, 0);
		nav->str = ft_strdup(data->input);
		if (!nav->str)
		{
			nav = nav->next;
			free_at_pos(inp, i);
			if (!nav)
				return (0);
		}
		else
			nav = nav->next;
		i++;
	}
	return (1);
}
