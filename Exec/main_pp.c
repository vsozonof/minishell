/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:10:50 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/22 15:11:28 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	Pipex_Exec(int argc, char *argv[], char *envp[])
{
	char	**buf;
	char	*fre;
	int i;

	i = 0;
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
	// ft_freedb(argv); // a voir par rapport a mes free
	return (0);
}
