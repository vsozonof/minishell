/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:09:07 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 13:28:28 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_cmd *cmd)
{
	char	*comd;
	int		verif;

	verif = builtin_single(cmd);
	if (verif == 0)
		return (0);
	comd = ft_do_process(cmd->env, cmd->cmd);
	if (!comd)
		return (fprintf(stderr, "la commande a echouer\n"), 1);
	exec_single(cmd, comd);
	free(comd);
	return (0);
}

int	exec_single(t_cmd *cmd, char *comd)
{
	int		pid;
	int		error;

	pid = fork();
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
	{
		if (len_list(cmd->redirs) > 0)
		{
			fprintf(stderr, "mon nb redir = %ld\n", len_list(cmd->redirs));
			fprintf(stderr, "donc je passe par la\n");
			if (redirection_create(cmd) == 1)
				return (1);
		}
		error = execve(comd, cmd->param, cmd->env);
		if (error == -1)
			fprintf(stderr, "could not execute the command\n");
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}

int		get_and_print_statuscode()
{
	int		wstatus;
	int		statusCode;

	wait(&wstatus);
	statusCode = -1;
	if (WIFEXITED(wstatus))
	{
		statusCode = WEXITSTATUS(wstatus);
		if (statusCode != 0)
			fprintf(stderr, "failure status code: %d\n", (statusCode + 155));
		statusCode = WIFSIGNALED(wstatus);
		if (statusCode != 0)
			fprintf(stderr, "failure with a signal is unknown %d\n", (statusCode + 155));
	}
	return (statusCode);
}
