/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/27 18:44:00 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_parser(t_prompt *pr, t_data *data)
{
	init_str(data, pr);
	if (is_there_pipe(pr))
	{	
		if (!is_piped_input_valid(pr->input, data))
			return (free_master(data));
	}
	if (!is_there_pipe(pr))
	{
		if (!single_node_handler(data))
			return (free_master(data));
	}
	else if (is_there_pipe(pr))
	{
		if (!multi_node_handler(data, 0))
			return (free_master(data));
	}
	if (!init_exec_var(data))
		return (free_master(data));
	command_manager(data);
	if (g_status == 1)
	{
		set_status(data, 130, NULL, NULL);
		g_status = 0;
	}
	free_master(data);
}

int	init_exec_var(t_data *data)
{
	int	n;

	n = get_heredoc_counter(data->exec);
	data->n_redirs = get_n_redir(data->exec);
	data->n_cmds = get_node_len(data->exec);
	data->here_doc_fd
		= malloc(sizeof(int) * n);
	ft_memset(data->here_doc_fd, -1, n);
	if (!heredoc_finder(data->exec, data))
		return (0);
	return (1);
}

// void	node_printer(t_cmd *pr)
// {
// 	while (pr)
// 	{
// 		printf("_______________________\n");
// 		printf("CMD = \t [%s]\n", pr->cmd);
// 		printf("_______________________\n");
// 		int i = 0;
// 		printf("_______________________\n");
// 		printf("-------- PARAMS -------\n");
// 		while (pr->param[i])
// 		{
// 			printf("[%i] -> %s\n", i, pr->param[i]);
// 			i++;
// 		}
// 		printf("[%i] -> %s\n", i, pr->param[i]);
// 		printf("_______________________\n");
// 		printf("--------- REDIRS ------\n");
// 		t_redir	*nav = pr->redirs;
// 		while (nav)
// 		{
// 			printf("REDIR ID -> %i\n", nav->type);
// 			printf("FILNAME  -> %s\n", nav->file);
// 			printf("next = %p\n\n", nav->next);
// 			nav = nav->next;
// 		}
// 		printf("_______________________\n");
// 		pr = pr -> next;
// 	}
// }
