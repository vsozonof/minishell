/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:57:24 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/15 16:46:47 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(t_data *data, int **pipefd, int i, char **cmd_argument)
{
	char	*cmd_arg;

	if (ft_pipex_helper_dup(data, pipefd, i) == -1)
	{
		free(cmd_argument);
		ft_freedb(data->actual_path);
		return (-1);
	}
	if (check_redirection_now(data, i) == 0)
		cmd_arg = data->redir_tab[i];
	else
		cmd_arg = data->cmds[i];
	fprintf(stderr, "all_cmd = %s\n", cmd_arg);
	cmd_argument = ft_split(cmd_arg, ' ');
	// if (builtin_checker())
	// {
	// 	builtin;
	// 	exit(0);
	// }
	// cree un if qui contiens checker de builtin
	execve(data->actual_path[i], cmd_argument, data->pr->nv);
	free_all_pipe(pipefd);
	exit(0);
	return (0);
}

int	ft_pipex_helper_dup(t_data *data, int **pipefd, int i)
{
	int		check;

	check = 0;
	if (i % 2 == 0)
		check = child_process_in(pipefd, data, i, 0);
	else if (i % 2 == 1)
		check = child_process_in(pipefd, data, i, 1);
	if (check == -1)
		return (-1);
	return (0);
}
