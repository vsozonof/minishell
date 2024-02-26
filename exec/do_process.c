/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:29:51 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 10:29:22 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_do_process(char *envp[], char *cmd)
{
	int		i;
	char	**path;
	char	*buf2;

	i = 0;
	buf2 = ft_do_process_helper(cmd);
	if (buf2 != NULL)
		return (buf2);
	path = ft_get_path(envp);
	if (!path)
		return (NULL);
	while (path[i++])
	{
		buf2 = ft_strjoin_help(path, cmd, i);
		if (access(buf2, X_OK) == 0)
		{
			ft_split_free(path);
			return (buf2);
		}
		free(buf2);
	}
	ft_split_free(path);
	return (NULL);
}

char	*ft_do_process_helper(char *cmd)
{
	int		result;
	char	*buf2;

	buf2 = NULL;
	result = ft_do_process_checker(cmd);
	if (result == 0)
	{
		buf2 = ft_strdup(cmd);
		return (buf2);
	}
	return (NULL);
}

//X_OK Tests whether the file can be accessed for execution.
// -> verifie si on a les droits
int	ft_do_process_checker(char *cmd)
{
	if (!cmd)
		return (-2);
	if (access(cmd, X_OK) == 0)
		return (0);
	return (-1);
}

char	*ft_strjoin_help(char **path, char *cmd, int i)
{
	char	*buf;
	char	*buf2;

	buf = ft_strjoin(path[i], "/");
	if (!buf)
		return (write(2, "Error in path\n", 15), NULL);
	buf2 = ft_strjoin(buf, cmd);
	if (!buf2)
		return (write(2, "Error in path\n", 15), NULL);
	free(buf);
	return (buf2);
}

char	**ft_get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
	{
		if (!env[i + 1])
			break;
		i++;
	}
	if (!env[i])
		perror("Error: PATH not found");
	path = ft_split(env[i] + 5, ':');
	return (path);
}
