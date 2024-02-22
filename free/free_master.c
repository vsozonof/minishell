/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:29:11 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 13:46:00 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_manager(t_data *data, int key)
{
	if (key == 1)
	{
		if (data->pr->input)
			free(data->pr->input);
		if (data->input)
			free(data->input);
	}
	else if (key == 2)
	{
		if (data->cmds)
			free_cmds(data);
		if (data->pr->input)
			free(data->pr->input);
	}
	if (data->cmds)
		free_cmds(data);
	if (data->redir_tab)
		ft_split_free(data->redir_tab);
	if (data->tab)
		free_tab(data->tab);
}

void	free_master(t_data *data)
{
	printf("---------------------\n");
	printf("----------FREE-------\n");
	if (data->input)
		free(data->input);
	free_input_lst(data->inp);
	free_cmd_nodes(data->exec);
}
void	free_cmd_nodes(t_cmd *nodes)
{
	t_redir	*tmp1;
	t_redir	*nav;
	t_cmd	*tmp2;

	while (nodes)
	{
		printf("----------\n");
		printf("FREE NODE CMD\n");
		free (nodes->cmd);
		printf("SPLIT-FREE\n");
		ft_split_free(nodes->param);
		nav = nodes->redirs;
		while (nav)
		{
			free(nav->file);
			tmp1 = nav;
			nav = nav->next;
			free(tmp1);
		}
		tmp2 = nodes;
		nodes = nodes->next;
		free(tmp2);
	}
}

void	free_input_lst(t_input *lst)
{
	t_input	*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		if (lst->str)
			free(lst->str);
		free(lst);
		lst = tmp;
	}
	lst = NULL;
}

void	free_end_of_program(t_prompt *p)
{
	if (p->user)
		free(p->user);
	if (p->w_d)
		free(p->w_d);
	if (p->post)
		free(p->post);
	if (p->env)
		free_env(p->env);
	if (p->nv)
		free_env_tab(p->nv);
	if (p->name)
		free(p->name);
	if (p->pid)
		free(p->pid);
	if (p->data->c_status)
		free(p->data->c_status);
}
