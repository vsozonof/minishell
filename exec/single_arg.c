/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:09:07 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/28 02:35:03 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*single_arg(t_data *data)
{
	char	*comd;
	int		*file;

	comd = NULL;
	file = NULL;
	if (data->exec->cmd == NULL)
		return (free_problem(data, file, data->exec), file);
	if (builtin_checker(data->exec->cmd) > 0
		&& builtin_checker(data->exec->cmd) < 8)
	{
		if (data->n_redirs > 0)
		{
			file = redirection_create(data->exec, data, file);
			if (!file)
				return (NULL);
		}
		builtin_single(data->exec, data, file);
		return (NULL);
	}
	exec_single(data, comd, data->exec, file);
	if (data->n_redirs > 0)
		redir_here(data, file);
	return (file);
}

void	redir_here(t_data *data, int *file)
{
	t_redir	*redir;
	int		i;

	i = 0;
	redir = data->exec->redirs;
	if (file == NULL)
	{
		while (redir)
		{
			if (redir->type == 3)
			{
				close(data->here_doc_fd[data->index_here_doc]);
				data->index_here_doc++;
				unlink(redir->file);
			}
			i++;
			redir = redir->next;
		}
	}
	if (file != NULL)
		close_all_open_redirs(file, data->exec);
}

int	exec_single(t_data *data, char *comd, t_cmd *cmd, int *file)
{
	int					pid;
	struct sigaction	sa;
	int					status;

	pid = fork();
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
		child_process_single(data, cmd, file, comd);
	else if (pid > 0)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		waitpid(pid, &status, 0);
		get_and_print_statuscode(data, status);
	}
	free(comd);
	return (0);
}

int	child_process_single(t_data *data, t_cmd *cmd, int *file, char *comd)
{
	if (data->n_redirs > 0)
	{
		file = redirection_create(data->exec, data, file);
		if (!file)
			free_problem_single(data, file);
	}
	if (data->exec->cmd == NULL
		|| ft_strlen(data->exec->cmd) == 0)
	{
		set_status(data, 0, "Command not found\n", cmd->cmd);
		data->i_status = 127;
		free_problem_single(data, file);
	}
	comd = ft_do_process(data->exec->env, data->exec->cmd, data);
	if (!comd)
		free_problem_single(data, file);
	execve(comd, data->exec->param, data->exec->env);
	free_problem_single(data, file);
	free(comd);
	exit(1);
	return (-1);
}
