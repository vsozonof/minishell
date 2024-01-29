/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:31:19 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/29 02:50:16 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_do_process(char *envp[], char *cmd)
{
	int		i;
	char	**path;
	char	*buf2;

	i = 0;
	path = ft_get_path(envp);
	if (!path)
		return (NULL);
	while (path[i++])
	{
		buf2 = ft_strjoin_help(path, cmd, i);
		free(path[i]);
		if (access(buf2, 0) == 0)
		{
			while (path[i++])
				free(path[i]);
			return (free(path), buf2);
		}
		free(buf2);
	}
	free(path[i]);
	free(path);
	return (NULL);
}

char *ft_strjoin_help(char **path, char *cmd, int i)
{
	char	*buf;
	char	*buf2;
	
	buf = ft_strjoin(path[i], "/");
	if (!buf)
		return (fprintf(stderr, "ERROR IN PATH\n"), NULL);
	buf2 = ft_strjoin(buf, cmd);
	if (!buf2)
		return (fprintf(stderr, "ERROR IN PATH\n"), NULL);
	free(buf);
	return (buf2);
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
	return (path);
}
