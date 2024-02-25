/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:09:07 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/25 19:18:12 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_data *data)
{
	char	*comd;
	// int		verif;

	comd = NULL;
	fprintf(stderr, "je passe par single\n");
	exec_single(data, comd, data->exec);
	free(comd);
	return (0);
}

int	exec_single(t_data *data, char *comd, t_cmd *cmd)
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
			file = redirection_create(cmd, data);
		builtin_single(data, file);
		comd = ft_do_process(data->exec->env, data->exec->cmd);
		if (!comd)
			free_problem(data, file);
		error = execve(comd, data->exec->param, data->exec->env);
		if (error == -1)
			fprintf(stderr, "could not execute the command\n");
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}
