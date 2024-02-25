/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/25 14:08:31 by vsozonof         ###   ########.fr       */
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
	node_printer(data->exec);
	init_exec_var(data);
	node_printer(data->exec);
	command_manager(data);
	free_master(data);
}

void	init_exec_var(t_data *data)
{
	data->n_redirs = get_n_redir(data->exec);
	data->n_cmds = get_node_len(data->exec);
	heredoc_finder(data->exec);
}

void	heredoc_finder(t_cmd *node)
{
	t_redir	*nav1;
	t_cmd	*nav2;

	nav2 = node;
	while (nav2)
	{
		nav1 = nav2->redirs;
		while (nav1)
		{
			if (nav1->type == 3)
			{
				do_heredoc(nav1->file, nav1);
				nav1 = nav1->next;
			}
			else
				nav1 = nav1->next;
		}
		nav2 = nav2->next;
	}
}

void	do_heredoc(char *delimiter, t_redir *redir_node)
{
	char	*tmp_fname;
	char	*heredoc_input;
	int		fd;

	tmp_fname = get_tmp_filename();
	fd = open(tmp_fname, O_APPEND | O_WRONLY | O_CREAT, 0644);
	while (42)
	{
		heredoc_input = readline("> ");
		if (!ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter)))
		{
			free(heredoc_input);
			break ;
		}
		ft_putstr_fd(heredoc_input, fd);
		write(fd, "\n", 1);
		free(heredoc_input);
	}
	free(delimiter);
	redir_node->file = tmp_fname;
}

char	*get_tmp_filename(void)
{
	char		*str;
	int			i;
	int			fd;

	fd = open("/dev/random", O_RDONLY);
	str = malloc(sizeof(char) * 21);
	if (!fd)
		return (fprintf(stderr, "problem with fd in here_doc\n"), NULL);
	read(fd, str, 14);
	i = 1;
	str[0] = '.';
	while (i <= 15)
	{
		str[i] = (str[i] % 25) + 'a';
		i++;
	}
	str[16] = '.';
	str[17] = 't';
	str[18] = 'x';
	str[19] = 't';
	str[20] = '\0';
	close(fd);
	return (str);
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


