/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:55:02 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/29 06:27:27 by tpotilli         ###   ########.fr       */
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
	cmd_argument = ft_split(essaie, ' ');
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
	buf2 = ft_essaie_helper(buf, i, c);
	free(buf);
	return (buf2);
}

char *ft_essaie_helper(char *buf, int i, int c)
{
	char	*buf2;
	int		cpt;
	(void)c;

	cpt = ft_count_space(buf);
	int y = 0;
	while (buf[y] && buf[y] != ' ')
		y++;
	buf2 = malloc(sizeof(char) * (y + 1));
	while (buf[i] && buf[i] != ' ')
	{
		buf2[i] = buf[i];
		i++;
	}
	buf2[i] = '\0';
	return (buf2);
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
				if (dup2(data->tab[0][2], 1) < 0)
					return (close(data->tab[data->index_redirs][2]), printf("problem with dup2 1"), -1);
			}
		}
	}
	return (0);
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