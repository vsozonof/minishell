/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:10:50 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/22 14:53:14 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	Pipex_Exec(int argc, char *argv[], char *envp[])
{
	// char	**new_argv;
	// int		new_argc;
	char	**buf;
	char	*fre;
	(void)argc;
	// new_argv = NULL;
	// new_argv = get_new_argv(argv);
	// new_argc = found_max(new_argv);
	int i = 0;
	while (argv[i])
	{
		buf = arg(argv[i]);
		fre = ft_do_process(envp, buf[0], 0, 0);
		if (!fre)
		{
			perror("wrong commd\n");
			ft_freedb(buf);
			ft_freedb(argv);
			return (0);
		}
		ft_freedb(buf);
		free(fre);
		i++;
	}
	// ft_pipex(argv, envp, argc);
	waitpid(-1, NULL, 0);
	ft_freedb(argv);
	return (0);
}
