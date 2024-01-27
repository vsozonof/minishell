/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:55:02 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/27 00:49:09 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_data *data)
{
	char	*buf;
	char	*fre;
	char	**cmd_argument;

	buf = arg(data->input, data);
	cmd_argument = ft_split(data->input, ' ');
	fre = ft_do_process(data->pr->nv, buf);
	if (!fre || !cmd_argument)
	{
		perror("wrong commd\n");
		free(buf);
		ft_freedb(data->cmds);
		ft_freedb(cmd_argument);
		return (0);
	}
	exec_single(cmd_argument, fre, data);
	free(buf);
	ft_freedb(cmd_argument);
	free(fre);
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
		execve(fre, cmd_argument, data->pr->nv);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}
