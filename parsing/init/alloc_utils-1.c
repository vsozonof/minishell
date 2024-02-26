/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils-1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:11:25 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/26 18:17:22 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_redir_list(t_cmd *pr, int n)
{
	int		i;
	t_redir	*p;

	p = pr->redirs;
	i = 1;
	while (i < n - 1)
	{
		p->next = malloc(sizeof(t_redir));
		if (!p->next)
			return (0);
		p = p->next;
		i++;
	}
	p -> next = NULL;
	return (1);
}

t_input	**alloc_struct(t_input **ptr, int n)
{
	int	i;

	i = 0;
	ptr = malloc(sizeof(t_input *) * n);
	while (i < (n - 1))
	{
		ptr[i] = malloc(sizeof(t_input));
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

void	alloc_multi_nodes(t_input **inp, t_cmd *pr)
{
	int		i;
	t_cmd	*nav;

	nav = pr;
	i = 1;
	while (inp[i])
	{
		nav -> next = malloc(sizeof(t_cmd));
		if (!nav -> next)
			return ;
		i++;
		nav = nav -> next;
	}
	nav->next = NULL;
}

t_input	*alloc_input_struct()
{
	t_input	*inp;

	inp = malloc(sizeof(t_input));
	if (!inp)
		return (NULL);
	inp->cmds = NULL;
	inp->next = NULL;
	inp->str = NULL;
	return (inp);
}
