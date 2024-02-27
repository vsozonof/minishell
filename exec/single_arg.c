/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:09:07 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 09:27:16 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_data *data)
{
	char	*comd;

	comd = NULL;
	exec_single(data, comd, data->exec);
	// fprintf(stderr, "e probleme viens de la\n");
	// get_and_print_statuscode(data, data->exec->cmd);
	free(comd);
	return (0);
}

int	exec_single(t_data *data, char *comd, t_cmd *cmd)
{
	int					pid;
	int					*file;
	struct sigaction    sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ft_siginal;
	sigaction(SIGINT, &sa, NULL);
	file = NULL;
	if (data->n_redirs > 0)
	{
		file = redirection_create(cmd, data);
		if (!file)
			return (0);
	}
	if (data->exec->cmd == NULL)
		return (free_problem(data, file, cmd), 0);
	if (builtin_single(cmd, data, file) == -1)
		return (0);
	pid = fork();
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
		child_process_single(data, cmd, file, comd);
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}

int	child_process_single(t_data *data, t_cmd *cmd, int *file, char *comd)
{
	int	error;

	comd = ft_do_process(data->exec->env, data->exec->cmd);
	if (!comd)
	{
		free_problem(data, file, cmd);
		exit(0);
	}
	fprintf(stderr, "avant exec\n");
	error = execve(comd, data->exec->param, data->exec->env);
	if (error == -1)
		write(2, "could not execute the command\n", 31);
	fprintf(stderr, "apres exec\n");
	free_problem(data, file, cmd);
	free(comd);
	exit(0);
	return (-1);
}
