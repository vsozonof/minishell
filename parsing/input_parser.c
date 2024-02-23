/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/23 12:02:05 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_parser(t_prompt *pr, t_data *data)
{
	init_str(data, pr);
	if (!is_piped_input_valid(pr->input, data))
		return (free_master(data));
	if (!is_there_pipe(pr))
	{
		if (!single_node_handler(data))
			return ;
	}
	else if (is_there_pipe(pr))
		multi_node_handler(data, 0);
	init_exec_var(data);
	printf("APRES EXPAND\n");
	// node_printer(data->exec);
	command_manager(data);
	free_master(data);
}

void	init_exec_var(t_data *data)
{
	data->n_redirs = get_n_redir(data->exec);
	data->n_cmds = get_node_len(data->exec);
}



void	node_printer(t_cmd *pr)
{
	while (pr)
	{
		printf("_______________________\n");
		printf("CMD = \t [%s]\n", pr->cmd);
		printf("_______________________\n");
		int i = 0;
		printf("_______________________\n");
		printf("-------- PARAMS -------\n");
		while (pr->param[i])
		{
			printf("[%i] -> %s\n", i, pr->param[i]);
			i++;
		}
		printf("[%i] -> %s\n", i, pr->param[i]);
		printf("_______________________\n");
		printf("--------- REDIRS ------\n");
		t_redir	*nav = pr->redirs;
		while (nav)
		{
			printf("REDIR ID -> %i\n", nav->type);
			printf("FILNAME  -> %s\n", nav->file);
			printf("next = %p\n\n", nav->next);
			nav = nav->next;
		}
		printf("_______________________\n");
		pr = pr -> next;
	}
}


