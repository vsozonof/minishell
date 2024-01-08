/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 04:25:22 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/08 07:41:26 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data_struct(t_data *data)
{
	int		i;

	i = 0;
	while (data)
	{
		free(data->input);
		free(data->pr);
		free_data_envp(data, i);
		free_flags(data);
		data = data->next;
	}
}

void	free_data_envp(t_data *data, int i)
{
	while (data->envp[i])
	{
		free(data->envp[i]);
		i++;
	}
}

void	free_flags(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_flags)
	{
		free(data->flag[i]);
		i++;
	}
	free(data->flag);
}

void	free_args(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_args)
	{
		free(data->args[i]);
		i++;
	}
	free(data->args);
}

void	free_cmds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmds)
	{
		free(data->cmds[i]);
		i++;
	}
	free(data->cmds);
}