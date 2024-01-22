/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:02:25 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/22 10:58:19 by vsozonof         ###   ########.fr       */
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
	path = extract_arg(data->input);
	if (!ft_strncmp(path, "..", 2))
	{
		
	}
	printf("path = [%s]\n", path);
	free(path);
}

void	change_directory(t_data *data, char *path)
{
	if (access(path, F_OK) != -1)
	{
		if (chdir(path) == 0)
		{
			update_vars(data);
			free(path);
		}
		else
			printf("poisson poulet\n");
	}
	else
		printf("poisson des alpes\n");
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
