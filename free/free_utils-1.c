/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 04:25:22 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 20:39:49 by vsozonof         ###   ########.fr       */
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
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

t_input	*free_at_pos(t_input *L, int pos)
{
	t_input		*prec;
	t_input		*cur;
	int			i;

	cur = L;
	prec = L;
	i = 0;
	if (pos == 0)
	{
		L = L->next;
		free(cur);
		return (NULL);
	}
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cur->next;
	free(cur);
	return (L);
}
