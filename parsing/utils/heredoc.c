/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:37:41 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/26 10:25:25 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_finder(t_cmd *node)
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
				if (!do_heredoc(nav1->file, nav1))
					return (0);
				nav1 = nav1->next;
			}
			else
				nav1 = nav1->next;
		}
		nav2 = nav2->next;
	}
	return (1);
}

int	do_heredoc(char *delimiter, t_redir *redir_node)
{
	char	*tmp_fname;
	int		fd;

	tmp_fname = get_tmp_filename();
	fd = open(tmp_fname, O_CREAT | O_WRONLY, 0644);
	g_status = 2;
	if (!(do_heredoc_extra(delimiter, fd)))
	{
		free(tmp_fname);
		return (0);
	}
	free(delimiter);
	redir_node->file = tmp_fname;
	return (1);
}

int	do_heredoc_extra(char *delimiter, int fd)
{
	int		dup_save;
	char	*heredoc_input;

	while (42)
	{
		dup_save = dup(0);
		heredoc_input = readline("> ");
		dup2(dup_save, 0);
		if (g_status == 1)
			return (0);
		if (!heredoc_input)
			break ;
		if (!ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter)))
		{
			free(heredoc_input);
			break ;
		}
		ft_putstr_fd(heredoc_input, fd);
		write(fd, "\n", 1);
		free(heredoc_input);
	}
	return (1);
}

char	*get_tmp_filename(void)
{
	char		*str;
	int			i;
	int			fd;

	fd = open("/dev/random", O_RDONLY);
	str = malloc(sizeof(char) * 21);
	if (!fd)
		return (write(2, "problem with fd in here_doc\n", 29), NULL);
	read(fd, str, 16);
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