/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils-2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:20:24 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/28 23:19:22 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_side_env(t_prompt *ptr)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = ptr->env;
	ptr->nv = malloc(sizeof(char *) * (env_len(ptr->env) + 1));
	if (!ptr->nv)
		return ;
	while (tmp)
	{
		ptr->nv[i] = ft_strdup(tmp->var);
		i++;
		tmp = tmp->next;
	}
	ptr->nv[i] = NULL;
}

int	env_len(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}