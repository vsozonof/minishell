/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:18:20 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 10:20:40 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_node(t_cmd *pr, t_input *inp, t_data *data)
{
	int	n;

	n = get_word_count(inp);
	pr->cmd = extract_command_name(inp);
	pr->param = malloc (sizeof(char *) * (n + 1));
	pr->param[n] = NULL;
	pr->env = data->pr->nv;
	// ajoute un compteur du nombre de cmd total (tous les maillons)
	// ajoute un compteur du nombre de redirection dans la node
	// ajoute un compteur du nombre de redir total (tous les maillons)
	extract_params(inp, pr);
	n = get_redir_count(inp) + 1;
	if (n > 1)
	{
		pr->redirs = malloc(sizeof(t_redir));
		if (!pr->redirs)
			return ;
		alloc_redir_list(pr, n);
		extract_redirs(inp, pr);
	}
	node_printer(pr);
}

void	extract_redirs(t_input *inp, t_cmd *pr)
{
	t_input	*nav;
	t_redir	*red;

	nav = inp;
	red = pr->redirs;
	while (nav)
	{
		if (nav->i == 1 && red)
		{
			red->type = set_redir_type(nav->str);
			nav = nav->next;
			red->file = nav->str;
			red = red->next;
		}
		else
			nav = nav->next;
	}
}

int	set_redir_type(char *token)
{
	if (token[0] == '>' && !token[1])
		return (1);
	else if (token[0] == '<' && !token[1])
		return (2);
	else if (token[0] == '<' && token[1] == '<' && !token[3])
		return (3);
	else if (token[0] == '>' && token[1] == '>' && !token[3])
		return (4);
	printf("Error with redir type\n");
	return (-1);
}

void	extract_params(t_input *inp, t_cmd *pr)
{
	t_input	*nav;
	int		i;

	nav = inp;
	i = 0;
	while (nav)
	{
		if (nav->i == 0)
		{
			pr->param[i] = nav->str;
			i++;
		}
		nav = nav->next;
	}
}

char	*extract_command_name(t_input *inp)
{
	t_input	*nav;

	nav = inp;
	while (nav)
	{
		if (nav->i == 0)
			return (nav->str);
		nav = nav->next;
	}
	return (NULL);
}
