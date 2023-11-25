/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:29:44 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/25 14:43:35 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	(void)argc;
	(void)argv;
	get_input(envp);
}

void	free_data_struct(t_data *data)
{
	int		i;

	i = 0;
	while (data)
	{
		free(data->input);
		free(data->pr);
		free_data_envp(data, i);
		free_data_flag(data, i);
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

void	free_data_flag(t_data *data, int i)
{
	while (data->flag[i])
	{
		free(data->flag[i]);
		i++;
	}
}
