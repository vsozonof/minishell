/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:31:19 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/06 14:30:35 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_do_process(char *envp[], char *cmd)
// {
// 	int		i;
// 	char	**path;
// 	char	**cmd_argument;

// 	i = 0;
// 	cmd_argument = ft_split(cmd, ' ');
// 	path = ft_get_path(envp);
// 	while (path[i])
// 	{
// 		path[i] = str_join_free(path[i], "/");
// 		path[i] = str_join_free(path[i], cmd_argument[0]);
// 		execve(path[i], cmd_argument, envp);
// 		i++;
// 	}
// 	ft_freedb(path);
// 	execve(cmd_argument[0], cmd_argument, envp);
// 	ft_freedb(cmd_argument);
// 	return ;
// }

// char	**ft_get_path(char **env)
// {
// 	int		i;
// 	char	**path;

// 	i = 0;
// 	while (ft_strncmp(env[i], "PATH=", 5) != 0)
// 		i++;
// 	if (!env[i])
// 		perror("Error: PATH not found");
// 	path = ft_split(env[i] + 5, ':');
// 	return (path);
// }

// char *str_join_free(char *path, char *cmd)
// {
// 	char *str;
	
// 	str = ft_strjoin(path, cmd);
// 	free(path);
// 	return (str);
// }

void	ft_freedb(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// int	ft_create_fd(char *argv, int flag)
// {
// 	int	fd;

// 	fd = open(argv, flag, 0644);
// 	if (fd < 0)
// 		return (printf("problem with fd\n"), -1);
// 	return (fd);
// }
