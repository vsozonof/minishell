/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:09:07 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/23 15:22:25 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_data *data)
{
	char	*comd;
	// int		verif;

	comd = NULL;
	fprintf(stderr, "je passe par single\n");
	exec_single(data, comd);
	free(comd);
	return (0);
}

int	exec_single(t_data *data, char *comd)
{
	int		pid;
	int		error;
	int		*file;

	file = NULL;
	pid = fork();
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
	{
		if (data->n_redirs > 0)
		{
			file = redirection_create(data);
			if (!file)
				return (1);
		}
		if (builtin_single(data) == 1)
			return (fprintf(stderr, "error in builtin\n"));
		comd = ft_do_process(data->exec->env, data->exec->cmd);
		if (!comd)
		{
			close_all_open_redirs(file, data->n_redirs - 1);
			fprintf(stderr, "la commande a echouer\n");
			exit(0);
		}
		error = execve(comd, data->exec->param, data->exec->env);
		if (error == -1)
			fprintf(stderr, "could not execute the command\n");
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}
