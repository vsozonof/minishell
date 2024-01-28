/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:55:02 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/28 22:00:52 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_data *data)
{
	char	*buf;
	char	*fre;
	char	**cmd_argument;
	int		i;

	i = 0;
	data->index_redirs = 0;
	buf = arg(data->input, data);
	cmd_argument = ft_split(data->input, ' ');
	fre = ft_do_process(data->pr->nv, buf);
	if (!fre || !cmd_argument)
	{
		perror("wrong commd\n");
		free(buf);
		ft_freedb(cmd_argument);
		return (0);
	}
	exec_single(cmd_argument, fre, data);
	free(buf);
	ft_freedb(cmd_argument);
	free(fre);
	close(data->tab[0][2]);
	return (0);
}

int	exec_single(char **cmd_argument, char *fre, t_data	*data)
{
	int		pid;
	int		i;

	pid = fork();
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
	{
		if (redirection_single(data) == -1)
			return (-1);
		execve(fre, cmd_argument, data->pr->nv);
		free(fre);
		i = 0;
		ft_freedb(cmd_argument);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}

int	redirection_single(t_data *data)
{
	if (data->n_redirs > 0)
	{
		fprintf(stderr, "n_redir = %d\n", data->n_redirs);
		if (data->n_redirs == 2)
		{
			if (dup2(data->tab[0][2], 0) < 0)
				return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
			if (dup2(data->tab[1][2], 1) < 0)
				return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
		}
		if (data->n_redirs == 1)
		{
			if (data->tab[0][1] == 1)
			{
				if (dup2(data->tab[0][2], 0) < 0)
					return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
			}
			else
			{
				fprintf(stderr, "je suis ici\n");
				fprintf(stderr, "voici l'input %s\n", data->input);
				if (dup2(data->tab[0][2], 1) < 0)
					return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
			}
		}
	}
	return (0);
}

/*
if (data->n_redirs > 0)
	{
		if (data->tab[data->index_redirs])
		{
			if (data->tab[data->index_redirs][0] == i)
			{
				if (data->tab[data->index_redirs][1] == 1)
					return (buf[1]);
				else if (data->tab[data->index_redirs][1] == 3)
					return (buf[i--]);
			}
		}
	}
*/