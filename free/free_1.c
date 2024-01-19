/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 04:25:22 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/19 03:07:46 by vsozonof         ###   ########.fr       */
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
		data = data->next;
	}
}

void	free_data_envp(t_data *data, int i)
{
	(void)data;
	(void)i;
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

void	free_pwd(t_data *data)
{
	(void)data;
}

void	free_env(t_env	*env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		tmp = env->next;
		free(env->var);
		free(env);
		env = tmp;
	}
}
