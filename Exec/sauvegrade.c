/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sauvegrade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 09:50:48 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/10 09:50:55 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// t_pipes *init_struct(char *argv[])
// {
// 	t_pipes *pipes;
// 	int		nb;
// 	int		i;
// 	int		tmp;

// 	i = 0;
// 	nb = get_nb_pipes(argv);
// 	nb++;
// 	// printf("mon nb dans init_pipe %i\n", nb);
// 	pipes = malloc(sizeof(t_pipes) * (nb));
// 	if (!pipes)
// 		return (printf("problem malloc\n"), NULL);
// 	while (i < nb)
// 	{
// 		if (pipe(pipes[i].pipes) == -1)
// 			return (printf("pipe problem\n"), free(pipes), NULL);
// 		i++;
// 	}
// 	pipes[0].fd1 = argv[1];
// 	if (!pipes[0].fd1)
// 		return (printf("fd1 problem\n"), free(pipes), NULL);
// 	tmp = found_max(argv) - 1;
// 	pipes[0].fd2 = argv[tmp];
// 	if (!pipes[0].fd2)
// 		return (printf("fd2 problem\n"), free(pipes), NULL);
// 	return (pipes);
// }

// int	found_max(char **argv)
// {
// 	int	i;

// 	i = 0;
// 	while (argv[i])
// 		i++;
// 	return (i);
// }
// //revoir systheme pou rcompter le nombre de pipe
// // faire ne sorte que ca s'adapte pour nb de pipes, de fd, pour le moment simple
// int		get_nb_pipes(char **argv)
// {
// 	int		i;
// 	int		cpt;
// 	int		tmp;

// 	i = ((cpt = 0));
// 	tmp = 0;
// 	i = i + 2;
// 	while (i < found_max(argv))
// 	{
// 		tmp++;
// 		i++;
// 	}
// 	cpt = tmp - 2;
// 	return (cpt);
// }

// int	ft_pipex(char *argv[], char *env[], char *new_argv[])
// {
// 	pid_t	pid[2];
// 	int		status;
// 	int		i;
// 	int		nb;
// 	t_pipes	*pipes;
// 	pid_t	pid_child;
// 	// (void)pid_child;
// 	// (void)i;
// 	// (void)status;
// 	// (void)env;
// 	// (void)new_argv;
// 	// (void)nb;
// 	// (void)pid;
// 	nb = get_nb_pipes(argv);
// 	pipes = NULL;
// 	pipes = init_struct(argv);
// 	if (!pipes)
// 		return (-1);
// 	printf("nb %i\n", nb);
// 	i = 0;
// 	i = 0;
// 	nb++;
// 	while (i < nb)
// 	{
// 		pid[i] = fork();
// 		if (pid[i] < 0)	
// 			return (printf("erreur de fork\n"), 1);
// 		if (pid[i] == 0)
// 		{
// 			fprintf(stderr, "boucle numero %d et nb %d\n", i, nb);
// 			if (i == 0)
// 			{
// 				fprintf(stderr, "========JE SUIS DANS IN========\n");
// 				if (child_process_in(pipes, i, env, new_argv) == -1)
// 					return (-1);
// 				fprintf(stderr, "========JE SORS DE IN========\n");
// 			}
// 			else if (i == nb - 1)
// 			{
// 				fprintf(stderr, "///JE SUIS DANS OUT ET VOICI I = %d///\n", i);
// 				if (child_process_out(pipes, i, env, new_argv) == -1)
// 					return (-1);
// 				fprintf(stderr, "///JE SORS DE OUT ET VOICI I = %d///\n", i);
// 				exit(0);
// 			}
// 			else
// 			{
// 				fprintf(stderr, "--------JE SUIS DANS MIDDLE--------\n");
// 				if (child_process_middle(pipes, i, env, new_argv) == -1)
// 					return (-1);
// 				fprintf(stderr, "--------JE SORS DE MIDDLE--------");
// 				printf("truc de ouf\n");
// 			}
// 		}
// 		i++;
// 	}
// 	fprintf(stderr, "JE SUIS SORTIS DE MA BOUCLE voici mon pid %d\n", pid[i]);
// 	close(pipes[0].pipes[0]);
// 	close(pipes[0].pipes[1]);
// 	i = 0;
// 	while (i < nb)
// 	{
// 		pid_child = waitpid(pid[i], &status, 0);
// 		if (pid_child == -1)
// 			return (printf("problem pid\n"), free(pipes), -1);
// 		fprintf(stderr, "pid dans boucle = %d\n", pid[i]);
// 		fprintf(stderr, "i dans ma boucle de pid %d\n", i);
// 		i++;
// 	}
// 	fprintf(stderr, "=====WAH WAH WAH TU VA SORTIR LA=====\n");
// 	fprintf(stderr, "=====WAH WAH WAH TU VA SORTIR LA=====\n");
// 	fprintf(stderr, "=====WAH WAH WAH TU VA SORTIR LA=====\n");
// 	free(pipes);
// 	return (0);
// }


// int	child_process_in(t_pipes *pipes, int i, char *env[], char *argv[])
// {
// 	int	fd;
// 	fd = ft_create_fd(pipes[0].fd1, O_RDONLY); // trouver nom fichier argv[4]
// 	if (fd < 0)
// 		return (close(pipes[i].pipes[1]), -1);
// 	if (dup2(fd, STDIN_FILENO) < 0)
// 		return (close(pipes[i].pipes[1]), close(fd), perror("dup2"), -1);
// 	close(fd);
// 	if (dup2(pipes[i].pipes[1], STDOUT_FILENO) < 0)
// 		return (close(pipes->pipes[1]), perror("dup2"), -1);
// 	close(pipes[i].pipes[1]);
// 	close(pipes[i].pipes[0]);
// 	ft_do_process(env, argv[0], i);
// 	return (0);
// }

// // [penser a regler probleme de dup2] car le retour en cas d'erreur fonctionne mal
// int	child_process_middle(t_pipes *pipes, int i, char *env[], char *argv[])
// {
// 	if (dup2(pipes[i - 1].pipes[0], STDIN_FILENO) < 0)
// 		return (close(pipes[i - 1].pipes[0]), perror("dup2"), -1);
// 	close(pipes[i - 1].pipes[0]);
// 	close(pipes[i - 1].pipes[1]);
// 	if (dup2(pipes[i].pipes[1], STDOUT_FILENO) < 0)
// 		return (close(pipes[i].pipes[1]), perror("dup2"), -1);
// 	close(pipes[i].pipes[1]);
// 	close(pipes[i].pipes[0]);
// 	ft_do_process(env, argv[i], i);
// 	return (0);
// }

// int	child_process_out(t_pipes *pipes, int i, char *env[], char *argv[])
// {
// 	int		fd;
// 	// int j = 0;

// 	if (dup2(pipes[i - 1].pipes[0], STDIN_FILENO) < 0)
// 		return (close(pipes[i - 1].pipes[0]), perror("dup2"), -1);
// 	close(pipes[i - 1].pipes[0]);
// 	close(pipes[i - 1].pipes[1]);
// 	fd = ft_create_fd(pipes[0].fd2, O_WRONLY | O_CREAT | O_TRUNC);
// 	if (fd < 0)
// 		return (-1);
// 	if (dup2(fd, STDOUT_FILENO) < 0)
// 		return (close(pipes[i].pipes[0]), close(fd), perror("dup2"), -1);
// 	close(fd);
// 	ft_do_process(env, argv[i], i);
// 	return (0);
// }
