/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:10:50 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/08 15:37:44 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// cat > test1 > test2 < test3 | wc
// ls > out > out1 > out2 < Makefile | cat < Makefile
// pour la cmd au dessus, il faut que dans out2 il y est un ls
// et que dans mon terminal il y ait le cat makefile
// peut etre ls ecrit proprement  dans out2 mais que tout se fait concatener
// par cat < makefile qui ecrit le makefile dans out2
// si plsuieurs pipe faire attention au input a la place du pipe

// !!! dnas redirection manager j'ai baisser mon nb_redirs -> retirer

/*
**	This function takes as parameter: 
**
**
** =====================================================
** =====================================================
**
**
*/

/*
**	This function takes as parameter: 
**
**	data -> the struct who contains all variables
**  to exec our program
**
** =====================================================
** =====================================================
**
**  Pipex_exec will check if we can execute the command
**  with the function ft_do_process (we also get the path)
**  then we go to ft_pipex to start the execution
*/

int	pipex_exec(t_data	*data)
{
	int		i;
	char	**cmd_argument;

	cmd_argument = NULL;
	data->index_redirs = ((i = 0));
	fprintf(stderr, "je passe par multi\n");
	while (data->cmds[i])
	{
		fprintf(stderr, "data->cmds[%d] = %s\n\n\n", i, data->cmds[i]);
		i++;
	}
	i = 0;
	while (data->redir_tab && data->redir_tab[i])
	{
		fprintf(stderr, "data->redir[%d] = %s\n\n\n", i, data->redir_tab[i]);
		i++;
	}
	i = 0;
	if (ft_check_access(data, i) == -1)
		return (-1);
	i = 0;
	while (data->actual_path[i])
	{
		fprintf(stderr, "data->actual[%d] = %s\n\n\n", i, data->actual_path[i]);
		i++;
	}
	fprintf(stderr, "len_db_tab(data->cmds) %d\n", len_db_tab(data->cmds));
	i = 0;
	ft_pipex(data, i, cmd_argument);
	ft_freedb(data->actual_path);
	return (0);
}

int	ft_check_access(t_data *data, int i)
{
	char	*buf;

	buf = NULL;
	data->actual_path = malloc(sizeof(char *) * (len_db_tab(data->cmds) + 1));
	if (!data->actual_path)
		return (-1);
	while (data->cmds[i])
	{
		buf = arg(data->cmds[i], data);
		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
		if (!data->actual_path[i])
		{
			while (i > 0)
				free(data->actual_path[i--]);
			perror("wrong commd\n");
			return (free(data->actual_path), free(buf), -1);
		}
		free(buf);
		i++;
	}
	data->actual_path[i] = NULL;
	return (0);
}

/*
data->actual_path = malloc(sizeof(char *) * (len_db_tab(data->cmds) + 1));
	if (!data->actual_path)
		return (0);
	while (data->cmds[i])
	{
		data->actual_path[i] = malloc(sizeof(char) * (ft_strlen(data->cmds[i]) + 1));
		if (!data->actual_path[i])
			return (0);
		buf = arg(data->cmds[i], data);
		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
		if (!data->actual_path[i])
		{
			perror("wrong commd\n");
			free(buf);
			// ft_freedb(data->cmds);
			return (0);
		}
		free(buf);
		i++;
	}
*/

/* acien ft_check_access
int	ft_check_access(t_data *data, int i)
{
	char	*buf;
	int		j;

	j = 0;
	data->actual_path = malloc(sizeof(char *) * len_db_tab(data->cmds));
	if (!data->actual_path)
		return (-1);
	while (data->cmds[i])
	{
		data->actual_path[i] = malloc(sizeof(char) * (ft_strlen(data->cmds[i]) + 1));
		if (!data->actual_path[i])
		{
			fprintf(stderr, "access a echouer\n");
			while (i >= 0)
				free(data->actual_path[i--]);
			free(data->actual_path);
			data->actual_path = NULL;
			return (-1);
		}
		buf = arg(data->cmds[i], data);
		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
		if (!data->actual_path[i])
		{
			perror("wrong commd\n");
			free(buf);
			return (-1);
		}
		data->actual_path[i][ft_strlen(data->cmds[i]) + 1] = '\0';
		free(buf);
		i++;
	}
	fprintf(stderr, "access a reussis\n");
	return (0);
}
*/

/*
data->actual_path = malloc(sizeof(char *) * (len_db_tab(data->cmds) + 1));
	if (!data->actual_path)
		return (0);
	while (data->cmds[i])
	{
		data->actual_path[i] = malloc(sizeof(char) * ft_strlen(data->cmds[i]));
		if (!data->actual_path[i])
			return (0);
		buf = arg(data->cmds[i], data);
		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
		if (!data->actual_path[i])
		{
			while (i > 0)
				free(data->actual_path[i--]);
			free(data->actual_path);
			perror("wrong commd\n");
			free(buf);
			// ft_freedb(data->cmds);
			return (0);
		}
		free(buf);
		i++;
	}
	data->actual_path[i] = NULL;
*/