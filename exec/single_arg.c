/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:55:02 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/16 08:36:54 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_data *data, char **cmd_argument)
{
	char	*buf;
	char	*fre;
	char	*essaie;
	int		check;

	data->index_redirs = ((i = 0));
	buf = arg(data->input, data);
	if (!buf)
		return (-1);
	if (data->n_redirs > 0)
		essaie = data->redir_tab[0];
	else
		essaie = data->input;
	cmd_argument = ft_split(essaie, ' ');
	if (cmd_argument == NULL)
		return (free(buf), -1);
	fre = ft_do_process(data->pr->nv, buf);
	check = check_fre_cmd(data, buf, cmd_argument, fre);
	if (check == 1)
		return (-1);
	exec_single(cmd_argument, fre, data);
	// if (data->n_redirs > 0)
	// 	free(essaie);
	free_single(data, cmd_argument, buf, fre);
	return (0);
}

int	check_fre_cmd(t_data *data, char *buf, char **cmd_argument, char *fre)
{
	if (!fre || !cmd_argument)
	{
		set_status(data, 1, "command not found", buf);
		free(buf);
		ft_freedb(cmd_argument);
		return (1);
	}
	return (0);
}

int	exec_single(char **cmd_argument, char *fre, t_data	*data)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
	{
		if (data->n_redirs > 0)
		{
			if (redirection_single(data) == -1)
				return (-1);
		}
		execve(fre, cmd_argument, data->pr->nv);
		fprintf(stderr, "execve fail\n");
		free(fre);
		ft_freedb(cmd_argument);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}

int	redirection_single(t_data *data)
{
	int		last;
	int		first;

	first = first_redirect(data, data->input, 0);
	last = last_redirect(data, data->input, 0);
	i = 0;
	if (data->n_redirs >= 1)
	{
		if (redirection_dup1_in(data, first, last) == -1)
			return (-1);
	}
	return (0);
}

int	redirection_single_chev(t_data *data, char *input)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = data->tab[0][0];
	while (input[i++])
	{
		if (input[i] == ' ')
			cpt--;
		if (input[i] == '>' && cpt > 0)
			return (1);
		else if (input[i] == '<' && cpt > 0)
			return (2);
		else if ((input[i] == '>' || input[i] == '<')
			&& cpt == 0)
			return (0);
	}
	return (-1);
}
