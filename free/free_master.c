/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:29:11 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/09 04:42:41 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_manager(t_data *data, int key)
{
	if (key == 1)
	{
		free(data->pr->input);
		if (data->input)
			free(data->input);
	}
	else if (key == 2)
	{
		free_cmds(data);
		free(data->pr->input);
	}
	free(data->c_status);
	if (data->redir_tab)
		ft_split_free(data->redir_tab);
	if (data->redir_tab)
		ft_split_free(data->redir_tab);
	if (data->n_redirs)
		free_tab(data->tab, data->n_redirs);
}

void	free_end_of_program(t_prompt *p)
{
	free(p->w_d);
	free(p->post);
	free_env(p->env);
	free_env_tab(p->nv);
	free(p->name);
	free(p->pid);
}
