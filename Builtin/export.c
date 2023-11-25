/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:49:13 by tpotilli          #+#    #+#             */
/*   Updated: 2023/11/25 15:38:04 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_export(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->envp[i])
		i++;
	while (data->input)
	{
		data->envp[i][j] = data->input[j];
		j++;
	}
}
