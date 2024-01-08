/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_overall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:26:54 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/08 04:14:45 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// il me faut le argv argv et envp

int pipe_command(t_data *data)
{
    // printf("input %s\ncounter %d\n", data->input, data->n_args);
    // printf("c args %d\n", data->c_args);
    // printf("voici la liste dans data\n");
    // printf("salut\n");
	// printf("input entier : %s\n", data->input);
	// if (data->n_args == 1)
		// exec_one_arg(data->input);
	int i = 0;
	while (data->n_args > i)
	{
		// printf("args entier : %s\n", data->args[i]);
		i++;
	}
	// printf("BREF\n");

	return (0);
}

void	exec_one_arg(char **cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

// int multi_pipe(t_data *data)
// {

// 	if (argc >= 5)
// 	{
// 		file[0] = ft_create_fd(argv[1], O_RDONLY);
// 		file[1] = ft_create_fd(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
// 		if (file[0] == -1 || file[1] == -1)
// 			return (1);
// 		ft_pipex(argv, file, envp, argc);
// 	}
// 	else
// 		write(2, "Invalid argument\n", 18);
// 	return (0);
// }

// int	ft_pipex(char *argv[], int *file, char *env[], int argc)
// {
// 	int	i;

// 	i = 3;
// 	dup2(STDIN, 0);
// 	dup2(file[1], 1);
// 	process(argv[2], env, file[0]);
// 	while (i < argc - 2)
// 	{
// 		process(argv[i], env, 1);
// 		i++;
// 	}
// 	ft_do_process(env, argv[i]);
// 	return (0);
// }

// int	process(char *cmd, char *env[], int token)
// {
// 	pid_t	pid;
// 	int		pipefd[2];

// 	pipe(pipefd);
// 	pid = fork();
// 	if (pid)
// 	{
// 		close(pipefd[1]);
// 		dup2(pipefd[0], 0);
// 		waitpid(pid, NULL, 0);
// 	}
// 	else
// 	{
// 		close(pipefd[0]);
// 		dup2(pipefd[1], 1);
// 		if (token == 0)
// 			exit(1);
// 		else
// 			ft_do_process(env, cmd);
// 	}
// 	return (0);
// }

// char **remake_argv(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	**argv;

// 	i = 0;
// 	argv = malloc(sizeof(char *) * (data->n_args + 1));
// 	if (!argv)
// 		return (NULL);
// 	while (i < data->n_args)
// 	{
// 		j = 0;
// 		argv[i] = malloc(sizeof(char) * (ft_strlen(data->input) + 1));
// 		if (!argv)
// 			return (free(argv), NULL);
// 		while (data->input[j])
// 		{
// 			argv[i][j] = data->input[j];
// 			j++;
// 		}
// 		argv[i][j] = '\0';
// 		data = data->next;
// 		i++;
// 	}
// 	argv[i] = NULL;
// 	return (argv);
// }