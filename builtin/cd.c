/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:02:25 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/29 02:48:01 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Update les var dans la struct prompt quand changement de dossier

void	execute_cd(t_data *data)
{
	char	*path;

	if (n_args(data->input) == 0)
	{
		change_directory(data, ft_get_env(data->env, "HOME"));
		data->i_status = 0;
		return ;
	}
	else if (n_args(data->input) != 1)
	{
		pr_error("cd: too many arguments.");
		data->i_status = 127;
		return ;
	}
	path = cd_extract_arg(data->input);
	if (!ft_strncmp(path, "..", 2))
	{
		go_back_one_level(data);
		free(path);
	}
	else
		change_directory(data, path);
}

void	go_back_one_level(t_data *data)
{
	char	*path;
	int		i;

	i = ft_strlen(data->pr->w_d);
	i--;
	while (i > 0 && data->pr->w_d[i] && data->pr->w_d[i] != '/')
		i--;
	path = ft_substr(data->pr->w_d, 0, i + 1);
	change_directory(data, path);
}

void	change_directory(t_data *data, char *path)
{
	if (access(path, F_OK) != -1)
	{
		if (chdir(path) == 0)
		{
			update_vars(data);
			return (free(path));
		}
		else
			error_handling(errno, path);
	}
	else
		error_handling(errno, path);
}

void	update_vars(t_data *data)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*old_wd;

	old_pwd = ft_get_env_node(data->env, "OLDPWD");
	pwd = ft_get_env_node(data->env, "PWD");
	free(data->pr->w_d);
	data->pr->w_d = getcwd(NULL, 0);
	old_wd = pwd->var;
	free(old_pwd->var);
	old_pwd->var = ft_strjoin("OLD", old_wd);
	free(old_wd);
	pwd->var = ft_strjoin("PWD=", data->pr->w_d);
}