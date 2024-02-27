/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:48:51 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 23:25:48 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*creating_file(t_redir *nav, t_data *data, t_cmd *cmd)
{
	int	*file_tab;
	int	i;

	i = 0;
	file_tab = malloc(sizeof(int) * len_list(nav));
	if (!file_tab)
	{
		write(2, "a problem append with a malloc\n", 32);
		free_problem(data, NULL, cmd);
		return (NULL);
	}
	while (i < len_list(nav))
	{
		file_tab[i] = -1;
		i++;
	}
	return (file_tab);
}
