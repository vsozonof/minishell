/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:18:20 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 14:49:26 by tpotilli         ###   ########.fr       */
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
	else
		pr->redirs = NULL;
	pr->next = NULL;
	// node_printer(pr);
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
			if (nav)
			{
				red->file = ft_strdup(nav->str);
				red = red->next;
			}
			else
				red->file = NULL;
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
			pr->param[i] = ft_strdup(nav->str);
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
			return (ft_strdup(nav->str));
		nav = nav->next;
	}
	return (NULL);
}
