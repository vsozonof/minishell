/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:29:51 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 21:47:53 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_do_process(char *envp[], char *cmd, t_data *data)
{
	int		i;
	char	**path;
	char	*buf2;

	i = 0;
	buf2 = ft_do_process_helper(cmd, data);
	if (buf2 != NULL)
		return (buf2);
	if (data->i_status == 126)
		return (NULL);
	path = ft_get_path(envp);
	if (!path)
		return (NULL);
	while (path[i++])
	{
		buf2 = ft_strjoin_help(path, cmd, i);
		if (access(buf2, F_OK) == 0)
		{
			if (access(buf2, X_OK) == 0)
				return (ft_split_free(path), buf2);
			set_status(data, 0, "Permission denied\n", cmd);
			ft_split_free(path);
			data->i_status = 1;
			return (NULL);
		}
		free(buf2);
	}
	set_status(data, 0, "Command not found\n", cmd);
	data->i_status = 127;
	ft_split_free(path);
	return (NULL);
}

char	*ft_do_process_helper(char *cmd, t_data *data)
{
	int			result;
	char		*buf2;
	struct stat	S_ISDIR;

	buf2 = NULL;
	result = ft_do_process_checker(cmd, data);
	if (stat(cmd, &S_ISDIR) == 0)
	{
		set_status(data, 0, "No such file or directory\n", cmd);
		data->i_status = 126;
		return (NULL);
	}
	if (result == 0)
	{
		buf2 = ft_strdup(cmd);
		return (buf2);
	}
	return (NULL);
}

//X_OK Tests whether the file can be accessed for execution.
// -> verifie si on a les droits
int	ft_do_process_checker(char *cmd, t_data *data)
{
	if (!cmd)
		return (-2);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (0);
		set_status(data, 0, "Permission denied\n", cmd);
		data->i_status = 126;
		return (-2);
	}
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
