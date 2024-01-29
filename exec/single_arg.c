/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:55:02 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/29 23:29:52 by tpotilli         ###   ########.fr       */
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
		essaie = ft_essaie(data);
	else
		essaie = data->input;
	fprintf(stderr, " essaie = %s\n", essaie);
	cmd_argument = ft_split(data->input, ' ');
	fre = ft_do_process(data->pr->nv, buf);
	if (!fre || !cmd_argument)
	{
		perror("wrong commd\n");
		free(buf);
		ft_freedb(cmd_argument);
		// free(essaie);
		return (0);
	}
	exec_single(cmd_argument, fre, data);
	ft_freedb(cmd_argument);
	free(buf);
	free(fre);
	// free(essaie);
	if (data->n_redirs > 0)
		close(data->tab[0][2]);
	return (0);
}

char *ft_essaie(t_data *data)
{
	char	*buf;
	char	*buf2;
	int		c;
	int		i;

	buf = malloc(sizeof(char) * (ft_strlen(data->input) + 1));
	i = 0;
	c = 0;
	while (data->input[i])
	{
		if (data->input[i] != '>' && data->input[i] != '<')
		{
			buf[c] = data->input[i];
			c++;
		}
		i++;
	}
	buf[c] = '\0';
	i = 0;
	c = 0;
	buf2 = ft_essaie_helper(buf, i, c, data);
	free(buf);
	return (buf2);
}

char *ft_essaie_helper(char *buf, int i, int j, t_data *data)
{
	char	*str;
	int		len;
	(void)j;
	(void)data;

	len = len_buf(buf, i);
	str = malloc(sizeof(char) * (len + 1));
	while (buf[i])
	{
		str[j] = buf[i];
		j++;
		i++;
		if (buf[i] == ' ' && buf[i + 1] == ' ')
			i++;
		// if (i == 11)
		// {
		// 	i++;
		// 	while (buf[i] != ' ')
		// 		i++;
		// 	i++;
		// }
	}
	str[j] = '\0';
	fprintf(stderr, "VOICI LE RESULTAT %s\n", str);
	return (str);
}

int	exec_single(char **cmd_argument, char *fre, t_data	*data)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
	{
		if (redirection_single(data) == -1)
			return (-1);
		int j = 0;
		while (cmd_argument[j])
		{
			fprintf(stderr, "%s\n", cmd_argument[j]);
			j++;
		}
		fprintf(stderr, "JUSTE AVANT EXEC VOICI %s\n", fre);
		int i = 0;
		while (cmd_argument[i++])
			fprintf(stderr, "%s\n", cmd_argument[i]);
		execve(fre, cmd_argument, data->pr->nv);
		fprintf(stderr, "rater\n");
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
			if (redirection_single_chev(data) == 0)
			{
				// fprintf(stderr, "je suis donc en entre\n");
				if (dup2(data->tab[0][2], 0) < 0)
					return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
			}
			else if (redirection_single_chev(data) == 1)
			{
				// fprintf(stderr, "je suis donc en sortie\n");
				if (dup2(data->tab[0][2], 1) < 0)
					return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
			}
			fprintf(stderr, "je sors\n");
		}
	}
	return (0);
}

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