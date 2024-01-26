/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:31:19 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/26 20:38:40 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_do_process(char *envp[], char *cmd)
{
	int		i;
	char	**path;
	char	*buf;
	char	*buf2;

	i = 0;
	path = ft_get_path(envp);
	while (path[i++])
	{
		buf = ft_strjoin(path[i], "/");
		buf2 = ft_strjoin(buf, cmd);
		free(buf);
		if (access(buf2, 0) == 0)
		{
			free(path[i]);
			while (path[i++])
				free(path[i]);
			free(path);
			return (buf2);
		}
		free(buf2);
		free(path[i]);
	}
	free(path);
	return (NULL);
}

char	**ft_get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		perror("Error: PATH not found");
	path = ft_split(env[i] + 5, ':');
	// fprintf(stderr, "%s\n", env[i] + 5);
	return (path);
}
