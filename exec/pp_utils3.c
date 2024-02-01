/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:26 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/31 16:43:17 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_redirs_ac(t_data *data)
{
	int		nb;
	int		j;

	nb = ((j = 0));
	while (data->cmds[data->index_redirs][j])
	{
		if (data->cmds[data->index_redirs][j] == '>'
			|| data->cmds[data->index_redirs][j] == '<')
			nb++;
		j++;
	}
	return (nb);
}
