/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:55:02 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/31 15:13:47 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_data *data)
{
	char	*buf;
	char	*fre;
	char	**cmd_argument;
	char	*essaie;

	data->index_redirs = 0;
	buf = arg(data->input, data);
	if (data->n_redirs > 0)
		essaie = ft_essaie(data, data->input);
	else
		essaie = data->input;
	cmd_argument = ft_split(essaie, ' ');
	fre = ft_do_process(data->pr->nv, buf);
	if (!fre || !cmd_argument)
	{
		exit_status_updater(data, 1, "command not found", buf);
		free(buf);
		ft_freedb(cmd_argument);
		// free(essaie);
		return (0);
	}
	int	c = 0;
	fprintf(stderr, "fre = %s\n", fre);
	while (cmd_argument[c++])
		fprintf(stderr, "cmd = %s\n", cmd_argument[c]);
	exec_single(cmd_argument, fre, data);
	ft_freedb(cmd_argument);
	free(buf);
	free(fre);
	if (data->n_redirs > 0)
		free(essaie);
	if (data->n_redirs > 0)
		close(data->tab[0][2]);
	return (0);
}

int	exec_single(char **cmd_argument, char *fre, t_data	*data)
{
	int		pid;
	int		j;
	int		i;

	pid = fork();
	j = ((i = 0));
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
	{
		if (redirection_single(data) == -1)
			return (-1);
		execve(fre, cmd_argument, data->pr->nv);
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
	if (data->n_redirs > 0)
	{
		// fprintf(stderr, "%d\n", data->n_redirs);
		if (data->n_redirs == 2)
		{
			if (dup2(data->tab[0][2], 0) < 0)
				return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
			if (dup2(data->tab[1][2], 1) < 0)
				return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
		}
		else if (data->n_redirs == 1)
		{
			if (redirection_single_chev(data, data->input) == 0)
			{
				if (dup2(data->tab[0][2], 0) < 0)
					return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
				close(data->tab[0][2]);
			}
			else if (redirection_single_chev(data, data->input) == 1)
			{
				if (dup2(data->tab[0][2], 1) < 0)
					return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
				close(data->tab[0][2]);
			}
			fprintf(stderr, "je sors\n");
		}
	}
	return (0);
}

int	redirection_single_chev(t_data *data, char *input)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = data->tab[0][0];
	// fprintf(stderr, "voici la pos de mon fd %d\n", cpt);
	while (input[i++])
	{
		if (input[i] == ' ')
			cpt--;
		// fprintf(stderr, "%d\n", cpt);
		// fprintf(stderr, " i = %d\n", i);
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

/* ancienne versin bonne pour single arg a garder !!!!!!!!!!!!!
int	redirection_single_chev(t_data *data)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = data->tab[0][0];
	// fprintf(stderr, "voici la pos de mon fd %d\n", cpt);
	while (data->input[i++])
	{
		if (data->input[i] == ' ')
			cpt--;
		// fprintf(stderr, "%d\n", cpt);
		// fprintf(stderr, " i = %d\n", i);
		if (data->input[i] == '>' && cpt > 0)
			return (1);
		else if (data->input[i] == '<' && cpt > 0)
			return (2);
		else if ((data->input[i] == '>' || data->input[i] == '<')
			&& cpt == 0)
			return (0);
	}
	return (-1);
}
*/

/*if (data->n_redirs > 0)
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

/*

char	**espoir(char **cmd_argument)
{
	int		i;
	int		j;
	int		c;
	char	**buf;

	i = 0;
	c = 0;
	buf = malloc(sizeof(char *) * (found_max(cmd_argument) + 1));
	while (cmd_argument[i + 1])
	{
		j = 0;
		buf[c] = malloc(sizeof(char *) * (ft_strlen(cmd_argument[i]) + 1));
		while (cmd_argument[i][j])
		{
			buf[c][j] = cmd_argument[i][j];
			j++;
		}
		buf[c][j] = '\0';
		i++;
		c++;
	}
	buf[c] = NULL;
	return (buf);
}
*/

/*
{
	char	*buf2;
	char	**split;
	int		cpt;
	int		fd_pos;

	fd_pos = data->tab[0][0];
	cpt = ft_count_space(buf);
	int y = 0;
	while (buf[y] && buf[y] != ' ')
		y++;
	split = ft_split(buf, ' ');
	buf2 = malloc(sizeof(char) * (y + 1));
	while (split[i])
	{
		j = 0;
		if (i != fd_pos)
		{
			while (split[i][j] && split[i][j] != ' ')
			{
				buf2[j] = split[i][j];
				j++;
			}
		}
		i++;
	}
	buf2[j] = '\0';
	return (buf2);
}
*/