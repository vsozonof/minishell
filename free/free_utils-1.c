/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 04:25:22 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/16 08:37:03 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	data->cmds = NULL;
}

void	free_env(t_env	*env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		tmp = env->next;
		if (env->var)
			free(env->var);
		free(env);
		env = tmp;
	}
}

void	free_env_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i])
			free(env[i]);
		i++;
	}
	free(env);
}

void	free_tab(int **tab)
{
	int	i;

	i = 0;
	// printf("->->-> %i \n", n_redir);
	while (i < n_redir)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}
